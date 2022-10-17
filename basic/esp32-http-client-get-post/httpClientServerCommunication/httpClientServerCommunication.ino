/**
  This code is an example of sending and recieving json data from server(Laravel is used Here)
  Deserialize json data
  posting json data as json string in server in post method with httpclient
  by Debarun Saha
*/
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#define HOST "http://4154d15d.ngrok.io"

const char* ssid       = "xxx";
const char* password   = "xxx";

StaticJsonDocument<200> doc;
StaticJsonDocument<200> postJson;
void setup()
{

  Serial.begin(115200);
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

}

void loop()
{


  //  httpGet();
  //  Serial.println("----------");
  //  httPost();
  //  delay(300000);
  jsonDataPost();
  delay(300000);
}

void httPost() {
  HTTPClient httPost;
  httPost.begin("http://921709fa.ngrok.io/api/http-post");
  httPost.addHeader("Content-Type", "application/json");
  int httpResponceCode = httPost.POST("{\n\"sensor\":\"gps\",\n\"time\":1351824120,\n\"data\":[\n48.756080,\n2.302038\n]\n}");
  if (httpResponceCode > 0) {
    String response = httPost.getString();
    Serial.println(httpResponceCode);
    Serial.println(response);
  } else {
    Serial.print("err:");
    Serial.println(httpResponceCode);
  }
  httPost.end();

}

void httpGet() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://921709fa.ngrok.io/api/http-get");
    //    http.addHeader("Content-Type","text/plain");
    int httpResponceCode = http.GET();
    if (httpResponceCode > 0) {
      String response = http.getString();
      Serial.println(httpResponceCode);
      Serial.println(response);
      DeserializationError error = deserializeJson(doc, response);
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }
      const char* retval1 = doc["data"][0];
      const char* retval2 = doc["data"][1];
      Serial.println("Parsed data : ");
      Serial.println(retval1);
      Serial.println(retval2);

    } else {
      Serial.print("err:");
      Serial.println(httpResponceCode);
    }
    http.end();
  } else {
    Serial.println("wifi err");
  }
}

void jsonDataPost() {
  StaticJsonDocument<128> jsonDoc;
  JsonObject stateObj = jsonDoc.createNestedObject("state");
  JsonObject reportedObj = stateObj.createNestedObject("reported");
  JsonObject desiredObj = stateObj.createNestedObject("desired");
  JsonObject locationObj = reportedObj.createNestedObject("location");
  locationObj["latitude"] = 22.54;
  locationObj["longitude"] = 88.72;
  char jsonBuffer[512];
  serializeJson(jsonDoc, jsonBuffer);
    Serial.println(jsonBuffer);
  HTTPClient httPost;
  httPost.begin(HOST"/api/arduino-json");
  httPost.addHeader("Content-Type", "application/json");
  int httpResponceCode = httPost.POST(jsonBuffer);
  if (httpResponceCode > 0) {
    String response = httPost.getString();
    Serial.println(httpResponceCode);
    Serial.println(response);
  } else {
    Serial.print("err:");
    Serial.println(httpResponceCode);
  }
  httPost.end();
}
