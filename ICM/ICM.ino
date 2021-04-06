// reference: https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/
#define SERVICE_UUID        "b3a9b76b-e3cc-46cd-adc7-ceeba9977b0f"
#define CHARACTERISTIC_UUID "d1dcac5b-8961-4917-ac9d-b59b36351594"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

void setup() {
  Serial.begin(115200);
  Serial.println("ICM booting");
  Serial.println("initializing bluetooth service");
  BLEDevice::init("ICM");
  BLEServer* server = BLEDevice::createServer();
  BLEService* service = server->createService(SERVICE_UUID);
  BLECharacteristic* characteristic = service->createCharacteristic(
                              CHARACTERISTIC_UUID,
                              BLECharacteristic::PROPERTY_READ |
                              BLECharacteristic::PROPERTY_WRITE);
  characteristic->setValue("hello world!");
  service->start();
  BLEAdvertising* advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->setScanResponse(true);
  advertising->setMinPreferred(0x06); // helps with iPhone connections
  advertising->setMaxPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("ICM finished booting");
}

void loop() {
  delay(2000);
}
