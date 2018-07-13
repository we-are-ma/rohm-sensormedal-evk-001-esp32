<font color="OrangeRed">SensorMedalのデータのNotification がうまく受信できていませんので未完成のサンプルです</font>

# ROHM-sensormedal-evk-001-esp32
ESP32 Arduino で SensorMedal-evk-001 の値を取得する為のサンプル

#必要環境
VScode
PlatformIO 拡張

# ビルド方法
```
git clone git@github.com:we-are-ma/rohm-sensormedal-evk-001-esp32.git
cd rohm-sensormedal-evk-001-esp32
code .
```

# デバイス名やサービスUUIDの情報
## デバイス名
ROHM RAW

## Service UUID, Characteristic UUID
| Service UUID | Characteristic UUID | R/W,Notification | 内容 |
|:-----------|:------------|:------------|:------------|
| 0179bbc0-0000-0100-8000-00805f9b34fb |  | SensorMedal-EVK-001サービス |
|  | 0179bbc1-0000-0100-8000-00805f9b34fb | Read ||
|  | 0179bbc2-0000-0100-8000-00805f9b34fb | Write ||
|  | 0179bbc3-0000-0100-8000-00805f9b34fb | Notification | 加速度,地磁気,角速度,気圧 |
|  | 0179bbc4-0000-0100-8000-00805f9b34fb | --- ||

# 参考
[ESP32 BLE Arduino](https://platformio.org/lib/show/1841/ESP32%20BLE%20Arduino)

[ESP32_BLE_Arduino BLE_scan](https://github.com/nkolban/ESP32_BLE_Arduino/blob/master/examples/BLE_scan/BLE_scan.ino)

[ESP32_BLE_Arduino BLE_client](https://github.com/nkolban/ESP32_BLE_Arduino/blob/master/examples/BLE_client/BLE_client.ino)

