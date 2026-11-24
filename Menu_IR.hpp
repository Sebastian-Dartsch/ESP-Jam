#pragma once
#include <nvs_flash.h>

void switchMenu(MenuState newState) {
  currentState = newState; selectedIndex = 0; scrollOffset = 0;
}

void clampScroll(int itemCount) {
  if (selectedIndex < scrollOffset) {
    scrollOffset = selectedIndex;
  } else if (selectedIndex >= scrollOffset + ITEMS_PER_PAGE) {
    scrollOffset = selectedIndex - ITEMS_PER_PAGE + 1;
  }
  int maxOffset = max(0, itemCount - ITEMS_PER_PAGE);
  if (scrollOffset > maxOffset) scrollOffset = maxOffset;
}

void drawTVRemoteUI() {
  display.clearDisplay();
  display.drawBitmap(5, 20, image_TV_s_TEXT_bits, 7, 23, 1);
  display.drawBitmap(87, 38, image_CHANNEL_DOWN_bits, 21, 19, 1);
  display.drawBitmap(62, 7, image_VOL_UP_bits, 20, 19, 1);
  display.drawBitmap(87, 7, image_VOL_DOWN_bits, 20, 19, 1);
  display.drawBitmap(61, 38, image__CHANNEL_UP_bits, 21, 19, 1);
  display.drawBitmap(27, 35, image_POWER_BUTTON_bits, 19, 25, 1);
  display.drawBitmap(27, 4, image_MENU_BUTTON_bits, 19, 25, 1);
    
  int hX = 0, hY = 0, hW = 0, hH = 0;

  switch(selectedIndex) {
    case 0: hX = 27; hY = 35; hW = 19; hH = 25; break;
    case 1: hX = 27; hY = 4;  hW = 19; hH = 25; break;
    case 2: hX = 62; hY = 7;  hW = 20; hH = 19; break;
    case 3: hX = 87; hY = 7;  hW = 20; hH = 19; break;
    case 4: hX = 61; hY = 38; hW = 21; hH = 19; break;
    case 5: hX = 87; hY = 38; hW = 21; hH = 19; break;
  }
  
  display.fillRect(hX, hY, hW, hH, SSD1306_INVERSE);
  display.display();
}

void drawACRemoteUI() {
  display.clearDisplay();
  display.drawBitmap(9, 47, image_paint_11_bits, 1, 1, 1);
  display.drawBitmap(9, 46, image_paint_12_bits, 1, 3, 0);
  display.drawRect(40, 16, 1, 1, 0);
  display.drawBitmap(9, 46, image_paint_12_bits, 1, 3, 0);
  display.drawBitmap(9, 47, image_paint_11_bits, 1, 1, 0);
  display.drawBitmap(20, 46, image_paint_12_bits, 1, 3, 0);
  display.drawBitmap(19, 28, image_paint_11_bits, 1, 1, 1);
  display.drawBitmap(19, 28, image_paint_11_bits, 1, 1, 0);
  display.drawBitmap(72, 7, image_paint_67_copy_1_bits, 19, 21, 1);
  display.drawBitmap(81, 38, image_paint_11_bits, 1, 1, 0);
  display.drawBitmap(62, 38, image_paint_11_bits, 1, 1, 0);
  display.drawBitmap(62, 38, image_paint_11_bits, 1, 1, 0);
  display.drawBitmap(27, 46, image_paint_12_bits, 1, 3, 0);
  display.drawBitmap(72, 36, image_paint_67_1_bits, 19, 21, 1);
  display.drawBitmap(23, 46, image_paint_12_bits, 1, 3, 0);
  display.drawBitmap(23, 45, image_paint_12_bits, 1, 3, 0);
  display.drawBitmap(5, 20, image_paint_23_bits, 7, 23, 1);
  display.drawBitmap(30, 35, image_paint_51_bits, 19, 25, 1);
  display.drawBitmap(30, 4, image_paint_25_bits, 19, 25, 1);
    
  int hX = 0, hY = 0, hW = 0, hH = 0;

  switch(selectedIndex) {
    case 0: hX = 30; hY = 35; hW = 19; hH = 25; break;
    case 1: hX = 30; hY = 4; hW = 19; hH = 25; break;
    case 2: hX = 72; hY = 36; hW = 19; hH = 21; break;
    case 3: hX = 72; hY = 7; hW = 19; hH = 21; break;
  }
  
  display.fillRect(hX, hY, hW, hH, SSD1306_INVERSE);
  display.display();
}

void drawAudioRemoteUI() {
  display.clearDisplay();
  display.drawBitmap(9, 47, image_paint_1_bits, 1, 1, 1);
  display.drawBitmap(9, 46, image_paint_27_bits, 1, 3, 0);
  display.drawRect(40, 16, 1, 1, 0);
  display.drawBitmap(9, 46, image_paint_27_bits, 1, 3, 0);
  display.drawBitmap(9, 47, image_paint_1_bits, 1, 1, 0);
  display.drawBitmap(20, 46, image_paint_27_bits, 1, 3, 0);
  display.drawBitmap(19, 28, image_paint_1_bits, 1, 1, 1);
  display.drawBitmap(19, 28, image_paint_1_bits, 1, 1, 0);
  display.drawBitmap(87, 38, image_paint_14_bits, 21, 19, 1);
  display.drawBitmap(81, 38, image_paint_1_bits, 1, 1, 0);
  display.drawBitmap(62, 38, image_paint_1_bits, 1, 1, 0);
  display.drawBitmap(62, 7, image_paint_13_bits, 20, 19, 1);
  display.drawBitmap(62, 38, image_paint_1_bits, 1, 1, 0);
  display.drawBitmap(87, 7, image_paint_15_bits, 20, 19, 1);
  display.drawBitmap(27, 46, image_paint_27_bits, 1, 3, 0);
  display.drawBitmap(61, 38, image_paint_18_bits, 21, 19, 1);
  display.drawBitmap(23, 46, image_paint_27_bits, 1, 3, 0);
  display.drawBitmap(23, 45, image_paint_27_bits, 1, 3, 0);
  display.drawBitmap(27, 35, image_paint_22_bits, 19, 25, 1);
  display.drawBitmap(27, 4, image_paint_32_bits, 19, 25, 1);
  display.drawBitmap(5, 18, image_paint_0_bits, 7, 29, 1);
    
  int hX = 0, hY = 0, hW = 0, hH = 0;

  switch(selectedIndex) {
    case 0: hX = 27; hY = 35; hW = 19; hH = 25; break;
    case 1: hX = 27; hY = 4;  hW = 19; hH = 25; break;
    case 2: hX = 62; hY = 7;  hW = 20; hH = 19; break;
    case 3: hX = 87; hY = 7;  hW = 20; hH = 19; break;
    case 4: hX = 61; hY = 38; hW = 21; hH = 19; break;
    case 5: hX = 87; hY = 38; hW = 21; hH = 19; break;
  }
  
  display.fillRect(hX, hY, hW, hH, SSD1306_INVERSE);
  display.display();
}

