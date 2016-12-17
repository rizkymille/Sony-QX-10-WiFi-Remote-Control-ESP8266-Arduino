#include <ESP8266WiFi.h>
//#include <ArduinoJson.h>

//stałe trzymane w pamięci flash
const char* TAKE_PICTURE_COMMAND PROGMEM = "{\"method\":\"actTakePicture\",\"params\":[],\"id\":1,\"version\":\"1.0\"}";
const char* ssid PROGMEM     = "DIRECT-9uQ0:DSC-QX10";
const char* password PROGMEM = "JFJPXKpc";
const char* host PROGMEM = "10.0.0.1";
const int httpPort PROGMEM = 10000;
//koniec stałych

//zmienne globalne
WiFiClient client;
//koniec zmiennych globalnych

//prototypy funkcji
void sendCommandToCamera(String command);
//koniec prototypów


//INICJALIZACJA
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

  //FPSTR robi z const char* String'a, przydatne ;) Czytaj tu: https://github.com/esp8266/Arduino/blob/master/doc/reference.md#progmem
  sendCommandToCamera(FPSTR(TAKE_PICTURE_COMMAND));
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

 
//PĘTLA GŁÓWNA
void loop()
{}


//DEKLARACJE FUNKCJI VVVV

void sendCommandToCamera(String command){
  
  Serial.print("Laczenie z adresem ");
  Serial.println(host);
  if (!client.connect(host, httpPort)) {
    Serial.println("polaczenie nieudane");
    return;
  }
  
  Serial.print("Wysylanie zapytania JSON ");
  // This will send the request to the server
  client.println("POST /sony/camera HTTP/1.1");
  client.println("Connection: close");
  client.println("Content-Type: application/json;charset=utf-8");
  client.print("Content-Length: ");
  client.println(command.length());
  client.println();
  client.println(command);

  //zaczekać na odpowiedź trza ;)
  delay(500);

  while(client.available()){
    Serial.print(client.read());
  }

  //zamknięcie połączenia.
  client.stop();
}

