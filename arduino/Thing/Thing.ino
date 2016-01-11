
#include <SoftwareSerial.h>
const int LEDPin = 12;

#include "ESP8266.h"

#define HOST_NAME   "www.baidu.com"
#define HOST_PORT   (80)


SoftwareSerial softSerial(2, 3); // RX, TX
ESP8266 wifi(softSerial, 115200);

void setup()
{
    pinMode(LEDPin, OUTPUT);

    Serial.begin(115200);
    
    Serial.println("Demo2 starting");
    
    bool res = wifi.setup();

    delay(1000); 
    //connect to the wifi 
    Serial.print("Connecting to ");
    Serial.print(SSID);
    Serial.print(" : ");
    boolean connected = wifi.joinWifi(SSID, PASSWORD); 

    
    if(connected)
      Serial.println("Done");
    else
      Serial.println("FAILED");

    if (!connected){while(1);} 
    
    String version = wifi.getVersion();
    Serial.print("Version ");
    Serial.println(version.c_str());
    
    delay(5000); 
    //print the ip addr 
    softSerial.println("AT+CIFSR"); 
    Serial.println("ip address:"); 
    
   
    
    //set the single connection mode 
    softSerial.println("AT+CIPMUX=0");
}

void loop()
{
  digitalWrite(LEDPin, HIGH);
  delay(100);
  digitalWrite(LEDPin, LOW);
  delay(100);
}
