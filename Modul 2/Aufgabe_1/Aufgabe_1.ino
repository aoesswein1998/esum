#include <sps30.h>
#include <Adafruit_GFX.h> // Grafik und Text
#include <Adafruit_SSD1306.h> // Display
// Auswählen ob die Ausgabe über die Serielle Schnittstelle Lesbar oder im CSV Format gestaltet werden soll
//#define readable

struct sps30_measurement m;

Adafruit_SSD1306 display = Adafruit_SSD1306();

void print_counter(float counter) {
  display.clearDisplay(); // Puffer leeren
  display.setCursor(0, 8); // (0, 0) ist links oben
  display.setTextSize(2); // Textgröße (1, 2, 4)
  display.print("PM2.5:");
  display.println(counter);
  display.display(); 
}

void setup() {
  Serial.begin(115200);
  while(! Serial);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);

  sensirion_i2c_init();
  sps30_probe();
  sps30_start_measurement();
  #ifndef readable
  Serial.println("Time,PM1,PM2.5,PM4,PM10,Typical,Bucket1,Bucket2.5,Bucket4,Bucket10");
  #endif
}

void loop() {
  sps30_read_measurement(&m);
  unsigned long time = millis();
  print_counter(m.mc_2p5);
  float bucket_1um, bucket_2um5, bucket_4um, bucket_10um;
  bucket_1um = m.mc_1p0;
  bucket_2um5 = m.mc_2p5 - m.mc_1p0;
  bucket_4um = m.mc_4p0 - m.mc_2p5;
  bucket_10um = m.mc_10p0 - m.mc_4p0;

  #ifndef readable
  Serial.print(time);
  Serial.print(",");
  Serial.print(m.mc_1p0);
  Serial.print(",");
  Serial.print(m.mc_2p5);
  Serial.print(",");
  Serial.print(m.mc_4p0);
  Serial.print(",");
  Serial.print(m.mc_10p0);
  Serial.print(",");
  Serial.print(m.typical_particle_size);
  Serial.print(",");
  Serial.print(bucket_1um);
  Serial.print(",");
  Serial.print(bucket_2um5);
  Serial.print(",");
  Serial.print(bucket_4um);
  Serial.print(",");
  Serial.println(bucket_10um);
  #endif

  #ifdef readable
  Serial.println("PM1: " + String(m.mc_1p0) + " µg/m3");
  Serial.println("PM2.5: " + String(m.mc_2p5) + " µg/m3");
  Serial.println("PM4: " + String(m.mc_4p0) + " µg/m3");
  Serial.println("PM10: " + String(m.mc_10p0) + " µg/m3");
  Serial.println("Typical size: " + String(m.typical_particle_size) + " µm");
  Serial.println("Bucket_0.3-1.0uM: " + String(bucket_1um)+ " µg/m3");
  Serial.println("Bucket_1.0-2.5uM: " + String(bucket_2um5)+ " µg/m3");
  Serial.println("Bucket_2.5-4.0uM: " + String(bucket_4um)+ " µg/m3");
  Serial.println("Bucket_4.0-10uM: " + String(bucket_10um)+ " µg/m3");
  #endif
  delay(1000);
}