void drawEpsonRemoteUI() {
  display.clearDisplay();
  display.drawBitmap(9, 47, image_paint_101_bits, 1, 1, 1);
  display.drawBitmap(9, 46, image_paint_102_bits, 1, 3, 0);
  display.drawRect(40, 16, 1, 1, 0);
  display.drawBitmap(9, 46, image_paint_102_bits, 1, 3, 0);
  display.drawBitmap(9, 47, image_paint_101_bits, 1, 1, 0);
  display.drawBitmap(20, 46, image_paint_102_bits, 1, 3, 0);
  display.drawBitmap(19, 28, image_paint_101_bits, 1, 1, 1);
  display.drawBitmap(19, 28, image_paint_101_bits, 1, 1, 0);
  display.drawBitmap(81, 38, image_paint_101_bits, 1, 1, 0);
  display.drawBitmap(62, 38, image_paint_101_bits, 1, 1, 0);
  display.drawBitmap(62, 38, image_paint_101_bits, 1, 1, 0);
  display.drawBitmap(27, 46, image_paint_102_bits, 1, 3, 0);
  display.drawBitmap(23, 46, image_paint_102_bits, 1, 3, 0);
  display.drawBitmap(23, 45, image_paint_102_bits, 1, 3, 0);
  display.drawBitmap(33, 35, image_Richtige_ON_button_bits, 19, 25, 1);
  display.drawBitmap(76, 19, image_paint_121_bits, 19, 25, 1);
  display.drawBitmap(36, 15, image_paint_102_bits, 1, 3, 0);
  display.drawBitmap(28, 44, image_ON_Text_bits, 3, 7, 1);
  display.drawBitmap(5, 17, image_paint_122_bits, 8, 29, 1);
  display.drawBitmap(36, 46, image_paint_102_bits, 1, 3, 0);
  display.drawBitmap(28, 12, image_OFF_Text_bits, 3, 11, 1);
  display.drawBitmap(33, 4, image_Richtige_ON_button_bits, 19, 25, 1);
    
  int hX = 0, hY = 0, hW = 0, hH = 0;

  switch(selectedIndex) {
    case 0: hX = 33; hY = 35; hW = 19; hH = 25; break;
    case 1: hX = 33; hY = 4; hW = 19; hH = 25; break;
    case 2: hX = 76; hY = 19; hW = 19; hH = 25; break;
  }
  
  display.fillRect(hX, hY, hW, hH, SSD1306_INVERSE);
  display.display();
}

int dupCountFor(int idx) {
  if (scannedNetworks[idx].ssid.length() == 0) return 1;
  int c = 0;
  for (int i = 0; i < networkCount; i++)
    if (scannedNetworks[i].ssid == scannedNetworks[idx].ssid) c++;
  return c;
}

void drawDeauthList() {
  display.clearDisplay();
  display.setTextSize(1);

  if (!deauthRunning && networkCount == 0) {
    display.setCursor(10, 28);
    display.print("Keine Netzwerke!");
    display.setCursor(10, 40);
    display.print("< Back");
    display.display();
    return;
  }

  if (!deauthRunning) clampScroll(networkCount + 1);

  if (deauthRunning) {
    display.drawRoundRect(14, 10, 100, 36, 4, SSD1306_WHITE);
    display.setCursor(22, 17);
    display.print("DEAUTHING...");
    display.setCursor(22, 28);
    String n = deauthTargetName;
    if (n.length() > 14) n = n.substring(0, 14);
    display.print(n);
    display.setCursor(22, 39);
        if (jamAPCount > 1) display.print("Kan: " + String(jamAPCount) + " APs");
    else display.print("Kanal: " + String(targetChannel));
    display.setCursor(0, 54);
    display.print("TX:" + String(deauthSent) + " DC:" + String(droppedClients));
    display.display();
    return;
  }

  int total = networkCount + 1;
  for (int i = 0; i < ITEMS_PER_PAGE; i++) {
    int item = scrollOffset + i;
    if (item >= total) break;
    int yPos = i * 16;
    if (item == selectedIndex) display.drawRoundRect(0, yPos, 120, 15, 3, SSD1306_WHITE);
    if (item == networkCount) {
      display.setCursor(20, yPos + 4);
      display.print("< Back");
    } else {
      if (item == deauthTargetIdx || jamSelected[item]) { display.setCursor(3, yPos + 4); display.print("*"); }
      display.setCursor(12, yPos + 4);
      String name = scannedNetworks[item].ssid;
      if (name.length() == 0) name = "(hidden)";
      int dup = dupCountFor(item);
      if (dup > 1) name = "(" + String(dup) + ") " + name;
      if (name.length() > 8) name = name.substring(0, 8);
      display.print(name);
      display.setCursor(72, yPos + 4);
      display.print("ch" + String(scannedNetworks[item].channel));
      display.setCursor(100, yPos + 4);
      display.print(String(scannedNetworks[item].rssi));
    }
  }

  display.drawLine(125, 0, 125, 63, SSD1306_WHITE);
  int barHeight = 64 / total;
  int barY = (total > 1) ? (selectedIndex * (64 - barHeight)) / (total - 1) : 0;
  display.fillRoundRect(123, barY, 4, barHeight, 1, SSD1306_WHITE);
  display.display();
}

void drawDeauthClients() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Clients: " + String(clientCount));
  display.setCursor(88, 0);
  display.print("ch" + String(targetChannel));
  display.drawLine(0, 9, 128, 9, SSD1306_WHITE);
  clampScroll(clientCount + 2);

  int total = clientCount + 2;
  for (int i = 0; i < ITEMS_PER_PAGE; i++) {
    int item = scrollOffset + i;
    if (item >= total) break;
    int yPos = 12 + i * 11;
    if (item == selectedIndex) display.drawRoundRect(0, yPos - 1, 120, 12, 2, SSD1306_WHITE);
    if (item == clientCount) {
      display.setCursor(4, yPos);
      display.print("> Broadcast");
    } else if (item == clientCount + 1) {
      display.setCursor(4, yPos);
      display.print("< Back");
    } else {
      uint8_t *m = clients[item].mac;
      char buf[18];
      snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
               m[0], m[1], m[2], m[3], m[4], m[5]);
      display.setCursor(4, yPos);
      display.print(buf);
    }
  }
  display.display();
}

