#include <ArduinoBLE.h>

const int soundSensorPin = A2; // Assign to pin A2
const int threshold = 150;     // Threshold value for sound level

BLEService soundService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLEIntCharacteristic soundCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

void setup() {
  Serial.begin(9600); // Begin Serial Communication

  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  // Set advertised local name and service UUID
  BLE.setLocalName("SoundSensor");
  BLE.setAdvertisedService(soundService);

  // Add the characteristic to the service
  soundService.addCharacteristic(soundCharacteristic);

  // Add the service
  BLE.addService(soundService);

  // Start advertising
  BLE.advertise();

  Serial.println("BLE Peripheral device started, waiting for connections...");
}

void loop() {
  // Read sound sensor
  int soundValue = readSoundSensor();

  // Print sound value
  Serial.println(soundValue);

  // Update BLE characteristic
  soundCharacteristic.writeValue(soundValue);

  // Print visualization if sound value exceeds threshold
  if (soundValue > threshold) {
    printSoundVisualization();
  }

  delay(50); // Short delay between readings
}

int readSoundSensor() {
  int soundValue = 0;
  for (int i = 0; i < 32; i++) {
    soundValue += analogRead(soundSensorPin);
  }
  return soundValue >> 5; // Bitshift operation
}

void printSoundVisualization() {
  Serial.println("         ||        ");
  Serial.println("       ||||||      ");
  Serial.println("     |||||||||     ");
  Serial.println("   |||||||||||||   ");
  Serial.println(" ||||||||||||||||| ");
  Serial.println("   |||||||||||||   ");
  Serial.println("     |||||||||     ");
  Serial.println("       ||||||      ");
  Serial.println("         ||        ");
}