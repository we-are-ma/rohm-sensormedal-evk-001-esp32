/** 周辺のBLEをスキャンして
 * 
 * 参考 ESP32_BLE_Arduino BLE_scan.ino
 * https://github.com/nkolban/ESP32_BLE_Arduino/blob/master/examples/BLE_scan/BLE_scan.ino
 * 
 * */
#include <Arduino.h>
#include <BLEDevice.h>
#include "SensorMedalDevice.h"

#define SCAN_TIME  60 // seconds

#define SERIAL_PRINT

void log(const char* v){
#ifdef SERIAL_PRINT
    Serial.println(v);
#endif
}

class MySensorMedalDevice: public SensorMedalDevice {
public:
    MySensorMedalDevice(std::string stringAddress):SensorMedalDevice(stringAddress){

    }

    void onData(BLEAdvertisedDevice *advertisedDevice,SensorMedalData *data){
        log("Advertised Device:");
        log(advertisedDevice->toString().c_str());
    }
};

MySensorMedalDevice *sensorMedalDevice = new MySensorMedalDevice("c1:d4:48:18:e9:33");

void setup() {
    Serial.begin(115200);
    log("ESP32 BLE Scanner");
    delay(1000);

    //BLE 初期設定
    log("BLEDevice init");    
    sensorMedalDevice->init();
    delay(1000);
    
    //周辺の BLEデバイスを SCAN_TIME 秒間だけ スキャン する
    log("BLEScan start");
    BLEScanResults foundDevices = sensorMedalDevice->scanStart(SCAN_TIME);
    log("Scan done!");
    delay(1000);
    if(foundDevices.getCount() > 0){
        sensorMedalDevice->connect();
    }
}

void loop() {
    //FreeRTOS::sleep(5000);
    sensorMedalDevice->loop();
    delay(1000);
}