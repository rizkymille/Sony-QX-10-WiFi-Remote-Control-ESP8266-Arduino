#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid     = "DIRECT-9uQ0:DSC-QX10";
const char* password = "JFJPXKpc";
const char* host = "10.0.0.1";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Laczenie do sieci WiFi: ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Polaczenie WiFi aktywne"); 
  Serial.println("Adres IP: ");
  Serial.println(WiFi.localIP());
 
  //-----------------------
  delay(2000);
 
  Serial.print("Laczenie z adresem ");
  Serial.println(host);
 
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 10000;
  if (!client.connect(host, httpPort)) {
    Serial.println("polaczenie nieudane");
    return;
  }
 Serial.print("Wysylanie zapytania JSON ");
  String PostData="{\"method\":\"actTakePicture\",\"params\":[],\"id\":1,\"version\":\"1.0\"}";
  // This will send the request to the server
  client.println("POST /sony/camera HTTP/1.1");
  client.println("Connection: close");
  client.println("Content-Type: application/json;charset=utf-8");
  client.print("Content-Length: ");
  client.println(PostData.length());
  client.println();
  client.println(PostData);

  /*
  delay(500);
   char c[1024];
  // Read all the lines of the reply from server and print them to Serial
   while(client.available()){
   c[0] = client.read();
   Serial.print(c);
   }
   
   StaticJsonBuffer<200> jsonBuffer;
   JsonObject& root = jsonBuffer.parseObject(c);
  int data = root["lowVersion"]; 
  Serial.println();
     Serial.print(data);
     
  Serial.println();
  Serial.println("closing connection"); 
  */
}

 

void loop()
{}
