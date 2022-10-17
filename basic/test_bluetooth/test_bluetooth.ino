#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int ledpin = 18;
void setup() {
  Serial.begin(115200);
  // pinMode(ledpin, OUTPUT);
  SerialBT.begin("esp69"); //Bluetooth device name
}
void loop() {  
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  
  delay(20);
}
