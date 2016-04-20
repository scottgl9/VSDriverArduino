#include <CurieIMU.h>

void setup() {
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device
  Serial.println("Initializing IMU device...");
  CurieIMU.begin();

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
}

void loop() {
  int axRaw, ayRaw, azRaw;         // raw accelerometer values
  float ax, ay, az;

  // read raw accelerometer measurements from device
  CurieIMU.readAccelerometer(axRaw, ayRaw, azRaw);

  // convert the raw accelerometer data to G's
  //ax = convertRawAcceleration(axRaw);
  //ay = convertRawAcceleration(ayRaw);
  //az = convertRawAcceleration(azRaw);

  // display accelerometer x/y/z values
  if (Serial.available() > 0) {
    int val = Serial.read();
    if (val == 's') { // if incoming serial is "s"
      Serial.print(axRaw);
      Serial.print(","); // print comma so values can be parsed
      Serial.print(ayRaw);
      Serial.print(","); // print comma so values can be parsed
      Serial.println(azRaw);
    }
  }
}

float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  
  float a = (aRaw * 2.0) / 32768.0;

  return a;
}

