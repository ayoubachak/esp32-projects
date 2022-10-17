  /*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/cloud-weather-station-esp32-esp8266/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

*/

#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include "ESPAsyncWebServer.h"
#include <EEPROM.h>

#include <Wire.h>

// const char* ssid = "Redmii";
// const char* password = "ayoubachak01";

// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /esp-post-data.php also needs to have the same key

// router fucntions 
AsyncWebServer server(80);

struct settings {
  char ssid[30];
  char password[30];
} user_wifi = {};

void save_to_EEPROM(String _1, String _2){
     strncpy(user_wifi.ssid, _1.c_str(), sizeof(user_wifi.ssid) );
      strncpy(user_wifi.password, _2.c_str(), sizeof(user_wifi.password) );
      user_wifi.ssid[_1.length()] = user_wifi.password[_2.length()] = '\0';
      EEPROM.put(0, user_wifi);
      EEPROM.commit();
     
}

void connect_wifi(){
        WiFi.begin(user_wifi.ssid, user_wifi.password);
        while (WiFi.status() != WL_CONNECTED) {
          delay(1000);
          Serial.print(".");
        }
      Serial.println("");
      Serial.print("Connected to WiFi network with IP Address: ");
      Serial.println(WiFi.localIP());

}

void wifi_setup(){
  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
      String inputMessage1 ;
      String inputMessage2 ;
      AsyncWebParameter *p = request->getParam(0);
      Serial.print("SSID : ");
      inputMessage1 =p->value(); 
      Serial.println(inputMessage1);
      p = request->getParam(1);
      Serial.print("PASSWORD : ");
      inputMessage2 =p->value();  
      Serial.println(inputMessage2);
      
      save_to_EEPROM(inputMessage1, inputMessage2);
      request->send(200,   "text/html",  "<!doctype html><html lang='en'><head><meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1'><title>Wifi Setup</title><style>*,::after,::before{box-sizing:border-box;}body{margin:0;font-family:'Segoe UI',Roboto,'Helvetica Neue',Arial,'Noto Sans','Liberation Sans';font-size:1rem;font-weight:400;line-height:1.5;color:#212529;background-color:#f5f5f5;}.form-control{display:block;width:100%;height:calc(1.5em + .75rem + 2px);border:1px solid #ced4da;}button{border:1px solid transparent;color:#fff;background-color:#007bff;border-color:#007bff;padding:.5rem 1rem;font-size:1.25rem;line-height:1.5;border-radius:.3rem;width:100%}.form-signin{width:100%;max-width:400px;padding:15px;margin:auto;}h1,p{text-align: center}</style> </head> <body><main class='form-signin'> <h1>Wifi Setup</h1> <br/> <p>Your settings have been saved successfully!<br />Please restart the device.</p></main></body></html>" );
    });
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200,   "text/html", "<!doctype html><html lang='en'><head><meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1'><title>Wifi Setup</title> <style>*,::after,::before{box-sizing:border-box;}body{margin:0;font-family:'Segoe UI',Roboto,'Helvetica Neue',Arial,'Noto Sans','Liberation Sans';font-size:1rem;font-weight:400;line-height:1.5;color:#212529;background-color:#f5f5f5;}.form-control{display:block;width:100%;height:calc(1.5em + .75rem + 2px);border:1px solid #ced4da;}button{cursor: pointer;border:1px solid transparent;color:#fff;background-color:#007bff;border-color:#007bff;padding:.5rem 1rem;font-size:1.25rem;line-height:1.5;border-radius:.3rem;width:100%}.form-signin{width:100%;max-width:400px;padding:15px;margin:auto;}h1{text-align: center}</style> </head> <body><main class='form-signin'> <form action='/post' method='post'> <h1 class=''>Wifi Setup</h1><br/><div class='form-floating'><label>SSID</label><input type='text' class='form-control' name='ssid'> </div><div class='form-floating'><br/><label>Password</label><input type='password' class='form-control' name='password'></div><br/><br/><button type='submit'>Save</button><p style='text-align: right'></p></form></main> </body></html>" );
      });
      server.begin();
}

void setup() {
  Serial.begin(115200);
  // EEPROM Register
  EEPROM.begin(sizeof(struct settings) );
  EEPROM.get( 0, user_wifi );
  // First try to connect to the wifi 
  WiFi.mode(WIFI_STA);
  WiFi.begin(user_wifi.ssid, user_wifi.password);
  
  byte tries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    if (tries++ > 30) {
      WiFi.mode(WIFI_AP);
      WiFi.softAP("ESP69", "123456789");
      break;
    }
  }
  // this is the part where you connect to the wifi via the router interface
  wifi_setup();
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}


void loop() {


    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      Serial.println("Wifi connected.. you can do anythign here after the connection");
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    delay(10);
  
}
