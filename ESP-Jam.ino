extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3) {
  return (arg == 31337) ? 1 : 0;
}

#include "Globals.hpp"
#include "IR-Raw.hpp"
#include "BLE_Spam.hpp"
#include "Games.hpp"
#include "driver/rtc_io.h"
#include "soc/rtc_cntl_reg.h"
#include "Menu_IR.hpp"
#include <IRremote.hpp>
#include <esp_system.h>

#define IR_SEND_PIN 25

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);
  delay(500);
  Serial.println("\n[BOOT] Start");

  Serial.println("[BOOT] Pins...");
  pinMode(SubmitbuttonPin, INPUT_PULLUP);
  pinMode(LeftbuttonPin,   INPUT_PULLUP);
  pinMode(RightbuttonPin,  INPUT_PULLUP);
  pinMode(UpbuttonPin,     INPUT_PULLUP);
  pinMode(DownbuttonPin,   INPUT_PULLUP);
  pinMode(rootPin,         INPUT_PULLUP);
  pinMode(BUZZER_PIN,      OUTPUT);

  Serial.println("[BOOT] IR Sender...");
  IrSender.begin(IR_SEND_PIN);
  Serial.println("[BOOT] Preferences...");
  preferences.begin("Boot", false);

  currentMode = preferences.getInt("mode", 0);
  identification = preferences.getInt("idt", 5);
  Serial.printf("[BOOT] currentMode=%d identification=%d\n", currentMode, identification);
  brightnessValue = preferences.getInt("display", 1);

  Serial.println("[BOOT] WiFi read prefs...");
  wifiPrefs.begin("wifi", true);
  String savedSSID = wifiPrefs.getString("ssid", "");
  String savedPass = wifiPrefs.getString("pass", "");
  wifiPrefs.end();

  if (savedSSID.length() > 0 && currentMode == 0) {
    Serial.println("[BOOT] WiFi connect saved SSID...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(savedSSID.c_str(), savedPass.c_str());
    WiFi.setAutoReconnect(true);
    WiFi.setSleep(false);
  }

  if (digitalRead(rootPin) == LOW) {
    Serial.println("[BOOT] rootPin low -> Spam-Modus zurueckgesetzt");
    preferences.begin("Boot", false);
    preferences.putInt("mode", 0);
    preferences.putInt("idt", 0);
    preferences.end();
    currentMode = 0;
  }

  if (currentMode == 1) {
    Serial.println("[BOOT] Spam-Modus aktiv");
    Spam = true;
    Menu = false;
    Serial.printf("[BOOT] init idt=%d\n", identification);
    if (identification >= 1 && identification <= 3) { Serial.println("[BOOT] initBLESpam()..."); initBLESpam(); }
    if (identification == 4) { Serial.println("[BOOT] initBLEjam()..."); initBLEjam(); }
    if (identification == 5) { Serial.println("[BOOT] initBLESpamM()..."); initBLESpamM(); }
    Serial.println("[BOOT] Spam-Init fertig");
  }

  Serial.println("[BOOT] Display init...");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);

  display.dim(brightnessValue == 0);

  if (Spam == false) {
    display.display();
    display.clearDisplay();
    #include "Fonts/FreeMonoBold12pt7b.h"
    #include "Fonts/Picopixel.h"

    static const unsigned char PROGMEM image_Charging_lightning_mask_bits[] = {0x01,0x00,0x02,0x00,0x04,0x00,0x08,0x00,0x1e,0x00,0x3c,0x00,0x08,0x00,0x10,0x00,0x20,0x00,0x40,0x00};

    static const unsigned char PROGMEM image_WarningDolphin_bits[] = {0x00,0x00,0x00,0x00,0x10,0x40,0x00,0x00,0x00,0x00,0x10,0x40,0x00,0x00,0xff,0xe0,0x08,0x40,0x00,0x03,0x00,0x18,
    0x08,0x40,0x00,0x0c,0x00,0x06,0x04,0x40,0x00,0x10,0x00,0x01,0x04,0x40,0x00,0x20,0x00,0x00,0x80,0x00,0x00,0x40,0x00,0x00,0x42,0x40,0x00,0x80,0x00,0x00,0x40,0x00,0x00,0x80,0x00,
    0x00,0x20,0x00,0x01,0x00,0xf0,0x00,0x21,0xe0,0x01,0x01,0x08,0x00,0x16,0x10,0x02,0x02,0xf4,0x00,0x18,0x08,0x02,0x05,0xda,0x00,0x60,0x08,0x02,0x05,0xca,0x01,0x80,0x78,0x02,0x05,
    0xfa,0x06,0x01,0xf0,0x04,0x05,0xfa,0x00,0x03,0xe0,0x04,0x02,0xf4,0x00,0x0f,0xc0,0x04,0x01,0x7c,0x00,0x1f,0x80,0x04,0x00,0x82,0x00,0x3f,0x00,0x04,0x01,0x00,0x00,0x7e,0x00,0x04,
    0x00,0x00,0x00,0xfc,0x00,0x04,0x00,0x00,0x03,0x0f,0xf0,0x04,0x03,0x00,0x0c,0x03,0xc8,0x04,0x04,0x80,0xff,0xfc,0x08,0x0c,0x04,0x80,0x00,0x00,0x08,0x0c,0x04,0x80,0x00,0x00,0x10,
    0x1c,0x04,0x80,0x00,0x00,0x60,0x18,0x78,0x80,0x00,0x03,0x80,0x38,0x84,0x80,0x07,0xfc,0x00,0x39,0x03,0x80,0x01,0xf8,0x00,0x71,0x02,0x40,0x00,0x08,0x00,0x71,0x42,0x40,0x00,0x08,
    0x00,0xf1,0x42,0x40,0x00,0x08,0x00,0xe1,0x3c,0x40,0x00,0x08,0x00,0xe2,0x38,0x80,0x00,0x08,0x00,0xe2,0x01,0x00,0x00,0x08,0x00,0xc4,0x02,0x00,0x00,0x04,0x00,0xc4,0x02,0x00,0x00,
    0x04,0x00,0xc8,0x02,0x00,0x00,0x04,0x00,0x88,0x02,0x00,0x00,0x04,0x00,0x90,0x02,0x00,0x00,0x04,0x00};

    display.clearDisplay();

    display.setTextColor(1);
    display.setTextWrap(false);
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(16, 17);
    display.print("ESP-JAM");

    display.setFont(&Picopixel);
    display.setCursor(46, 59);
    display.print("Powered By SeDartsch");

    display.drawBitmap(-1, 23, image_WarningDolphin_bits, 45, 42, 1);

    display.drawBitmap(114, 50, image_Charging_lightning_mask_bits, 9, 10, 1);
    display.display();
    delay(2000);
    display.setFont();
    display.clearDisplay();
    drawMenu();
  }
  
  display.display();
  display.setTextSize(1);
}

