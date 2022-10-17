
#include <WiFi.h>
const char* ssid = "Orange_wifi_50D9";
const char* password = "n39B2aDYMAE";

WiFiServer server(80); // Port 80

#define LED2  2    // LED2 is a Built-in LED.
String state = "";
int wait30 = 30000; // time to reconnect when connection is lost.

void setup() {
  // 
  Serial.begin(115200);
  pinMode(LED2, OUTPUT);

// Connect WiFi net.

  Serial.println();
  Serial.print("Connecting with ");
  Serial.println(ssid);
 // hadi hia li catconnectih
  WiFi.begin(ssid, password);
 // if not connected yet katb9a tkteb f no9at
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // hna fach ghatconnecta
  Serial.println("Connected with WiFi.");
 
  // Start Web Server.
  server.begin();
  Serial.println("Web Server started.");
 
  // Esta es la IP
  Serial.print("This is IP to connect to the WebServer: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
}
 
void loop() {
// If disconnected, try to reconnect every 30 seconds.
  if ((WiFi.status() != WL_CONNECTED) && (millis() > wait30)) {
    Serial.println("Trying to reconnect WiFi...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    wait30 = millis() + 30000;
  } 
  
  // Check if a client has connected..
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  Serial.print("New client: ");
  Serial.println(client.remoteIP());
   
  // Espera hasta que el cliente envíe datos.
  // while(!client.available()){ delay(1); }

  /////////////////////////////////////////////////////
  // Read the information sent by the client.
  String req = client.readStringUntil('\r');
  Serial.println(req);

  // Make the client's request.
       if (req.indexOf("on2") != -1) {digitalWrite(LED2, HIGH); state = "ON";}
       if (req.indexOf("off2") != -1){digitalWrite(LED2, LOW); state = "OFF";}
     if(req.indexOf("admin")!= -1){state = "You are now Root!";}
     if (req.indexOf("consult") != -1){
         if (digitalRead(LED2)){state = "LED2 now is ON";}
         else {state = "LED2 now is OFF";}
          }
     
  //////////////////////////////////////////////
  //  WEB PAGE. ////////////////////////////
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  Important.
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta charset=utf-8></head>");
  client.println("<body><center><font face='Arial'>");
  client.println("<h1>ESP32 web server</h1>");
  client.println("<h2><font color='#009900'>Welcome ladies and gentelmen</font></h2>");
  client.println("<h3>Cyber Hassan</h3>");
  client.println("<br><br>");
  client.println("<a href='on2'><button>Click to ON LED2</button></a>");
  client.println("<a href='off2'><button>Click to OFF LED2</button></a>");
  client.println("<a href='consult'><button>Consult status LED2</button></a>");
  client.println("<br><br>");
  client.println(state);  
  client.println("</font></center></body></html>");

  Serial.print("Client disconnected: ");
  Serial.println(client.remoteIP());
  client.flush();
  client.stop();
}
