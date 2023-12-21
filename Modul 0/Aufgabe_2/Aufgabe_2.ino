 #include <Adafruit_GFX.h> // Grafik und Text
 #include <Adafruit_SSD1306.h> // Display

 #define BUTTON_A 9 // Pin-Belegung für M0
 #define BUTTON_B 6
 #define BUTTON_C 5

 Adafruit_SSD1306 display = Adafruit_SSD1306();

 int counter = 0;

 void setup() {
 pinMode(BUTTON_A, INPUT_PULLUP); // interne Pull-Up-Widerstände aktivieren
 pinMode(BUTTON_B, INPUT_PULLUP);
 pinMode(BUTTON_C, INPUT_PULLUP);

 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 display.setTextColor(WHITE);
 }

 void print_counter(int counter) {
 display.clearDisplay(); // Puffer leeren
 display.setCursor(0, 8); // (0, 0) ist links oben
 display.setTextSize(2); // Textgröße (1, 2, 4)
 display.println(counter);
 display.display(); 
 }


 void loop() {
 if (!digitalRead(BUTTON_A)) {
 delay(50); // Entprellen, Zeit ggf. anpassen
  if (!digitalRead(BUTTON_A)) {
    counter++;
  }
 }
 if (!digitalRead(BUTTON_B)) {
 delay(50); // Entprellen, Zeit ggf. anpassen
  if (!digitalRead(BUTTON_B)) {
    counter--;
  }
 }
 print_counter(counter);
 delay(50);
 }