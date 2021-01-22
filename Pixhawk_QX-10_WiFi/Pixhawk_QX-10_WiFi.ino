/* credits to Andrej for the Sony QX-10 remote
 * source: https://github.com/kuczy/Sony-QX-10-WiFi-Remote-Control-ESP8266-Arduino/tree/master/Sony_QX-10_Remote
 */

#include <WiFi.h>
//#include <ArduinoJson.h>

//variables kept in flash memory
const char* StillMode PROGMEM = "{\"method\":\"setShootMode\",\"params\":[\"still\"],\"id\":1,\"version\":\"1.0\"}";
const char* HalfPressShutter PROGMEM = "{\"method\":\"actHalfPressShutter\",\"params\":[],\"id\":1,\"version\":\"1.0\"}";
const char* TakePicture PROGMEM = "{\"method\":\"actTakePicture\",\"params\":[],\"id\":1,\"version\":\"1.0\"}";
const char* MovieMode PROGMEM = "{\"method\":\"setShootMode\",\"params\":[\"movie\"],\"id\":1,\"version\":\"1.0\"}";
const char* StartMovie PROGMEM = "{\"method\":\"startMovieRec\",\"params\":[],\"id\":1,\"version\":\"1.0\"}";
const char* StopMovie PROGMEM = "{\"method\":\"stopMovieRec\",\"params\":[],\"id\":1,\"version\":\"1.0\"}";
const char* ssid PROGMEM     = "DIRECT-dUQ0:DSC-QX10";
const char* password PROGMEM = "NE8oHWt5";
const char* host PROGMEM = "10.0.0.1";
const int httpPort PROGMEM = 10000;
//camera trigger pin
const int camtrig = 13;
int camtrig_value;

//global variable
WiFiClient client;

//prototypes function
void sendCommandToCamera(String command);

//initialization
void setup() {
  //reading pwm trigger from pixhawk
  pinMode(camtrig, INPUT);
  
  Serial.begin(115200);
  delay(1000);

  //start by connecting to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to WiFi network: ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connection Active"); 
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
 
  //-----------------------
  delay(2000);
}

//main loop
void loop(){
  camtrig_value = pulseIn(camtrig, HIGH);
  if (camtrig_value > 1500){
    delay(100);
    sendCommandToCamera(HalfPressShutter);
    sendCommandToCamera(TakePicture);
  }
}

//function declarations
void sendCommandToCamera(String command){
  Serial.print("Linking to an adress ");
  Serial.println(host);
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
  
  Serial.print("Send a JSON inquiry ");
  //this will send the request to the server
  client.println("POST /sony/camera HTTP/1.1");
  client.println("Connection: close");
  client.println("Content-Type: application/json;charset=utf-8");
  client.print("Content-Length: ");
  client.println(command.length());
  client.println();
  client.println(command);

  //wait for the third answer
  delay(500);

  while(client.available()){
    Serial.print(client.read());
  }

  //close the connection
  client.stop();
}