void loop() {
  if (deauthRunning) {
    unsigned long now = millis();
    if (now - lastDeauthMillis >= deauthInterval) {
      sendDeauth();
      lastDeauthMillis = now;
    }
  }

  if (currentState == DEAUTH_CLIENTS && !deauthRunning) {
    static unsigned long lastListRefresh = 0;
    if (millis() - lastListRefresh >= 500) {
      lastListRefresh = millis();
      drawMenu();
    }
  }

  if (deauthRunning) {
    static unsigned long lastDropCheck = 0;
    if (millis() - lastDropCheck >= 1000) {
      lastDropCheck = millis();
      for (int i = 0; i < clientCount; i++) {
        if (!clients[i].dropped && (millis() - clients[i].lastSeen) > 4000) {
          clients[i].dropped = true;
          droppedClients++;
        }
      }
      if (currentState == DEAUTH_LIST) drawMenu();
    }
  }
  if (scanning) {
    int found = WiFi.scanComplete();
    if (found >= 0) {
      showScannedNetworks();
      scanning = false;
    }
    else if (found == WIFI_SCAN_FAILED) {
      scanning = false;
      wlanLastError = "Scan fehlgeschlagen";
      switchMenu(WLAN_MENU);
      drawMenu();
    }
  }

  if (deauthScanRunning) {
    int found = WiFi.scanComplete();
    if (found >= 0) {
      networkCount = min(found, MAX_SCANNED_NETWORKS);
      for (int i = 0; i < networkCount; i++) {
        String name = WiFi.SSID(i);
        scannedNetworks[i].ssid = (name.length() == 0) ? "(hidden)" : name;
        memcpy(scannedNetworks[i].bssid, WiFi.BSSID(i), 6);
        scannedNetworks[i].channel = WiFi.channel(i);
        scannedNetworks[i].rssi = WiFi.RSSI(i);
      }
      WiFi.scanDelete();
      deauthScanRunning = false;
      deauthTargetIdx = 0;
      if (etPendingSelect) {
        etPendingSelect = false;
        switchMenu(networkCount > 0 ? EVIL_TWIN_SELECT : WLAN_TOOLS_MENU);
      } else {
        switchMenu(DEAUTH_LIST);
      }
      drawMenu();
    }
    else if (found == WIFI_SCAN_FAILED) {
      deauthScanRunning = false;
      switchMenu(WLAN_TOOLS_MENU);
      drawMenu();
    }
  }

  if (snifferRunning && currentState == SNIFFER_UI) {
    unsigned long now = millis();
    if (snifferAutoHop && (now - lastChannelHop >= snifferHopInterval)) {
      setSnifferChannel(snifferChannel + 1);
    }
    if (now - lastSnifferDisplay >= 200) {
      lastSnifferDisplay = now;
      drawMenu();
    }
  }

  if (bleSnifferRunning && currentState == BLE_SNIFFER_UI) {
    static unsigned long lastBleSnifferUI = 0;
    if (millis() - lastBleSnifferUI >= 300) {
      lastBleSnifferUI = millis();
      drawMenu();
    }
  }

  if (currentState == WLAN_CONNECTING) {
    if (WiFi.status() == WL_CONNECTED) {
      wlanLastError = "";
      wifiPrefs.begin("wifi", false);
      wifiPrefs.putString("ssid", connectSSID);
      wifiPrefs.putString("pass", connectPassword);
      wifiPrefs.end();
      switchMenu(WLAN_STATUS);
      drawMenu();
    }
    else if (WiFi.status() == WL_CONNECT_FAILED || WiFi.status() == WL_NO_SSID_AVAIL) {
      WiFi.disconnect();
      wlanLastError = "Auth/SSID Fehler";
      switchMenu(WLAN_STATUS);
      drawMenu();
    }
    else if (millis() - wlanConnectStart > WLAN_CONNECT_TIMEOUT) {
      WiFi.disconnect();
      wlanLastError = "Timeout";
      switchMenu(WLAN_STATUS);
      drawMenu();
    }
  }

  if (evilTwinActive) {
    evilTwinTick();
    if (currentState == EVIL_TWIN_UI) {
      static unsigned long lastEvilTwinUI = 0;
      if (millis() - lastEvilTwinUI >= 400) { lastEvilTwinUI = millis(); drawMenu(); }
    }
  }
  if (currentState == BLE_SCAN && bleScanning) {
    bleScanTick();
    if (bleScanDirty) { bleScanDirty = false; drawMenu(); }
  }

  if (currentState == WLAN_SCAN_LIST) {
    static unsigned long lastRescan = 0;
    static bool rescanPending = false;
    if (!rescanPending && millis() - lastRescan >= 8000) {
      WiFi.scanNetworks(true);
      rescanPending = true;
      lastRescan = millis();
    }
    if (rescanPending) {
      int n = WiFi.scanComplete();
      if (n >= 0) {
        rescanPending = false;
        int count = min(n, MAX_WLAN_RESULTS - 1);
        if (count == 0) {
          wlanLastError = "Nichts gefunden!";
          switchMenu(WLAN_STATUS);
        } else {
          for (int i = 0; i < count; i++) {
            String name = WiFi.SSID(i);
            if (name.length() == 0) name = "(versteckt)";
            wlanOpen[i] = (WiFi.encryptionType(i) == WIFI_AUTH_OPEN);
            wlanScanMenu[i] = name + (!wlanOpen[i] ? " *" : "");
          }
          wlanScanMenu[count] = "< Back";
          wlanScanCount = count + 1;
          if (selectedIndex >= wlanScanCount) selectedIndex = wlanScanCount - 1;
        }
        WiFi.scanDelete();
        drawMenu();
      }
      else if (n == WIFI_SCAN_FAILED) rescanPending = false;
    }
  }

  if (currentState == DEAUTH_LIST && !deauthRunning) {
    static unsigned long lastRescan = 0;
    static bool rescanPending = false;
    if (!rescanPending && millis() - lastRescan >= 8000) {
      WiFi.scanNetworks(true);
      rescanPending = true;
      lastRescan = millis();
    }
    if (rescanPending) {
      int n = WiFi.scanComplete();
      if (n >= 0) {
        rescanPending = false;
        networkCount = min(n, MAX_SCANNED_NETWORKS);
        for (int i = 0; i < networkCount; i++) {
          String name = WiFi.SSID(i);
          scannedNetworks[i].ssid = (name.length() == 0) ? "(hidden)" : name;
          memcpy(scannedNetworks[i].bssid, WiFi.BSSID(i), 6);
          scannedNetworks[i].channel = WiFi.channel(i);
          scannedNetworks[i].rssi = WiFi.RSSI(i);
        }
        WiFi.scanDelete();
        jamSelCount = 0;
        for (int i = 0; i < MAX_SCANNED_NETWORKS; i++) {
          if (jamSelected[i] && i >= networkCount) jamSelected[i] = false;
          else if (jamSelected[i]) jamSelCount++;
        }
        if (selectedIndex > networkCount) selectedIndex = networkCount;
        clampScroll(networkCount + 1);
        drawMenu();
      }
      else if (n == WIFI_SCAN_FAILED) rescanPending = false;
    }
  }

  if (currentState == DEAUTH_CLIENTS && !deauthRunning) {
    if (selectedIndex > clientCount + 1) selectedIndex = clientCount + 1;
    clampScroll(clientCount + 2);
  }

  if (Menu) handleMenu();
  if (Game) handleBlackJack();
  if (Game2) handlePingPong();
  if (Game4) handleRaumschiff();
  if (Game5) handleDoodle();
  if (Spam) handleSpam();
}
