#include "ESP8266.h"

ESP8266::ESP8266(SoftwareSerial& softSerial, uint32_t baud) : m_pSerial(&softSerial)
{
    m_pSerial->begin(baud);
    //m_pSerial->setTimeout(5000); 
    //m_pSerial->empty();
}

bool ESP8266::setup()
{
    bool res = restart();
    
    if(res) 
    { 
        Serial.println("Module is ready"); 
        return true;
    } 
    else 
    { 
        Serial.println("Module have no response."); 
        return false;
    }

    return res;
}

bool ESP8266::restart(void)
{
    unsigned long start;
    if (eATRST()) {
        delay(2000);
        start = millis();
        while (millis() - start < 3000) {
            if (eAT()) {
                delay(1500); /* Waiting for stable */
                return true;
            }
            delay(100);
        }
    }
    
    return false;
}

bool ESP8266::joinWifi(String ssid, String pwd)
{
  return sATCWJAP(ssid, pwd);
}

String ESP8266::getVersion()
{
    String version;
    eATGMR(version);
    return version;
}

void ESP8266::empty()
{
    while(m_pSerial->available() > 0)
        m_pSerial->read();
}


bool ESP8266::recvFindAndFilter(String target, String begin, String end, String &data, uint32_t timeout)
{
    String data_tmp;
    data_tmp = recvString(target, timeout);
    if (data_tmp.indexOf(target) != -1) {
        int32_t index1 = data_tmp.indexOf(begin);
        int32_t index2 = data_tmp.indexOf(end);
        if (index1 != -1 && index2 != -1) {
            index1 += begin.length();
            data = data_tmp.substring(index1, index2);
            return true;
        }
    }
    data = "";
    return false;
}
  
String ESP8266::recvString(String target, uint32_t timeout)
{
    String data;
    char a;
    unsigned long start = millis();
    while (millis() - start < timeout) {
        while(m_pSerial->available() > 0) {
            a = m_pSerial->read();
      if(a == '\0') continue;
            data += a;
        }
        if (data.indexOf(target) != -1) {
            break;
        }   
    }
    return data;
}

String ESP8266::recvString(String target1, String target2, uint32_t timeout)
{
    String data;
    char a;
    unsigned long start = millis();
    while (millis() - start < timeout) {
        while(m_pSerial->available() > 0) {
            a = m_pSerial->read();
      if(a == '\0') continue;
            data += a;
        }
        if (data.indexOf(target1) != -1) {
            break;
        } else if (data.indexOf(target2) != -1) {
            break;
        }
    }
    return data;
}


bool ESP8266::recvFind(String target, uint32_t timeout)
{
    String data_tmp;
    data_tmp = recvString(target, timeout);
    if (data_tmp.indexOf(target) != -1) {
        return true;
    }
    return false;
}

bool ESP8266::eAT(void)
{
    empty();
    m_pSerial->println("AT");
    return recvFind("OK");
}

bool ESP8266::eATRST(void) 
{
    empty();
    m_pSerial->println("AT+RST");
    return recvFind("OK");
}


bool ESP8266::eATGMR(String &version)
{
    empty();
    m_pSerial->println("AT+GMR");
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", version); 
}

bool ESP8266::sATCWJAP(String ssid, String pwd)
{
    String data;
    empty();
    m_pSerial->print("AT+CWJAP=\"");
    m_pSerial->print(ssid);
    m_pSerial->print("\",\"");
    m_pSerial->print(pwd);
    m_pSerial->println("\"");
    
    data = recvString("OK", "FAIL", 10000);
    if (data.indexOf("OK") != -1) {
        return true;
    }
    
    return false;
}

