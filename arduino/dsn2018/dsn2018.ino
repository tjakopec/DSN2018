#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// KONSTANTE
const char mreza[] = "xxxx";  
const char mrezaLozinka[] = "xxxx"; 
const char apiURL[] = "http://dweet.io/get/latest/dweet/for/dsn2018"; 

const int ledPin = 5; //D1
const int onlinePin = 4; //D2
const int wifiPin = 0; //D3



void setup() {
  pinMode(onlinePin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(wifiPin,OUTPUT);
  Serial.begin(9600);                           
  spojiWIFI();

  
}
 
void loop() {

  odradiAPIupit();
  /*
  digitalWrite(ledPin, LOW);
  digitalWrite(onlinePin, HIGH);
  Serial.println("---------");
  delay(1000); 
  digitalWrite(ledPin, HIGH);
  digitalWrite(onlinePin, LOW);
  delay(1000);
*/
delay(10000); 
  if(WiFi.status()==3){
    digitalWrite(wifiPin,LOW);
  }
  else
    digitalWrite(wifiPin,HIGH);
}

void odradiAPIupit(){
  HTTPClient http;
  http.begin(apiURL);
  int httpCode = http.GET();
  if (httpCode==HTTP_CODE_OK){
    String vratioDweet = http.getString();
    Serial.println(vratioDweet);
    StaticJsonBuffer<400> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(vratioDweet);
    const char* klima = root["with"][0]["content"]["klima"];
    Serial.print("klima -> ");
    Serial.println(klima);
    const char* rasvjeta = root["with"][0]["content"]["rasvjeta"];
    Serial.print("rasvjeta -> ");
    Serial.println(rasvjeta);
    const char* grijanje = root["with"][0]["content"]["grijanje"];
    Serial.print("grijanje -> ");
    Serial.println(grijanje);
    
  }
  
  http.end();  //Close connection
}

void spojiWIFI(){
  Serial.println("Spajanje na Wifi...");
  WiFi.begin(mreza, mrezaLozinka); 
  digitalWrite(onlinePin, LOW);
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi spojen");
  Serial.print("IP adresa: ");
  Serial.println(WiFi.localIP());
  
}

