/**************************************************************************/
/*!
    @file     1.ino
    @author   Adrian Oeßwein

    Dieses Programm liest den Adafruit MMA8451 Beschleunigungssensor aus.
    Zu Beginn des Programms werden 200 Werte gesammelt, deren Durchschnitt
    gebildet und anschließend als Kalibrierung raus gerechnet.
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
// Wechselt zwischen Ausgabe als 14 Bit Rohwerte oder m/s^2
#define raw

Adafruit_MMA8451 mma = Adafruit_MMA8451();
int calibrate_x;
int calibrate_y;
int calibrate_z;

/**************************************************************************/
// Funktion: calibrate
//
// Nimmt 200 Messwerte des Beschleunigungssensors auf und speichert deren
// Durchschnitt in den calibrate_ globalen Variablen
/**************************************************************************/
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
  // Stoppe das Programm falls der MMA8451 nicht antwortet
  if (! mma.begin()) {
    while (1);
  }
  // Setze den Messbereich des Beschleunigungssensors auf 2g
  mma.setRange(MMA8451_RANGE_2_G);

  calibrate();
}

void loop() {
  // Read the 'raw' data in 14-bit counts
  float start = millis();
  mma.read();
  float end = millis();
  //Serial.println(end-start);
  float x = mma.x - calibrate_x;
  float y = mma.y - calibrate_y;
  float z = mma.z - calibrate_z;
  #ifdef raw
  Serial.print(x); 
  Serial.print(",");
  Serial.print(y); 
  Serial.print(",");
  Serial.print(z);
  Serial.println();
  #endif
  #ifndef raw
  Serial.print(x*4/16383);
  Serial.print(",");
  Serial.print(y*4/16383); 
  Serial.print(",");
  Serial.print(z*4/16383);
  Serial.println();
  #endif
  delay(50);
}