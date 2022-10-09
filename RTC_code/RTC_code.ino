#include "NTPClient.h"
#include "ESP8266WiFi.h"
#include <ESP8266WebServer.h>
#include "WiFiUdp.h"
#include <ArduinoJson.h>
#include <stdio.h>
#include <stdlib.h>

const char *ssid = "Naren";
const char *password = "open1234";


ESP8266WebServer server(80);  //Define server object
const long utcOffsetInSeconds = -14400; //UTC -4:00 = -4*3600 = -14400

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup(){
Serial.begin(115200);

WiFi.begin(ssid, password);

while ( WiFi.status() != WL_CONNECTED ) {
delay ( 500 );
Serial.print ( "." );
}

//  Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP
//   server.on("/", loop);      //Associate handler function to web requests
    
//   server.begin(); //Start web server
//   Serial.println("HTTP server started");

timeClient.begin();
}


void loop() {

//server.handleClient();
//String webPage;
//RTC and temperature
timeClient.update();
int analogValue = analogRead(A0);
float temp = ((analogValue / 1241.21) / 0.01) - 0.5;

//JSON
DynamicJsonBuffer jBuffer;
JsonObject& data = jBuffer.createObject();

data["Time"] = timeClient.getFormattedTime() ;
data["Raw value"] = analogValue ;
data["Temperature"] = temp + 4;

data.printTo(Serial);
//data.printTo(webPage); 
//server.send(200, "text/html", webPage);
Serial.print("\n");
delay(1000);

}