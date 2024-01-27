# ESP-32 Server with temperature, humidity and CO2 concentration measuring

## Sensors

The full device contains 
  * SenseAir S8-0053 sensor
  * DHT 22(AM2302) sensor
  * IIC SSD1306 display
  * ESP32-WROOM-32D (Pinout: https://images.theengineeringprojects.com/image/webp/2020/12/introduction-to-esp32-3.png.webp?ssl=1)
  * Wires, buttons and 18650 supply modules

## Connection

All documantations for these modules can be found in internet, let's pick up some resourses, which I used to connect all devices:

  * https://microkontroller.ru/esp32-projects/podklyuchenie-oled-displeya-k-modulyu-esp32/
  * https://raw.githubusercontent.com/KlausMu/esp32-co2monitor/main/images/fritzing_CO2monitor.png
  * https://blog.ifound.me/smarthome/podklyuchaem-k-esp8266-datchik-senseair-s8-0053/
  * https://github.com/KlausMu/esp32-co2monitor/tree/main?tab=readme-ov-file

Notice: Personally I disconnected co2 sensor while flashing esp.

## Code

Most of used libraries are open-source, found in resources above. Code is raw a bit, try to find details in libraries realisation. 
