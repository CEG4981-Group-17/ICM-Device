// CEG4981 TEAM PROJECTS II GROUP 17
// ICM device code

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// reference: https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/
#define SERVICE_UUID        "b3a9b76b-e3cc-46cd-adc7-ceeba9977b0f"
#define LOCK_UUID           "d1dcac5b-8961-4917-ac9d-b59b36351594"

#define MOTOR_ON_TIME 250

#define LOCK_LED_PIN  13
#define MOTOR_IN1     5
#define MOTOR_IN2     15

BLECharacteristic* lock_charact = 0;
bool locked = true;

void setup() {
  Serial.begin(115200);
  Serial.println("ICM booting");

  // setup our pins
  pinMode(LOCK_LED_PIN, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  
  // initialize bluetooth
  /*
  Serial.println("initializing bluetooth service");
  BLEDevice::init("ICM");
  BLEServer* server = BLEDevice::createServer();
  BLEService* service = server->createService(SERVICE_UUID);

  // characteristic is similar to a channel
  lock_charact = service->createCharacteristic(LOCK_UUID,
                              BLECharacteristic::PROPERTY_READ |
                              BLECharacteristic::PROPERTY_WRITE);

  // make our device ready to pair
  service->start();
  BLEAdvertising* advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->setScanResponse(true);
  advertising->setMinPreferred(0x06); // helps with iPhone connections
  advertising->setMaxPreferred(0x12);
  BLEDevice::startAdvertising();
  */

  locked = true; // true at first so locking mechanism is forced to unlock
  setUnlocked();
  Serial.println("ICM finished booting");
}

void loop() {
  /*
  if(recievedUnlock()) {
    setLocked();
  } else if(recievedlock()) {
    setUnlocked();
  }*/

  setLocked();
  delay(2000);
  setUnlocked();
  delay(4000);
  
  // TODO: mail detection
  // TODO: door detection
  // TODO: flag detection
}

bool recievedUnlock() {
  // check if the bluetooth value changed
  return locked && lock_charact->getValue() == "unlocked";
}

bool recievedlock() {
  // check if the bluetooth value changed
  return !locked && lock_charact->getValue() == "locked";
}

void lock_mech_on() {
  digitalWrite(MOTOR_IN1,LOW);
  digitalWrite(MOTOR_IN2,HIGH);
  delay(MOTOR_ON_TIME);
  digitalWrite(MOTOR_IN1,LOW);
  digitalWrite(MOTOR_IN2,LOW);
}

void lock_mech_off() {
  digitalWrite(MOTOR_IN1,HIGH);
  digitalWrite(MOTOR_IN2,LOW);
  delay(MOTOR_ON_TIME);
  digitalWrite(MOTOR_IN1,LOW);
  digitalWrite(MOTOR_IN2,LOW);
}

void lock_LED_on() {
  digitalWrite(LOCK_LED_PIN, HIGH);
}

void lock_LED_off() {
  digitalWrite(LOCK_LED_PIN, LOW);
}

void setLocked() {
  bool prev_locked = locked;
  locked = true;

  //lock_charact->setValue("locked");
  lock_LED_on();
  if(prev_locked != locked) lock_mech_on();
}

void setUnlocked() {
  bool prev_locked = locked;
  locked = false;
  
  //lock_charact->setValue("unlocked");
  lock_LED_off();
  
  if(prev_locked != locked) lock_mech_off();
}
