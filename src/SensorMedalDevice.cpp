#include "SensorMedalDevice.h"

class AdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
private:
    SensorMedalDevice *sensorMedalDevice;
public:
    AdvertisedDeviceCallbacks(SensorMedalDevice *device):BLEAdvertisedDeviceCallbacks(){
        sensorMedalDevice = device;
    }

    void onResult(BLEAdvertisedDevice advertisedDevice) {
        Serial.print("Advertised Device: "); Serial.println(advertisedDevice.toString().c_str());

        //デバイスアドレスが一致するか確認する
        if(advertisedDevice.getAddress().equals(*(sensorMedalDevice->getDeviceAddress())) == false) return;
        
        //接続対象のデバイスが見つかったらスキャンを停止
        advertisedDevice.getScan()->stop();
    }
};

SensorMedalDevice::SensorMedalDevice(std::string stringAddress) {
    pDeviceAddress = new BLEAddress(stringAddress);
    callbacks = new AdvertisedDeviceCallbacks(this);
}

SensorMedalDevice::~SensorMedalDevice() {

}

void SensorMedalDevice::init(){
    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan(); //create new scan
    pBLEScan->setAdvertisedDeviceCallbacks(callbacks);
    pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
}

BLEAddress *SensorMedalDevice::getDeviceAddress(){
    return pDeviceAddress;
}

BLEScanResults SensorMedalDevice::scanStart(uint32_t duration){
    return pBLEScan->start(duration);
}

//見つけたセンサーに接続する
bool SensorMedalDevice::connect(){
    Serial.println("connect");

    //接続してみる
    BLEClient *pClient = BLEDevice::createClient();
    Serial.print("pDeviceAddress: "); Serial.println(pDeviceAddress->toString().c_str());

    if ( pClient->connect(*pDeviceAddress) == false){
        Serial.print("Failed to connect");
        return false;
    }
    Serial.println("- connect to Success");

    //サービスUUIDを確認
    BLERemoteService* pRemoteService = pClient->getService( BLEUUID(SENSOR_MEDAL_SERVICE_UUID) );
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service");
      return false;
    }
    Serial.println("- Found our service");
    Serial.println(pRemoteService->toString().c_str());

    //キャラクタリスティックがあるか確認
    pRemoteCharacteristic = pRemoteService->getCharacteristic( BLEUUID(SENSOR_MEDAL_CHARACTERISTICS_UUID) );
    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic");
      return false;
    }
    Serial.println("- Found our characteristic");
    Serial.println(pRemoteCharacteristic->toString().c_str());

    //センサーデータが更新されると呼び出される
    auto notifyCallback = [&](
			BLERemoteCharacteristic* pBLERemoteCharacteristic,
			uint8_t*                 pData,
			size_t                   length,
			bool                     isNotify){
                Serial.print("Notify callback for characteristic ");
                Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
                Serial.print(" of data length ");
                Serial.println(length);

                //TODO センサーデータを読み出して SensorMedalData コールバックする
                //sensorMedalDevice->onData(&advertisedDevice,new SensorMedalData());
            };
    pRemoteCharacteristic->registerForNotify(notifyCallback);

    //CCCD(Client Characteristic Configuration Descriptor)
    BLERemoteDescriptor *p2902 = pRemoteCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902));
    if (p2902 == nullptr) {
      Serial.print("Failed to find our descriptor");
      return false;
    }
    Serial.println("- Found our descriptor");
    const uint8_t v[]={0x1,0x0};
    p2902->writeValue((uint8_t*)v,2,true);
}

void SensorMedalDevice::loop(){

}