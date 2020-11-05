#include <M5Stack.h>
#include <TinyGPS++.h>

//_____________________________________________________________

#include <M5LoRa.h>

//_____________________________________________________________

static const uint32_t GPSBaud = 9600;
String out;
int i;

TinyGPSPlus gps;

HardwareSerial ss(2);

void setup()
{
  M5.begin();
  M5.Lcd.setTextSize(2);
    
    ss.begin(GPSBaud, SERIAL_8N1, 22, 21);
  Serial.begin(9600);

  //_____________________________________________________________
  M5.Power.begin();
  // override the default CS, reset, and IRQ pins (optional)
//  LoRa.setPins(); // default set CS, reset, IRQ pin
  Serial.println("LoRa Sender");
  M5.Lcd.println("LoRa Sender");

  // frequency in Hz (433E6, 866E6, 915E6)
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    M5.Lcd.println("Starting LoRa failed!");
    while (1);
  }

  // LoRa.setSyncWord(0x69);
  Serial.println("LoRa init succeeded.");
  M5.Lcd.println("LoRa init succeeded.");

  //_____________________________________________________________
  


}

void loop()
{
  M5.Lcd.setCursor(10, 120);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.println(out);

  //_____________________________________________________________
  
  LoRa.beginPacket();
  LoRa.print(out);
  LoRa.endPacket();
  
  //_____________________________________________________________
    
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    M5.Lcd.println(F("No GPS data received: check wiring"));
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
//________________________________________________________________________________ 
String str = "";
char buff[12];
      Serial.println(gps.time.hour());
      str = str + gps.time.hour();
      str = str + ":";
      Serial.println(gps.time.minute());
      str = str + gps.time.minute();
      str = str + ":";      
      Serial.println(gps.time.second());
      str = str + gps.time.second();
      str = str + ",";      
      Serial.println(gps.satellites.value());
      str = str + gps.satellites.value();
      str = str + ",";       
      Serial.println(gps.location.lat(), 6);
      float lat = gps.location.lat();
      dtostrf(lat, 5, 6, buff);
      str = str + buff;
      str = str + ",";            
      Serial.println(gps.location.lng(), 6);
      float lng = gps.location.lng();
      dtostrf(lng, 5, 6, buff);               
      str = str + buff;
      str = str + ",";       
      Serial.println(gps.altitude.meters());
      str = str + gps.altitude.meters();      
      out = str;
  } while (millis() - start < ms);
}
