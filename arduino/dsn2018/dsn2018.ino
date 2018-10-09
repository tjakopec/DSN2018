#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// KONSTANTE
const char mreza[] = "xxxxx";  
const char mrezaLozinka[] = "xxxxx"; 
const char apiURL[] = "http://dweet.io/get/latest/dweet/for/dsn2018"; //URL od dweet API

const int klimaPin = 5; //D1 CREVNO
const int rasvjetaPin = 4; //D2 BIJELO
const int grijanjePin = 0; //D3 PLAVO
const char* upaljeno="1"; //vrijednost u JSON
const int ledUpaljen= LOW;
const int ledUgasen= HIGH;
const int intervalAPI=5000;//milisekundi


void setup() {
  pinMode(klimaPin,OUTPUT);
  pinMode(grijanjePin,OUTPUT);
  pinMode(rasvjetaPin,OUTPUT);
  digitalWrite(klimaPin,ledUgasen);
  digitalWrite(grijanjePin,ledUgasen);
  digitalWrite(rasvjetaPin,ledUgasen);
  Serial.begin(9600);                           
  spojiWIFI();
}
 
void loop() {
  odradiAPIupit();
  delay(intervalAPI); 
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
    digitalWrite(klimaPin, strcmp(klima,upaljeno)==0 ? ledUpaljen : ledUgasen);


    
    const char* rasvjeta = root["with"][0]["content"]["rasvjeta"];
    /*
    Serial.print("rasvjeta ->");
    Serial.print(rasvjeta);
    Serial.print("==");
    Serial.print(upaljeno);
    Serial.println("<");
    Serial.println(rasvjeta==upaljeno);
    */
    digitalWrite(rasvjetaPin, strcmp(rasvjeta,upaljeno)==0 ? ledUpaljen : ledUgasen);
    /*
    if(rasvjeta==upaljeno){
       digitalWrite(rasvjetaPin,ledUpaljen);
    }else{
       digitalWrite(rasvjetaPin,ledUgasen);
    }
    */

    
    const char* grijanje = root["with"][0]["content"]["grijanje"];
    digitalWrite(grijanjePin, strcmp(grijanje,upaljeno)==0 ? ledUpaljen : ledUgasen);
   
    
  }
  
  http.end();  //Close connection
}

void spojiWIFI(){
  Serial.println("Spajanje na Wifi...");
  WiFi.begin(mreza, mrezaLozinka); 
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi spojen");
  Serial.print("IP adresa: ");
  Serial.println(WiFi.localIP());
  
}

