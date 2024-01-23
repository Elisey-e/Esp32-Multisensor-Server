#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"
#include "senseair_s8.h"
#include "DHT.h"
 
// Раскомментируйте ту строку, которая соответствует вашему датчику
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22  // DHT 22 (AM2302), AM2321

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino resetpin)

#define I2C_SDA_COMMON 19
#define I2C_SCL_COMMON 18

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
const char* ssid = "***";   // Вводим сюда SSID
const char* password = "***";  //Вводим пароль
 
WebServer server(80);
 
// Датчик DHT
uint8_t DHTPin = 32;

// Инициализируем DHT
DHT dht(DHTPin, DHTTYPE);
 
float Temperature;
float Humidity;
 
void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(DHTPin, INPUT);
  dht.begin();
  co2_setup();
 
  // Подключаемся к WiFi ---
  Serial.println("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  // Проверяем подключение
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("t");
  }
 
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());
  // ---
 
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
 
  Serial.println("HTTP server started");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
  }

  display.clearDisplay();
}
 
void loop() {
  Temperature = dht.readTemperature(); // Получает значение температуры
  Humidity = dht.readHumidity(); // Получаем показания влажности
  co2_requestValueAndStatus();
  
  server.handleClient();
  
  display.clearDisplay();
  // Display Text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(0, 8);
  display.print("Temp: ");
  display.setCursor(40, 4);
  display.setTextSize(2);
  display.print((int) Temperature);
  display.print(".0");
  display.setTextSize(1);
  display.write(9);
  display.setTextSize(2);
  display.print("C\n");

  display.setTextSize(1);
  display.setCursor(0, 28);
  display.print("Humd: ");
  display.setCursor(40, 24);
  display.setTextSize(2);
  display.print((int) Humidity);
  display.print(".0%\n");

  display.setTextSize(1);
  display.setCursor(0, 48);
  display.print("CO2 : ");
  display.setCursor(40, 44);
  display.setTextSize(2);
  display.print((int) co2_value);
  display.setTextSize(1);
  display.print("ppm");
  
  display.display();
  delay(2000);
}
 
void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(Temperature, Humidity, co2_value));
}
 
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
 
String SendHTML(float Temperaturestat, float Humiditystat, unsigned long int co2_value_stat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>ESP32 Weather Report</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>ESP32 Weather Report</h1>\n";
  
  ptr += "<p>Temperature: ";
  ptr += (int) Temperaturestat;
  ptr += ".0";
  ptr += "°C</p>";
  
  ptr += "<p>Humidity: ";
  ptr += (int) Humiditystat;
  ptr += ".0";
  ptr += "%</p>";

  ptr += "<p>CO2 level: ";
  ptr += (int) co2_value_stat;
  ptr += "ppm</p>";
  
  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
