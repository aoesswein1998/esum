 #include <Adafruit_GFX.h> // Grafik und Text
 #include <Adafruit_SSD1306.h> // Display

 #define BUTTON_A 9 // Pin-Belegung für M0
 #define BUTTON_B 6
 #define BUTTON_C 5
 #define ANALOG A0 

 Adafruit_SSD1306 display = Adafruit_SSD1306();

 float analog = 0;
 float voltage = 0;

 void setup() {
 pinMode(BUTTON_A, INPUT_PULLUP); // interne Pull-Up-Widerstände aktivieren
 pinMode(BUTTON_B, INPUT_PULLUP);
 pinMode(BUTTON_C, INPUT_PULLUP);

 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 display.setTextColor(WHITE);
 analogReadResolution(12);
 
 print_counter(analog);
 Serial.begin(115200);
 while(!Serial);
 }

 void print_counter(float counter) {
 display.clearDisplay(); // Puffer leeren
 display.setCursor(0, 8); // (0, 0) ist links oben
 display.setTextSize(2); // Textgröße (1, 2, 4)
 display.println(counter);
 display.display(); 
 }


 void loop() {
 analog = analogRead(ANALOG);
 voltage = analog*3.3/4095.0;
 print_counter(voltage);
 Serial.println(voltage);
 delay(100);
 }