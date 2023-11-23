/**************************************************************************/
/*!
    @file     Adafruit_MMA8451.h
    @author   K. Townsend (Adafruit Industries)
    @license  BSD (see license.txt)

    This is an example for the Adafruit MMA8451 Accel breakout board
    ----> https://www.adafruit.com/products/2019

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    @section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

#define raw

Adafruit_MMA8451 mma = Adafruit_MMA8451();
int calibrate_x;
int calibrate_y;
int calibrate_z;

void calibrate(void) {
  int n = 200;
  int sumX = 0;
  int sumY = 0;
  int sumZ = 0;
  int i;
  for (i=0; i<n; i++) {
    mma.read();
    sumX += mma.x;
    sumY += mma.y;
    sumZ += mma.z;
    delay(5);
  }
  calibrate_x = sumX / n;
  calibrate_y = sumY / n;
  calibrate_z = sumZ / n;
}

void setup(void) {
  Serial.begin(115200);

  if (! mma.begin()) {
    while (1);
  }
  
  mma.setRange(MMA8451_RANGE_2_G);

  calibrate();
}

void loop() {
  // Read the 'raw' data in 14-bit counts
  mma.read();
  float x = mma.x - calibrate_x;
  float y = mma.y - calibrate_y;
  float z = mma.z - calibrate_z;
  #ifdef raw
  Serial.print(x); 
  Serial.print("\t");
  Serial.print(y); 
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\t");
  Serial.println();
  #endif
  #ifndef raw
  Serial.print(x*4/16383);
  Serial.print("\t");
  Serial.print(y*4/16383); 
  Serial.print("\t");
  Serial.print(z*4/16383);
  Serial.println();
  #endif
  delay(50);
}