void HardReset() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("WLAN/BLE off");
  display.display();


  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  if (esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_ENABLED) {
    btStop();
    esp_bt_controller_disable();
  }
  if (esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_ENABLED ||
      esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_IDLE) {
    esp_bt_controller_deinit();
  }
  delay(100);

  bool wifiIsOff = (WiFi.getMode() == WIFI_OFF);
  bool btIsOff   = (esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_IDLE);

  display.print(wifiIsOff && btIsOff ? "   [ OK ]" : "   [ ER ]");
  display.display();
  delay(200);

  preferences.end();
  wifiPrefs.end();

  display.setCursor(0, 10);
  display.print("NVS Reset");
  display.display();

  nvs_flash_deinit();
  esp_err_t nvsResult = nvs_flash_erase();
  if (nvsResult == ESP_OK) {
    nvs_flash_init();
    display.print("      [ OK ]");
  } else {
    display.print("      [ ER ]");
  }
  display.display();
  delay(200);

  display.setCursor(0, 30);
  display.print("System Reset");
  display.print("   [ OK ]");
  display.print("");
  display.print("[+] Rebooting...");
  display.display();
  delay(1000);

  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  ESP.restart();
}

void drawSnifferUI() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("SNIFFER");
  display.setCursor(88, 0);
  display.print("CH:" + String(snifferChannel) + (snifferAutoHop ? " A" : " M"));
  display.drawLine(0, 9, 128, 9, SSD1306_WHITE);
  display.setCursor(0, 18);
  display.print("Pkts:   " + String(packetCount));
  display.setCursor(0, 30);
  display.print("Deauth: " + String(deauthCount));
  display.setCursor(0, 42);
  display.print("EAPOL:  " + String(eapolCount));
  display.drawLine(0, 52, 128, 52, SSD1306_WHITE);
  display.setCursor(0, 54);
  display.print("[U/D]Kanal [OK]Stop");
  display.display();
}

void drawLinkBypassUI() {
  display.clearDisplay();
  display.setTextSize(1);
  display.drawRoundRect(8, 15, 112, 34, 4, SSD1306_WHITE);
  display.setCursor(14, 24);
  display.print("Coming soon...");
  display.setCursor(14, 36);
  display.print("[OK]/[<]=Zurueck");
  display.display();
}

void drawMenu() {
  display.clearDisplay();
  String* currentArray;
  int currentSize = 0;

  if (currentState == WLAN_PASSWORD_ENTRY) { drawWlanPasswordEntry(); return; }
  else if (currentState == WLAN_CONNECTING)     { drawWlanConnecting();     return; }
  else if (currentState == WLAN_STATUS)         { drawWlanStatus();         return; }
  else if (currentState == WLAN_SCANNING || currentState == DEAUTH_SCANNING) { drawScanningUI(); return; } 
  else if (currentState == MAIN_MENU) { currentArray = mainMenu; currentSize = MAIN_ITEMS; }
  else if (currentState == ABOUT_UI) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("ESP-Jam v2.5");
    display.drawLine(0, 9, 128, 9, SSD1306_WHITE);
    display.setCursor(0, 20);
    display.print("Sebastian Dartsch");
    display.setCursor(0, 32);
    display.print("dartschbasti@gmail.com");
    display.setCursor(0, 54);
    display.print("< =Zurueck");
    display.display();
    return;
  }
  else if (currentState == IR_MENU) { currentArray = irMenu; currentSize = IR_ITEMS; }
  else if (currentState == IR_SAVED_MENU) { currentArray = savedMenu; currentSize = SAVED_ITEMS; }
  else if (currentState == IR_UNIVERSAL_MENU) { currentArray = univMenu; currentSize = UNIV_ITEMS; }
  else if (currentState == GAMES_MENU) { currentArray = gamesMenu; currentSize = GAMES_ITEMS;}
  else if (currentState == BLUE_MENU) { currentArray = BlueMenu; currentSize = Blue_ITEMS;}
  else if (currentState == SPAM_MENU) { currentArray = spamMenu; currentSize = SPAM_ITEMS;}
  else if (currentState == SETTINGS_MENU) { currentArray = settingsMenu; currentSize = SETTINGS_ITEMS; }
  else if (currentState == WLAN_MENU) { currentArray = wlanMenu; currentSize = WLAN_ITEMS; }
  else if (currentState == WLAN_SCAN_LIST) { currentArray = wlanScanMenu; currentSize = wlanScanCount; }
  else if (currentState == WLAN_TOOLS_MENU) { currentArray = wlanToolsMenu; currentSize = WLAN_TOOLS_ITEMS; }
  else if (currentState == DEAUTH_LIST) { drawDeauthList(); return; }
  else if (currentState == DEAUTH_CLIENTS) { drawDeauthClients(); return; }
  else if (currentState == SNIFFER_UI) { drawSnifferUI(); return; }
  else if (currentState == LINKBYPASS_UI) { drawLinkBypassUI(); return; }
  else if (currentState == EVIL_TWIN_SELECT) { drawEvilTwinSelect(); return; }
  else if (currentState == EVIL_TWIN_UI)     { drawEvilTwinUI();     return; }
  else if (currentState == BLE_SCAN) { drawBLEScan(); return; }
  else if (currentState == BLE_DEVICE_DETAIL) { drawBLEDetails(); return; }
  else if (currentState == BLE_SNIFFER_UI) { drawBLESniffer(); return; }
  else if (currentState == TV_REMOTE_UI) {
    currentSize = 6;
    drawTVRemoteUI();
    return;
  }
  else if (currentState == AC_REMOTE_UI) {
    currentSize = 4;
    drawACRemoteUI();
    return;
  }
  else if (currentState == Audio_REMOTE_UI) {
    currentSize = 4;
    drawAudioRemoteUI();
    return;
  }
  else if (currentState == Epson_REMOTE_UI) {
    currentSize = 3;
    drawEpsonRemoteUI();
    return;
  }

  if (selectedIndex < scrollOffset) scrollOffset = selectedIndex;
  else if (selectedIndex >= scrollOffset + ITEMS_PER_PAGE) scrollOffset = selectedIndex - ITEMS_PER_PAGE + 1;
  
  display.drawLine(125, 0, 125, 63, SSD1306_WHITE);
  int barHeight = 64 / currentSize;
  int barY = (currentSize > 1) ? (selectedIndex * (64 - barHeight)) / (currentSize - 1) : 0;
  display.fillRoundRect(123, barY, 4, barHeight, 1, SSD1306_WHITE);

  for (int i = 0; i < ITEMS_PER_PAGE; i++) {
    int item_index = scrollOffset + i;
    if (item_index >= currentSize) break;
    int yPos = i * 16;
    if (item_index == selectedIndex) display.drawRoundRect(0, yPos, 120, 15, 3, SSD1306_WHITE);
    display.setCursor(20, yPos + 4);
    if (currentState == SETTINGS_MENU) {
        if (item_index == 0) display.print("Bright: " + String(brightnessValue ? "HIGH" : "LOW"));
        else if (item_index == 1) display.print("UTC: " + String(utcValue > 0 ? "+" : "") + String(utcValue));
        else if (item_index == 3) display.print("VOL: " + String(buzzerVol) + "%");
        else display.print(currentArray[item_index]);
    } else {
        display.print(currentArray[item_index]);
    }
  }
  display.display();
}

