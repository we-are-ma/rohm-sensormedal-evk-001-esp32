#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLE2902.h>

#ifndef SENSOR_MEDAL_DEVICE_H_
#define SENSOR_MEDAL_DEVICE_H_

#define SENSOR_MEDAL_SERVICE_UUID "0179bbc0-0000-0100-8000-00805f9b34fb"
#define SENSOR_MEDAL_CHARACTERISTICS_UUID "0179bbc3-0000-0100-8000-00805f9b34fb"

//Client Characteristic Configulation Descriptor
#define SENSOR_MEDAL_CCCD "00002902-0000-1000-8000-00805f9b34fb"

class SensorMedalData {

};

class SensorMedalDevice{
public:
	SensorMedalDevice(std::string stringAddress);
	virtual ~SensorMedalDevice();
    void init();
	void loop();
	BLEScanResults scanStart(uint32_t duration);
	virtual void onData(BLEAdvertisedDevice *pAdvertisedDevice,SensorMedalData *data) = 0;
	bool connect();

	BLEAddress *getDeviceAddress();
private:
	BLEAddress *pDeviceAddress;
	BLEScan* pBLEScan;    
	BLERemoteCharacteristic* pRemoteCharacteristic;
    BLEAdvertisedDeviceCallbacks *callbacks;
};

#endif
