#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include "config.h"
#include "senseair_s8.h"
#include "DHT.h"
 
// Раскомментируйте ту строку, которая соответствует вашему датчику
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22  // DHT 22 (AM2302), AM2321
 
const char* ssid = "MTS_GPON_E80C";   // Вводим сюда SSID
const char* password = "Tc7ku4cT";  //Вводим пароль
 
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
}
 
void loop() {
  server.handleClient();
}
 
void handle_OnConnect() {
  Temperature = dht.readTemperature(); // Получает значение температуры
  Humidity = dht.readHumidity(); // Получаем показания влажности
  co2_requestValueAndStatus();
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