void sendSelectedSignal() {
  display.clearDisplay();
  display.drawRoundRect(14, 15, 100, 34, 4, SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(22, 22);
  display.println(F("SENDING..."));
  display.setCursor(22, 35);
  
  int rawDataLength = sizeof(rawData) / sizeof(rawData[0]);
  int rawDataLength2 = sizeof(rawData2) / sizeof(rawData2[0]);
  
  if (currentState == IR_SAVED_MENU) {
    display.println(savedMenu[selectedIndex]); display.display();
    switch (selectedIndex) {
      case 0: IrSender.sendRC6(0x0, 0xC, 0); break;
      case 1: IrSender.sendRaw(rawData, rawDataLength, 38); break;
      case 2: IrSender.sendRaw(rawData2, rawDataLength2, 38); break;
      case 3: IrSender.sendSamsung(0x7, 0x2, 0); break;
      case 4: IrSender.sendNEC(0x0, 0x2, 0); break;
    }
  }
  else if (currentState == TV_REMOTE_UI) {
    display.println(""); display.display();
    switch (selectedIndex) {
      case 0: 
        IrSender.sendNEC(0x0586, 0x0F, 0); delay(40); IrSender.sendNEC(0x4, 0x8, 0); delay(40);
        IrSender.sendRC6(0x0, 0xC, 0); delay(40); IrSender.sendSamsung(0x7, 0x2, 0); delay(40);
        IrSender.sendSamsung(0x07, 0xE6, 0); delay(40); IrSender.sendSony(0x01, 0x15, 2, 12); delay(40);
        IrSender.sendSony(0x01, 0x2F, 2, 12); delay(40); IrSender.sendNEC(0xC7EA, 0x17, 0); delay(40);
        IrSender.sendNEC(0x40, 0x12, 0); delay(40); IrSender.sendNEC(0x80, 0x0C, 0);
        break;
      case 1: 
        IrSender.sendNEC(0x0586, 0x14, 0); delay(40); IrSender.sendRC6(0x0, 0x54, 0); delay(40);
        IrSender.sendSamsung(0x07, 0x1A, 0); delay(40); IrSender.sendSamsung(0x07, 0x79, 0); delay(40);
        IrSender.sendNEC(0x04, 0x43, 0); delay(40); IrSender.sendSony(0x01, 0x60, 2, 12); delay(40);
        IrSender.sendNEC(0x04, 0x1D, 0); delay(40); IrSender.sendNEC(0xC7EA, 0x03, 0); delay(40);
        IrSender.sendNEC(0x04, 0x2D, 0); delay(40); IrSender.sendNEC(0x04, 0x4F, 0); delay(40);
        IrSender.sendNEC(0x7D02, 0x45, 0); delay(40); IrSender.sendNEC(0x7F00, 0x5A, 0); delay(40);
        IrSender.sendNEC(0x7F00, 0x5A, 0); delay(40); IrSender.sendNEC(0x04, 0x7C, 0);
        break;
      case 2: 
        IrSender.sendNEC(0x0586, 0x0C, 0); delay(40); IrSender.sendNEC(0x4, 0x2, 0); delay(40);
        IrSender.sendRC6(0x0, 0x10, 0); delay(40); IrSender.sendSamsung(0x7, 0x7, 0); delay(40);
        IrSender.sendSony(0x01, 0x12, 2, 12); delay(40); IrSender.sendNEC(0x02, 0x1F, 0); delay(40);
        IrSender.sendNEC(0xC7EA, 0x0F, 0); delay(40); IrSender.sendNEC(0x0040, 0x1A, 0); delay(40);
        IrSender.sendNEC(0x04, 0x02, 0); delay(40); IrSender.sendNEC(0x7D02, 0x0C, 0);
        break;
      case 3:
        IrSender.sendNEC(0x0586, 0x0D, 0); delay(40); IrSender.sendNEC(0x4, 0x3, 0); delay(40);
        IrSender.sendRC6(0x0, 0x11, 0); delay(40); IrSender.sendSamsung(0x7, 0x0B, 0); delay(40);
        IrSender.sendSony(0x01, 0x13, 2, 12); delay(40); IrSender.sendNEC(0x02, 0x1E, 0); delay(40);
        IrSender.sendNEC(0xC7EA, 0x10, 0); delay(40); IrSender.sendNEC(0x0040, 0x1E, 0); delay(40);
        IrSender.sendNEC(0x04, 0x03, 0); delay(40); IrSender.sendNEC(0x7D02, 0x19, 0);
        break;
      case 4: 
        IrSender.sendNEC(0x0586, 0x42, 0); delay(40); IrSender.sendNEC(0x4, 0x0, 0); delay(40);
        IrSender.sendRC6(0x0, 0x4C, 0); delay(40); IrSender.sendSamsung(0x7, 0x60, 0); delay(40);
        IrSender.sendSamsung(0x7, 0x12, 0); delay(40); IrSender.sendNEC(0x04, 0x56, 0); delay(40);
        IrSender.sendSony(0x01, 0x74, 2, 12); delay(40); IrSender.sendSony(0x01, 0x10, 2, 12); delay(40);
        IrSender.sendNEC(0x04, 0x45, 0); delay(40); IrSender.sendNEC(0xC7EA, 0x19, 0); delay(40);
        IrSender.sendNEC(0x7D02, 0x0F, 0); delay(40); IrSender.sendNEC(0x7F00, 0x5E, 0); delay(40);
        IrSender.sendNEC(0x80, 0x01, 0);
        break;
      case 5: 
        IrSender.sendNEC(0x0586, 0x43, 0); delay(40); IrSender.sendNEC(0x4, 0x1, 0); delay(40);
        IrSender.sendRC6(0x0, 0x4D, 0); delay(40); IrSender.sendSamsung(0x7, 0x61, 0); delay(40);
        IrSender.sendSamsung(0x7, 0x10, 0); delay(40); IrSender.sendNEC(0x04, 0x57, 0); delay(40);
        IrSender.sendSony(0x01, 0x75, 2, 12); delay(40); IrSender.sendSony(0x01, 0x11, 2, 12); delay(40);
        IrSender.sendNEC(0x04, 0x46, 0); delay(40); IrSender.sendNEC(0xC7EA, 0x33, 0); delay(40);
        IrSender.sendNEC(0x7D02, 0x5A, 0); delay(40); IrSender.sendNEC(0x7F00, 0x56, 0); delay(40);
        IrSender.sendNEC(0x80, 0x03, 0);
        break;
    }
  }
  else if (currentState == AC_REMOTE_UI) {
    display.println(""); display.display();
    switch (selectedIndex) {
      case 0: 
        IrSender.sendNEC(0x0, 0x88, 0); delay(40); IrSender.sendNEC(0x01, 0x03, 0); delay(40);
        IrSender.sendNEC(0xFF01, 0x12, 0); delay(40); IrSender.sendNEC(0x6681, 0x81, 0);
        break;
      case 1: 
        IrSender.sendNEC(0x0, 0x94, 0); delay(40); IrSender.sendNEC(0x01, 0x0B, 0); delay(40);
        IrSender.sendNEC(0xFF01, 0x0A, 0); delay(40); IrSender.sendNEC(0x6681, 0x82, 0);
        break;
      case 2:
        IrSender.sendNEC(0x0, 0x8C, 0); delay(40); IrSender.sendNEC(0x01, 0x0B, 0); delay(40);
        IrSender.sendNEC(0xFF01, 0x13, 0); delay(40); IrSender.sendNEC(0x6681, 0x8A, 0);
        break;
      case 3:
        IrSender.sendNEC(0x0, 0x90, 0); delay(40); IrSender.sendNEC(0x01, 0x07, 0); delay(40);
        IrSender.sendNEC(0xFF01, 0x1A, 0); delay(40); IrSender.sendNEC(0xFF01, 0x0E, 0); delay(40);
        IrSender.sendNEC(0x6681, 0x85, 0); delay(40); IrSender.sendNEC(0x6681, 0x99, 0);
        break;
    }
  }
  else if (currentState == Audio_REMOTE_UI) {
    display.println(""); display.display();
    switch (selectedIndex) {
      case 0: 
        IrSender.sendNEC(0x6CD2, 0xCB, 0); delay(40); IrSender.sendNEC(0x04D2, 0x47, 0); delay(40);
        IrSender.sendNEC(0x03D2, 0x04, 0); delay(40); IrSender.sendSony(0x01, 0x15, 2, 15); delay(40);
        IrSender.sendSamsung(0x2D, 0x30, 0); delay(40); IrSender.sendNEC(0xB545, 0xC0, 0);
        break;
      case 1: 
        IrSender.sendNEC(0x0, 0x94, 0); delay(40); IrSender.sendNEC(0x01, 0x0B, 0); delay(40);
        IrSender.sendNEC(0xFF01, 0x0A, 0); delay(40); IrSender.sendNEC(0x6681, 0x82, 0); delay(40);
        IrSender.sendSamsung(0x2D, 0x67, 0); delay(40); IrSender.sendNEC(0xB545, 0x84, 0);
        break;
      case 2:
        IrSender.sendNEC(0x0, 0x8C, 0); delay(40); IrSender.sendNEC(0x01, 0x0B, 0); delay(40);
        IrSender.sendNEC(0xFF01, 0x13, 0); delay(40); IrSender.sendNEC(0x6681, 0x8A, 0);
        break;
      case 3:
        IrSender.sendNEC(0x0, 0x90, 0); delay(40); IrSender.sendNEC(0x01, 0x07, 0); delay(40);
        IrSender.sendNEC(0xFF01, 0x1A, 0); delay(40); IrSender.sendNEC(0xFF01, 0x0E, 0); delay(40);
        IrSender.sendNEC(0x6681, 0x85, 0); delay(40); IrSender.sendNEC(0x6681, 0x99, 0);
        break;
    }
  }
  else if (currentState == Epson_REMOTE_UI) {
    display.println(""); display.display();
    switch (selectedIndex) {
      case 0:
        IrSender.sendRaw(rawData_EPSON_Power, sizeof(rawData_EPSON_Power) / sizeof(rawData_EPSON_Power[0]), 38);
        break;
      case 1: 
        IrSender.sendRaw(rawData_EPSON_OFF, sizeof(rawData_EPSON_OFF) / sizeof(rawData_EPSON_OFF[0]), 38);
        break;
      case 2:
        IrSender.sendRaw(rawData_EPSON_MENU, sizeof(rawData_EPSON_MENU) / sizeof(rawData_EPSON_MENU[0]), 38);
        break;
    }
  }
  else if (currentState == IR_UNIVERSAL_MENU) {
    display.println(univMenu[selectedIndex]); display.display();
    switch (selectedIndex) {
      case 0:
        switchMenu(TV_REMOTE_UI);
        break;
      case 1:
        switchMenu(AC_REMOTE_UI);
        break;
      case 2:
        switchMenu(Audio_REMOTE_UI);
        break;
      case 3:
        IrSender.sendSony(0xD4, 0x15, 2, 15);
        IrSender.sendSony(0x6A15, 15, 2);
        break;
      case 4:
        //IrSender.sendNEC(0x8355, 0x906F, 0); delay(40); IrSender.sendRaw(rawData3, sizeof(rawData3) / sizeof(rawData3[0]), 38); delay(40);
        //IrSender.sendRaw(rawData4, sizeof(rawData4) / sizeof(rawData4[0]), 38); delay(40); IrSender.sendRaw(rawData5, sizeof(rawData5) / sizeof(rawData5[0]), 38); delay(60);
        //IrSender.sendNEC(0x8355, 0x906F, 0); delay(40); IrSender.sendRaw(rawData3, sizeof(rawData3) / sizeof(rawData3[0]), 38); delay(40);
        //IrSender.sendRaw(rawData4, sizeof(rawData4) / sizeof(rawData4[0]), 38); delay(40); IrSender.sendRaw(rawData5, sizeof(rawData5) / sizeof(rawData5[0]), 38); delay(40);
        //IrSender.sendRaw(rawData17, sizeof(rawData17) / sizeof(rawData17[0]), 38); delay(40); IrSender.sendRaw(rawData18, sizeof(rawData18) / sizeof(rawData18[0]), 38); delay(40);
        //IrSender.sendRaw(rawData17, sizeof(rawData17) / sizeof(rawData17[0]), 38); delay(40); IrSender.sendRaw(rawData18, sizeof(rawData18) / sizeof(rawData18[0]), 38);
        switchMenu(Epson_REMOTE_UI);
        break;
      case 5:
        IrSender.sendRaw(rawData6, sizeof(rawData6) / sizeof(rawData6[0]), 38); delay(40); IrSender.sendNEC(0x08, 0x0B, 0); delay(40);
        IrSender.sendNEC(0x0813, 0x8778, 0); delay(40); IrSender.sendRaw(rawData7, sizeof(rawData7) / sizeof(rawData7[0]), 38); delay(40);
        IrSender.sendNEC(0x02, 0x1D, 0); delay(40); IrSender.sendRaw(rawData8, sizeof(rawData8) / sizeof(rawData8[0]), 38); delay(40);
        IrSender.sendRaw(rawData9, sizeof(rawData9) / sizeof(rawData9[0]), 38); delay(40); IrSender.sendRaw(rawData10, sizeof(rawData10) / sizeof(rawData10[0]), 38); delay(40);
        IrSender.sendRaw(rawData11, sizeof(rawData11) / sizeof(rawData11[0]), 38); delay(40); IrSender.sendNEC(0x83F4, 0x4FB0, 0); delay(40);
        IrSender.sendNEC(0x8019, 0x10EF, 0); delay(40); IrSender.sendNEC(0x80, 0x51, 0); delay(40); IrSender.sendNEC(0x4040, 0x0A, 0); delay(40);
        IrSender.sendNEC(0x0030, 0x4EB1, 0); delay(40); IrSender.sendRaw(rawData12, sizeof(rawData12) / sizeof(rawData12[0]), 38); delay(40);
        IrSender.sendRaw(rawData13, sizeof(rawData13) / sizeof(rawData13[0]), 38); delay(40); IrSender.sendRaw(rawData14, sizeof(rawData14) / sizeof(rawData14[0]), 38); delay(40);
        IrSender.sendRaw(rawData14, sizeof(rawData14) / sizeof(rawData14[0]), 38); delay(40); IrSender.sendRaw(rawData15, sizeof(rawData15) / sizeof(rawData15[0]), 38); delay(40);
        IrSender.sendRaw(rawData16, sizeof(rawData16) / sizeof(rawData16[0]), 38); break;
      case 6:
        IrSender.sendNEC(0xD880, 0xD02F, 0); delay(40); IrSender.sendNEC(0x80D8, 0x64, 0); delay(40); IrSender.sendNEC(0x80D8, 0x6F, 0); break;
      case 7:
        IrSender.sendNEC(0x0, 0x40, 0); delay(40); IrSender.sendNEC(0x0, 0x47, 0); delay(40); IrSender.sendNEC(0x00EF, 0x01, 0); break;
      case 8:
        IrSender.sendNEC(0xA0BA, 0x4C, 0); delay(40); IrSender.sendNEC(0x35, 0x09, 0); delay(40); IrSender.sendNEC(0x8322, 0x08, 0); delay(40);
        IrSender.sendNEC(0x80, 0x1E, 0); delay(40); IrSender.sendSony(0x01, 0x0F, 2, 15); delay(40); IrSender.sendSony(0x01, 0x15, 2); delay(40);
        IrSender.sendNEC(0x0, 0x40, 0); delay(40); IrSender.sendNEC(0x7E, 0x2A, 0); break;
      case 9:
        IrSender.sendNEC(0xEE87, 0x028E, 0); delay(40); IrSender.sendNEC(0x0586, 0xF00F, 0); delay(40); IrSender.sendNEC(0xC2EA, 0x03, 0); delay(40);
        IrSender.sendNEC(0xEAC7, 0x17, 0); break;
    }
  }
  delay(600);
}

void moveSelection(int direction, int limit) {
  if (currentState == WLAN_PASSWORD_ENTRY) {
    wlanCharIndex = (wlanCharIndex + direction + wlanCharsetLen) % wlanCharsetLen;
  }
  else if (currentState == TV_REMOTE_UI || currentState == AC_REMOTE_UI || currentState == Audio_REMOTE_UI || currentState == Epson_REMOTE_UI) {
    selectedIndex += direction; 
    if (selectedIndex >= limit) selectedIndex = 0;
    if (selectedIndex < 0) selectedIndex = limit - 1;
  }
  else {
    selectedIndex -= direction; 
    if (selectedIndex >= limit) selectedIndex = 0;
    if (selectedIndex < 0) selectedIndex = limit - 1;
  }
}

void handleMenu() {
  bool currentUpState = digitalRead(UpbuttonPin);
  bool currentDownState = digitalRead(DownbuttonPin);
  bool currentSubmitState = digitalRead(SubmitbuttonPin);
  bool currentRightState = digitalRead(RightbuttonPin);
  bool currentLeftState = digitalRead(LeftbuttonPin);
  bool menuChanged = false;
  int currentLimit = 0;

  if (currentState == MAIN_MENU) currentLimit = MAIN_ITEMS;
  else if (currentState == SETTINGS_MENU) currentLimit = SETTINGS_ITEMS;
  else if (currentState == WLAN_MENU) currentLimit = WLAN_ITEMS;
  else if (currentState == WLAN_SCAN_LIST) currentLimit = wlanScanCount;
  else if (currentState == IR_MENU) currentLimit = IR_ITEMS;
  else if (currentState == IR_SAVED_MENU) currentLimit = SAVED_ITEMS;
  else if (currentState == IR_UNIVERSAL_MENU) currentLimit = UNIV_ITEMS;
  else if (currentState == GAMES_MENU) currentLimit = GAMES_ITEMS;
  else if (currentState == BLUE_MENU) currentLimit = Blue_ITEMS;
  else if (currentState == SPAM_MENU) currentLimit = SPAM_ITEMS;
  else if (currentState == WLAN_TOOLS_MENU) currentLimit = WLAN_TOOLS_ITEMS;
  else if (currentState == WLAN_SCANNING || currentState == DEAUTH_SCANNING) currentLimit = 0;
  else if (currentState == DEAUTH_LIST) currentLimit = deauthRunning ? 0 : networkCount + 1;
  else if (currentState == DEAUTH_CLIENTS) currentLimit = deauthRunning ? 0 : clientCount + 2;
  else if (currentState == SNIFFER_UI) currentLimit = 0;
  else if (currentState == LINKBYPASS_UI) currentLimit = 0;
  else if (currentState == EVIL_TWIN_SELECT) currentLimit = networkCount + 1;
  else if (currentState == EVIL_TWIN_UI) currentLimit = 0;
  else if (currentState == BLE_SCAN) currentLimit = bleScanCount + (bleScanCount > 0 ? 1 : 0);
  else if (currentState == BLE_DEVICE_DETAIL) currentLimit = 0;
  else if (currentState == TV_REMOTE_UI) currentLimit = 6;
  else if (currentState == AC_REMOTE_UI) currentLimit = 4;
  else if (currentState == Audio_REMOTE_UI) currentLimit = 6;
  else if (currentState == Epson_REMOTE_UI) currentLimit = 3;

  if (lastRightState == HIGH && currentRightState == LOW) {
    if (currentState == WLAN_PASSWORD_ENTRY) {
      if (connectPassword.length() < 32) {
        connectPassword += wlanCharset[wlanCharIndex];
      }
    }
    else if (currentState == DEAUTH_LIST && !deauthRunning) {
      if (selectedIndex < networkCount) {
        toggleJamSelect(selectedIndex);
      }
    }
    menuChanged = true;
  }

  if (lastUpState == HIGH && currentUpState == LOW) {
    if (currentState == WLAN_PASSWORD_ENTRY) {
      wlanCharIndex = (wlanCharIndex + 1) % wlanCharsetLen;
    }
    else if (currentState == SNIFFER_UI) {
      snifferAutoHop = false;
      setSnifferChannel(snifferChannel + 1);
    }
    else if (currentState == EVIL_TWIN_UI) {           // Login-Liste blaettern
      etViewPage = (etViewPage <= 0) ? (etLoginPages() - 1) : etViewPage - 1;
    }
    else if (currentState == TV_REMOTE_UI || currentState == AC_REMOTE_UI || currentState == Audio_REMOTE_UI || currentState == Epson_REMOTE_UI) {
      selectedIndex++; if (selectedIndex >= currentLimit) selectedIndex = 0;
    } else if (currentLimit > 0) {
      bool noWrap = (currentState == WLAN_SCAN_LIST || currentState == DEAUTH_LIST ||
                     currentState == DEAUTH_CLIENTS || currentState == BLE_SCAN);
      if (noWrap) {
        if (selectedIndex > 0) selectedIndex--;
      } else {
        selectedIndex--; if (selectedIndex < 0) selectedIndex = currentLimit - 1;
      }
    } else if (currentState == BLE_DEVICE_DETAIL) {
      bleDetailLine--; if (bleDetailLine < 0) bleDetailLine = 0;
    }
    menuChanged = true;
  }
  if (lastDownState == HIGH && currentDownState == LOW) {
    if (currentState == WLAN_PASSWORD_ENTRY) {
      wlanCharIndex = (wlanCharIndex - 1 + wlanCharsetLen) % wlanCharsetLen;
    }
    else if (currentState == SNIFFER_UI) {
      snifferAutoHop = false;
      setSnifferChannel(snifferChannel - 1);
    }
    else if (currentState == EVIL_TWIN_UI) {           // Login-Liste blaettern
      etViewPage = (etViewPage + 1) % etLoginPages();
    }
    else if (currentState == TV_REMOTE_UI || currentState == AC_REMOTE_UI || currentState == Audio_REMOTE_UI || currentState == Epson_REMOTE_UI) {
      selectedIndex--; if (selectedIndex < 0) selectedIndex = currentLimit - 1;
    } else if (currentLimit > 0) {
      bool noWrap = (currentState == WLAN_SCAN_LIST || currentState == DEAUTH_LIST ||
                     currentState == DEAUTH_CLIENTS || currentState == BLE_SCAN);
      if (noWrap) {
        if (selectedIndex < currentLimit - 1) selectedIndex++;
      } else {
        selectedIndex++; if (selectedIndex >= currentLimit) selectedIndex = 0;
      }
    } else if (currentState == BLE_DEVICE_DETAIL) {
      if (bleDetailLine < bleDevices[bleDetailDevice].lineCount - 1) bleDetailLine++;
    }
    menuChanged = true;
  }
  if (lastLeftState == HIGH && currentLeftState == LOW) {
    if (currentState == WLAN_PASSWORD_ENTRY) {
      if (connectPassword.length() > 0) connectPassword.remove(connectPassword.length() - 1);
    }
    else if (currentState == IR_MENU || currentState == GAMES_MENU) switchMenu(MAIN_MENU);
    else if (currentState == IR_SAVED_MENU || currentState == IR_UNIVERSAL_MENU) switchMenu(IR_MENU);
    else if (currentState == WLAN_TOOLS_MENU) switchMenu(MAIN_MENU);
    else if (currentState == BLUE_MENU || currentState == SETTINGS_MENU) switchMenu(MAIN_MENU);
    else if (currentState == SPAM_MENU) switchMenu(BLUE_MENU);
    else if (currentState == DEAUTH_LIST) { stopDeauth(); switchMenu(WLAN_TOOLS_MENU); }
    else if (currentState == DEAUTH_CLIENTS) { stopDeauth(); switchMenu(DEAUTH_LIST); }
    else if (currentState == SNIFFER_UI) { snifferAutoHop = !snifferAutoHop; }
    else if (currentState == LINKBYPASS_UI) switchMenu(WLAN_TOOLS_MENU);
    else if (currentState == EVIL_TWIN_SELECT) switchMenu(WLAN_TOOLS_MENU);
    else if (currentState == EVIL_TWIN_UI) { stopEvilTwin(); switchMenu(WLAN_TOOLS_MENU); }
    else if (currentState == BLE_DEVICE_DETAIL) switchMenu(BLE_SCAN);
    else if (currentState == BLE_SCAN) { stopBLEScan(); switchMenu(BLUE_MENU); }
    else if (currentState == TV_REMOTE_UI || currentState == AC_REMOTE_UI || currentState == Audio_REMOTE_UI || currentState == Epson_REMOTE_UI) switchMenu(IR_UNIVERSAL_MENU);
    else if (currentState == BLE_SNIFFER_UI) { stopBLESniffer(); switchMenu(BLUE_MENU); }
    else if (currentState == SETTINGS_MENU) switchMenu(MAIN_MENU);
    else if (currentState == ABOUT_UI) switchMenu(SETTINGS_MENU); 
    menuChanged = true;
  }
  if (lastSubmitState == HIGH && currentSubmitState == LOW) {
    if (currentState == MAIN_MENU) {
      if (selectedIndex == 0) switchMenu(IR_MENU);
      else if (selectedIndex == 1) switchMenu(GAMES_MENU);
      else if (selectedIndex == 2) switchMenu(BLUE_MENU);
      else if (selectedIndex == 3) switchMenu(WLAN_TOOLS_MENU);
      else if (selectedIndex == 4) switchMenu(SETTINGS_MENU);
    }
    else if (currentState == IR_MENU) {
      if (selectedIndex == 0) switchMenu(IR_SAVED_MENU);
      else if (selectedIndex == 1) switchMenu(IR_UNIVERSAL_MENU);
      else if (selectedIndex == 2) switchMenu(MAIN_MENU);
    }
    else if (currentState == BLUE_MENU) {
      if (selectedIndex == 0) switchMenu(SPAM_MENU);
      else if (selectedIndex == 1) startBLEScan();
      else if (selectedIndex == 2) startBLESniffer();
      else if (selectedIndex == 3) switchMenu(MAIN_MENU);
    }
    else if (currentState == BLE_SCAN) {
      if (bleScanCount == 0 || selectedIndex >= bleScanCount) switchMenu(BLUE_MENU);
      else {
        bleDetailDevice = selectedIndex;
        bleDetailLine = 0;
        switchMenu(BLE_DEVICE_DETAIL);
      }
    }
    else if (currentState == SPAM_MENU) {
      if (selectedIndex == 0) BLEJammerspam();
      else if (selectedIndex == 1) PairWatchSpam();
      else if (selectedIndex == 2) PairAppleAirpodsspam();
      else if (selectedIndex == 3) PairApplespam();
      else if (selectedIndex == 4) Windowsspam();
      else if (selectedIndex == 5) switchMenu(BLUE_MENU);
    }
    else if (currentState == IR_SAVED_MENU) {
      if (selectedIndex == 5) switchMenu(IR_MENU); else sendSelectedSignal(); 
    }
    else if (currentState == IR_UNIVERSAL_MENU) {
      if (selectedIndex == 10) switchMenu(IR_MENU); 
      else if (selectedIndex == 0) switchMenu(TV_REMOTE_UI);
      else if (selectedIndex == 1) switchMenu(AC_REMOTE_UI);
      else if (selectedIndex == 2) switchMenu(Audio_REMOTE_UI);
      else if (selectedIndex == 4) switchMenu(Epson_REMOTE_UI);
      else sendSelectedSignal(); 
    }
    else if (currentState == GAMES_MENU) {
      if (selectedIndex == 0) playPingPong();
      else if (selectedIndex == 1) playBlackJack();
      else if (selectedIndex == 2) Raumschiff();
      else if (selectedIndex == 3) playDoodleJump();
      else if (selectedIndex == 4) switchMenu(MAIN_MENU);
    }
    else if (currentState == SETTINGS_MENU) {
      switch (selectedIndex) {
        case 0: 
          brightnessValue = !brightnessValue; 
          display.dim(brightnessValue == 0); 
          preferences.putInt("display", brightnessValue);
          break;
        case 1: utcValue++; if (utcValue > 12) utcValue = -12; break;
        case 2: switchMenu(WLAN_MENU); break;
        case 3: buzzerVol += 25; if (buzzerVol > 100) buzzerVol = 0; break;
        case 4: HardReset(); break;
        case 5: switchMenu(ABOUT_UI); break;
        case 6: switchMenu(MAIN_MENU); break;
      }
    }
    else if (currentState == WLAN_MENU) {
      if (selectedIndex == 0) {
        startWiFiScan();
        switchMenu(WLAN_SCANNING);
        drawMenu();
      }
      else if (selectedIndex == 1) {
        switchMenu(WLAN_STATUS);
      }
      else if (selectedIndex == 2) {
        switchMenu(SETTINGS_MENU);
      }
    }
    else if (currentState == WLAN_SCAN_LIST) {
      if (selectedIndex == wlanScanCount - 1) {
        switchMenu(WLAN_MENU);
      } else {
        connectSSID = WiFi.SSID(selectedIndex);
        connectPassword = "";
        if (selectedIndex < MAX_WLAN_RESULTS && wlanOpen[selectedIndex]) {
          connectToWifi();
        } else {
          wlanCharIndex = 1;
          switchMenu(WLAN_PASSWORD_ENTRY);
        }
      }
    }
    else if (currentState == WLAN_PASSWORD_ENTRY) {
      if (connectPassword.length() >= 8) {
        connectToWifi();
      }
    }
    else if (currentState == WLAN_STATUS) {
      switchMenu(WLAN_MENU);
    }
    else if (currentState == WLAN_TOOLS_MENU) {
      if (selectedIndex == 0) {
        startDeauthScan();
        switchMenu(DEAUTH_SCANNING);
        drawMenu();
      }
      else if (selectedIndex == 1) { startSniffer(); switchMenu(SNIFFER_UI); }
      else if (selectedIndex == 2) {              // Evil Twin
        stopEvilTwin();                           // defensiv: laeuft nichts
        if (networkCount > 0) {
          switchMenu(EVIL_TWIN_SELECT);
        } else {
          etPendingSelect = true;
          startDeauthScan();
          switchMenu(DEAUTH_SCANNING);
          drawMenu();
        }
      }
      else if (selectedIndex == 3) switchMenu(LINKBYPASS_UI);
      else if (selectedIndex == 4) switchMenu(MAIN_MENU);
    }
    else if (currentState == DEAUTH_LIST) {
      if (!deauthRunning && networkCount == 0) {
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(10, 28);
        display.print("Keine Netzwerke!");
        display.setCursor(10, 40);
        display.print("< Back");
        display.display();
      } else {
        if (deauthRunning) { stopDeauth(); switchMenu(WLAN_TOOLS_MENU); }
        else if (selectedIndex == networkCount) { stopDeauth(); switchMenu(WLAN_TOOLS_MENU); }
        else if (jamSelCount > 0 && selectedIndex < networkCount) {
          startDeauthMulti();
          switchMenu(DEAUTH_LIST);
        }
        else { startDeauth(selectedIndex); switchMenu(DEAUTH_CLIENTS); }
      }
    }
    else if (currentState == DEAUTH_CLIENTS) {
      if (deauthRunning) { stopDeauth(); switchMenu(WLAN_TOOLS_MENU); }
      else if (selectedIndex == clientCount + 1) { stopDeauth(); switchMenu(DEAUTH_LIST); }
      else if (selectedIndex == clientCount) { startDeauthAttack(true);  switchMenu(DEAUTH_LIST); }
      else { memcpy(targetClientMAC, clients[selectedIndex].mac, 6);
              startDeauthAttack(false); switchMenu(DEAUTH_LIST); }
    }
    else if (currentState == SNIFFER_UI) { stopSniffer(); switchMenu(WLAN_TOOLS_MENU); }
    else if (currentState == LINKBYPASS_UI) switchMenu(WLAN_TOOLS_MENU);
    else if (currentState == EVIL_TWIN_SELECT) {
      if (networkCount == 0 || selectedIndex == networkCount) {
        switchMenu(WLAN_TOOLS_MENU);
      } else {
        startEvilTwin(selectedIndex);
        if (evilTwinActive) switchMenu(EVIL_TWIN_UI);
      }
    }
    else if (currentState == EVIL_TWIN_UI) { etDeauthEnabled = !etDeauthEnabled; etRequestBurstNow(); }
    else if (currentState == BLE_SNIFFER_UI) { stopBLESniffer(); switchMenu(BLUE_MENU); }
    else if (currentState == BLE_DEVICE_DETAIL) switchMenu(BLE_SCAN);
    else if (currentState == TV_REMOTE_UI || currentState == AC_REMOTE_UI || currentState == Audio_REMOTE_UI || currentState == Epson_REMOTE_UI) {
      sendSelectedSignal();
    }
    menuChanged = true;
  }

  lastUpState = currentUpState; lastDownState = currentDownState;
  lastSubmitState = currentSubmitState; lastLeftState = currentLeftState;
  lastRightState = currentRightState;

  if (menuChanged) drawMenu();
  delay(20);
}
