#pragma once

void switchMenu(MenuState newState) {
  currentState = newState; selectedIndex = 0; scrollOffset = 0;
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

void drawMenu() {
  display.clearDisplay();
  String* currentArray;
  int currentSize = 0;
  
  if (currentState == MAIN_MENU) { currentArray = mainMenu; currentSize = MAIN_ITEMS; }
  else if (currentState == IR_MENU) { currentArray = irMenu; currentSize = IR_ITEMS; }
  else if (currentState == IR_SAVED_MENU) { currentArray = savedMenu; currentSize = SAVED_ITEMS; }
  else if (currentState == IR_UNIVERSAL_MENU) { currentArray = univMenu; currentSize = UNIV_ITEMS; }
  else if (currentState == GAMES_MENU) { currentArray = gamesMenu; currentSize = GAMES_ITEMS;}
  else if (currentState == BLUE_MENU) { currentArray = BlueMenu; currentSize = Blue_ITEMS;}
  else if (currentState == SETTINGS_MENU) { currentArray = settingsMenu; currentSize = SETTINGS_MENU; }
  else if (currentState == WLAN_MENU) { currentArray = wlanMenu; currentSize = WLAN_ITEMS; }
  else if (currentState == BadUSB_MENU) { currentArray = BadusbMenu; currentSize = BadUSB_ITEMS; }
  else if (currentState == USB_MENU) { currentArray = UsbMenu; currentSize = USB_ITEMS; }
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
        IrSender.sendRaw(rawData_EPSON_ON, sizeof(rawData_EPSON_ON) / sizeof(rawData_EPSON_ON[0]), 38);
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

void handleMenu() {
    bool currentUpState = digitalRead(UpbuttonPin);
    bool currentDownState = digitalRead(DownbuttonPin);
    bool currentSubmitState = digitalRead(SubmitbuttonPin);
    bool currentLeftState = digitalRead(rootPin);
    bool menuChanged = false;
    int currentLimit = 0;

    if (currentState == MAIN_MENU) currentLimit = MAIN_ITEMS;
    else if (currentState == SETTINGS_MENU) currentLimit = SETTINGS_ITEMS;
    else if (currentState == WLAN_MENU) currentLimit = WLAN_ITEMS;
    else if (currentState == BadUSB_MENU) currentLimit = BadUSB_ITEMS;
    else if (currentState == USB_MENU) currentLimit = USB_ITEMS;
    else if (currentState == IR_MENU) currentLimit = IR_ITEMS;
    else if (currentState == IR_SAVED_MENU) currentLimit = SAVED_ITEMS;
    else if (currentState == IR_UNIVERSAL_MENU) currentLimit = UNIV_ITEMS;
    else if (currentState == GAMES_MENU) currentLimit = GAMES_ITEMS;
    else if (currentState == BLUE_MENU) currentLimit = Blue_ITEMS;
    else if (currentState == TV_REMOTE_UI) currentLimit = 6;
    else if (currentState == AC_REMOTE_UI) currentLimit = 4;
    else if (currentState == Audio_REMOTE_UI) currentLimit = 6;
    else if (currentState == Epson_REMOTE_UI) currentLimit = 3;

    if (lastUpState == HIGH && currentUpState == LOW) {
      if (currentState == TV_REMOTE_UI || currentState == AC_REMOTE_UI || currentState == Audio_REMOTE_UI || currentState == Epson_REMOTE_UI) {
        selectedIndex++; if (selectedIndex >= currentLimit) selectedIndex = 0;
      } else {
        selectedIndex--; if (selectedIndex < 0) selectedIndex = currentLimit - 1;
      }
      menuChanged = true;
    }
    if (lastDownState == HIGH && currentDownState == LOW) {
      if (currentState == TV_REMOTE_UI || currentState == AC_REMOTE_UI || currentState == Audio_REMOTE_UI || currentState == Epson_REMOTE_UI) {
        selectedIndex--; if (selectedIndex < 0) selectedIndex = currentLimit - 1;
      } else {
        selectedIndex++; if (selectedIndex >= currentLimit) selectedIndex = 0;
      }
      menuChanged = true;
    }
    if (lastLeftState == HIGH && currentLeftState == LOW) {
      if (currentState == IR_MENU || currentState == GAMES_MENU) switchMenu(MAIN_MENU);
      else if (currentState == IR_SAVED_MENU || currentState == IR_UNIVERSAL_MENU) switchMenu(IR_MENU);
      else if (currentState == TV_REMOTE_UI || currentState == AC_REMOTE_UI || currentState == Audio_REMOTE_UI || currentState == Epson_REMOTE_UI) switchMenu(IR_UNIVERSAL_MENU);
      menuChanged = true;
    }
    if (lastSubmitState == HIGH && currentSubmitState == LOW) {
      if (currentState == MAIN_MENU) {
        if (selectedIndex == 0) switchMenu(IR_MENU);
        else if (selectedIndex == 1) switchMenu(BadUSB_MENU);
        else if (selectedIndex == 2) switchMenu(GAMES_MENU);
        else if (selectedIndex == 3) switchMenu(BLUE_MENU);
        else if (selectedIndex == 4) switchMenu(SETTINGS_MENU);
      }
      else if (currentState == IR_MENU) {
        if (selectedIndex == 0) switchMenu(IR_SAVED_MENU);
        else if (selectedIndex == 1) switchMenu(IR_UNIVERSAL_MENU);
        else if (selectedIndex == 2) switchMenu(MAIN_MENU);
      }
      else if (currentState == BLUE_MENU) {
        if (selectedIndex == 0) BLEJammerspam();
        else if (selectedIndex == 1) PairWatchSpam();
        else if (selectedIndex == 2) PairAppleAirpodsspam();
        else if (selectedIndex == 3) PairApplespam();
        else if (selectedIndex == 4) Windowsspam();
        else if (selectedIndex == 5) switchMenu(MAIN_MENU);
      }
      else if (currentState == IR_SAVED_MENU) {
        if (selectedIndex == 5) switchMenu(IR_MENU); else sendSelectedSignal(); 
      }
      else if (currentState == IR_UNIVERSAL_MENU) {
        if (selectedIndex == 11) switchMenu(IR_MENU); 
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
        else if (selectedIndex == 3) playGame_of_life();
        else if (selectedIndex == 4) switchMenu(MAIN_MENU);
      }
      else if (currentState == BadUSB_MENU) {
        if (selectedIndex == 0);
        else if (selectedIndex == 1) switchMenu(USB_MENU);
        else if (selectedIndex == 2) switchMenu(MAIN_MENU);
      }
      else if (currentState == USB_MENU) {
        if (selectedIndex == 0);
        else if (selectedIndex == 1) BadUSB_ShutDown();
        else if (selectedIndex == 2) switchMenu(BadUSB_MENU);
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
          case 4: ESP.restart(); break;
          case 5: switchMenu(MAIN_MENU); break;
        }
      }
      else if (currentState == WLAN_MENU) {
        if (selectedIndex == 0) {
          // Scan starten
          startWiFiScan();
          // Kurze Statusmeldung anzeigen
          display.clearDisplay();
          display.setCursor(10, 30);
          display.print("Scanning...");
          display.display();
          delay(100);
          drawMenu();
        }
        else if (selectedIndex == 1) {
          // Status/Deauth-Auswahl anzeigen
          if (networkCount > 0) {
            // Zeige erstes Netzwerk zum Deauth an
            deauthTargetIndex = 0;
            // Hier kannst du später eine Auswahl einbauen
            startDeauth(deauthTargetIndex);
            display.clearDisplay();
            display.setCursor(10, 20);
            display.print("Deauth: ");
            display.print(scannedNetworks[deauthTargetIndex].ssid.substring(0, 10));
            display.setCursor(10, 35);
            display.print(deauthRunning ? "RUNNING" : "STOPPED");
            display.display();
            delay(1000);
          }
          drawMenu();
        }
        else if (selectedIndex == 2) {
          stopDeauth();
          switchMenu(SETTINGS_MENU);
        }
      }
      else if (currentState == TV_REMOTE_UI || currentState == AC_REMOTE_UI || currentState == Audio_REMOTE_UI || currentState == Epson_REMOTE_UI) {
        sendSelectedSignal();
      }
      menuChanged = true;
    }

    lastUpState = currentUpState; lastDownState = currentDownState;
    lastSubmitState = currentSubmitState; lastLeftState = currentLeftState;

    if (menuChanged) drawMenu();
    delay(20);
}