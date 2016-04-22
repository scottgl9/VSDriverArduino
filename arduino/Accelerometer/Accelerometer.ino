#include <CurieIMU.h>

boolean blinkState = false;          // state of the LED
int ax, ay, az;         // accelerometer values
int temp;

void setup() {
  Serial.begin(9600); // initialize Serial communication
  //while (!Serial);    // wait for the serial port to open

  /* Initialise the IMU */
  CurieIMU.begin();
  CurieIMU.attachInterrupt(eventCallback);

  //Serial.print("Starting Acceleration calibration and enabling offset compensation...");
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 0);

  /* Enable Shock Detection */
  //CurieIMU.setDetectionThreshold(CURIE_IMU_MOTION, 500);           // 1.5g = 1500 mg
  //CurieIMU.setDetectionDuration(CURIE_IMU_MOTION, 50);  // 50ms
  //CurieIMU.interrupts(CURIE_IMU_MOTION);
  CurieIMU.setDetectionThreshold(CURIE_IMU_SHOCK, 600); // 1.5g = 1500 mg
  CurieIMU.setDetectionDuration(CURIE_IMU_SHOCK, 25);   // 50ms
  CurieIMU.interrupts(CURIE_IMU_SHOCK);
}

void loop() {
  temp = CurieIMU.readTemperature();
  // blink the LED in the main loop:
  digitalWrite(13, blinkState);
  blinkState = !blinkState;
  delay(1000);

  /*
  if (Serial.available() > 0) {
    int val = Serial.read();
    if (val == 's') { // if incoming serial is "s"
      // read raw accelerometer measurements from device
      //CurieIMU.readAccelerometer(axRaw, ayRaw, azRaw);
      //CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);
      ax = CurieIMU.readAccelerometer(X_AXIS);
      ay = CurieIMU.readAccelerometer(Y_AXIS);
      az = CurieIMU.readAccelerometer(Z_AXIS);
      Serial.print(ax);
      Serial.print(",");
      Serial.print(ay);
      Serial.print(",");
      Serial.print(az);
      Serial.print(",");
      Serial.print(gx);
      Serial.print(",");
      Serial.print(gy);
      Serial.print(",");
      Serial.println(gz);
    }
  }
  */
}

static void eventCallback(void)
{
  if (CurieIMU.getInterruptStatus(CURIE_IMU_SHOCK)) {
    CurieIMU.readAccelerometer(ax, ay, az);

    if (CurieIMU.shockDetected(X_AXIS, POSITIVE)) {
      Serial.write(ax);
      Serial.write(ay);
      Serial.write(az);
      //Serial.println("Negative shock detected on X-axis");
    } else if (CurieIMU.shockDetected(X_AXIS, NEGATIVE)) {
      //Serial.print('X');
      Serial.write(ax);
      Serial.write(ay);
      Serial.write(az);
      //Serial.println("Positive shock detected on X-axis");
    } else if (CurieIMU.shockDetected(Y_AXIS, POSITIVE)) {
      //Serial.print('Y');
      Serial.write(ax);
      Serial.write(ay);
      Serial.write(az);
      //Serial.println("Negative shock detected on Y-axis");
    } else if (CurieIMU.shockDetected(Y_AXIS, NEGATIVE)) {
      //Serial.print('Y');
      Serial.write(ax);
      Serial.write(ay);
      Serial.write(az);
      //Serial.println("Positive shock detected on Y-axis");
    } else if (CurieIMU.shockDetected(Z_AXIS, POSITIVE)) {
      //Serial.print('Z');
      Serial.write(ax);
      Serial.write(ay);
      Serial.write(az);
      //Serial.println("Negative shock detected on Z-axis");
    } else if (CurieIMU.shockDetected(Z_AXIS, NEGATIVE)) {
      //Serial.println("Positive shock detected on Z-axis");
      //Serial.print('Z');
      Serial.write(ax);
      Serial.write(ay);
      Serial.write(az);
    }
  }
}
