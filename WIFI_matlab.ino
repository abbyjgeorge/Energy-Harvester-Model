#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

const char* ssid     = "4ESP32";
const char* password = "GoTigers2018";

WiFiServer server(80);
Adafruit_INA219 ina219;
void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(200);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected to IP address:");
    Serial.println(WiFi.localIP());
    server.begin();
    uint32_t currentFrequency;    
    ina219.begin();
    ina219.setCalibration_16V_400mA();
}
int value = 0;
void loop()
{
 WiFiClient client = server.available();
 if (client)
 {
    if (client.connected()) 
    {
      Serial.println("Client Connected");
      int t1 = millis();
      delay(100);
      int i = millis(); 
      while(i-t1<=5100)
      {
        i = millis();  
        double power_mW = 0;
        double busvoltage = 0;
        double current_mA = 0;
        double shuntvoltage = 0;
        double loadvoltage = 0;
        shuntvoltage = ina219.getShuntVoltage_mV();
        busvoltage = ina219.getBusVoltage_V();
        current_mA = ina219.getCurrent_mA();
        loadvoltage = busvoltage + (shuntvoltage/1000);
       //power_mW = ina219.getPower_mW();
        client.write(loadvoltage);
        //client.write(current_mA);
        client.print("%f",current_mA);
        Serial.println(loadvoltage);
        Serial.println(current_mA);
       // client.write(power_mW);
       // client.write(busvoltage);
       // client.write(shuntvoltage);
       // Serial.print(power_mW);
       // Serial.print(" ");
       // Serial.print(current_mA);
       // Serial.print(" ");
       // Serial.print(shuntvoltage);       
       }
      Serial.println("written 5 seconds of data");
    }
  }
}
