# M5StackCore_LoRa868_GPSAT6558
GPS and LoRa with M5Stack in Arduino IDE
Building on the LoRaReceiver and LoRaSender example sketches for the LoRa 868 module on M5Stack Core, I add the GPS unit to the LoRaSender and work through the GPS_AT6558 example sketches in the Arduino IDE to get GPS data sent to the LoRaReceiver.

LoRa 868 Module Tutorial for the M5Stack Core ESP32 in Arduino IDE
https://youtu.be/I2vA3luWvOs

Example sketches:
M5Stack / Modules / LoRa433_SX1278 / LoRaReceiver and LoRaSender
	As demonstrated, these are simple sketches that just need to be adapted for the scenario.

M5Stack / Basics / Display
	This shows how to overcome the issue where data scrolls off the screen on the reciever. Set cursor to specific location and overwrite.

M5Stack / Unit / GPS_AT6558 / FullExample
	Complex display with lots of data, more than needed.
	"No GPS data check wiring": I posted an issue on the M5Syack GitHub repository and got this response from GitHub site: use ss.begin(GPSBaud, SERIAL_8N1, 22, 21)
	I want to concatenate all desired data into a single string for lora packet transmission. I had two problems. Defining the string variable as 'char' gave me an     error converting 'int' types when concatenating. So I went with the String function to over come this. But I could not easy get the float precision for latitude and longitude that I desired until I found the dtostrf() function.

dtostrf() to convert float to string
http://www.nongnu.org/avr-libc/user-manual/group__avr__stdlib.html#ga060c998e77fb5fc0d3168b3ce8771d42

ESP32 Basic Core IoT Development Kit
https://m5stack.com/collections/m5-core/products/basic-core-iot-development-kit

LoRa Module( 868MHz )
https://m5stack.com/collections/m5-module/products/lora-module-868mhz

Mini GPS/BDS Unit (AT6558)
https://m5stack.com/collections/m5-unit/products/mini-gps-bds-unit

GitHub  m5stack / M5Stack (Arduino IDE Library)
https://github.com/m5stack/M5Stack
