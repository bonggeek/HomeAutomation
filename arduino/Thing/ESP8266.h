#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "WifiConfig.h"

class ESP8266 {
public:
    ESP8266(SoftwareSerial& softSerial, uint32_t baud);
    bool setup();
    bool joinWifi(String ssid, String pwd);

    String getVersion();
    bool restart(void);
private:
    void empty();
    String recvString(String target, uint32_t timeout = 1000);
    String recvString(String target1, String target2, uint32_t timeout = 1000);
    bool recvFindAndFilter(String target, String begin, String end, String &data, uint32_t timeout = 1000);
    bool recvFind(String target, uint32_t timeout = 1000);

    bool eAT(void);
    bool eATRST(void);
    bool eATGMR(String &version);
    bool sATCWJAP(String ssid, String pwd);
    
  SoftwareSerial* m_pSerial;  
};
#endif /* #ifndef __ESP8266_H__ */

