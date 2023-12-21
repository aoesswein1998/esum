#include <SPI.h>
#include <WiFi101.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
/*
config.h muss die folgenden defines enthalten:
#define IO_USERNAME ""
#define IO_KEY  ""
#define WIFI_SSID ""
#define WIFI_PASS ""
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define keyIndex 0
*/
#include "config.h"

#define ENA 2
#define RST 4
#define IRQ 7
#define CS 8
#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5

int textHight = 8;
int32_t counter;

int status = WL_IDLE_STATUS;
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, IO_USERNAME, IO_KEY);
Adafruit_SSD1306 display = Adafruit_SSD1306();

Adafruit_MQTT_Publish counters = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/counter");
Adafruit_MQTT_Subscribe feed = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME "/feeds/counter");
Adafruit_MQTT_Subscribe *subscription;

void mqttConnect(void){
  int8_t ret;
  while (WiFi.status() != WL_CONNECTED){
    display.clearDisplay();
    Serial.print(".");
    display.setCursor(0, 0);
    display.print("Trying to conect to:");
    display.setCursor(0, 1*textHight);
    display.print(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    display.display();
    delay(2000);
  }
  if (mqtt.connected()) {
    return;
  }
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Conected to WiFi.");
  display.setCursor(0,1 * textHight);
  display.print("Conecting to MQTT...");
  display.display();
  delay(2000);
  while (ret = mqtt.connect() != 0){
    display.setCursor(0,3 * textHight);
    display.print(mqtt.connectErrorString(ret));
    display.setCursor(0,4 * textHight);
    display.print("Retrying in 10 sec.");
    display.display();
    delay(10000);
    display.clearDisplay();
    display.display();
  }
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("MQTT conected!");
  display.display();
}

void display_setup(){
  // Initialisiret das Display und die Tasten
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);

}

void setup(){
  Serial.begin(15200);
  while (!Serial);
  WiFi.setPins(CS, IRQ, RST, ENA);
  display_setup();
  mqtt.subscribe(&feed);

  mqttConnect();
  mqtt.ping();
  
  while ((subscription = mqtt.readSubscription(1000))){
  }
}

void loop(){
  mqttConnect();
  display.clearDisplay();
  counter = atoi((char *)feed.lastread);
  int prevcounter = counter;
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
 
 if (prevcounter != counter) {
    Serial.println(counter);
    if (! counters.publish(counter)) {
      display.setCursor(0,1 *textHight);
      display.print("Failed!");
      display.display();
    }
    else {
      display.setCursor(0,2 *textHight);
      display.print("OK");
      display.display();
  }
 }
 
 while ((subscription = mqtt.readSubscription(100))){
    counter = atoi((char *)feed.lastread);
  }
  display.setCursor(0,3 *textHight);
  display.print("received:");
  display.print(atoi((char *)feed.lastread));
  display.display();
  delay(100);
}
