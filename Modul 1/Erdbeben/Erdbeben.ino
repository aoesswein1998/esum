#include <D7S.h>
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

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Start MMA");
  while (!mma.begin()) {
    Serial.print(".");
    delay(50);
  }
  Serial.println("done");
  mma.setRange(MMA8451_RANGE_2_G);

  calibrate();

  Serial.print("Starting D7S communications (it may take some time)...");
  D7S.begin();
  while (!D7S.isReady()) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("STARTED");

  Serial.println("Setting D7S sensor to switch axis at inizialization time.");
  D7S.setAxis(SWITCH_AT_INSTALLATION);

  Serial.println("Initializing the D7S. keep it steady!");
  delay(2000);
  Serial.print("Initializing...");
  D7S.initialize();
  while (!D7S.isReady()) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("INITIALIZED!");
}

void loop() {
	//checking if there is an earthquake occuring right now
  float start = millis();
  float end;
  if (D7S.isEarthquakeOccuring()) {
    //getting instantaneus SI
    Serial.print(D7S.getInstantaneusSI());
    Serial.print(",");
    //getting instantaneus PGA
    Serial.print(D7S.getInstantaneusPGA());
    Serial.print(",");
    end = millis();
  }
  else {
    Serial.print(0);
    Serial.print(",");
    Serial.print(0);
    Serial.print(",");
    end = start;
  }
  // Read the 'raw' data in 14-bit counts
  mma.read();
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
  //Serial.println(end-start);
}
