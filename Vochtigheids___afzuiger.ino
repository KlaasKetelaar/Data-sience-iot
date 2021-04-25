#include "BlynkSimpleEsp8266.h"
#include "DHT.h"
#include "Adafruit_Sensor.h"
#include <ESP8266WiFi.h>
String apiKey = ""; // voor thingspeak
char auth[] = ""; // voor de blynk app
char ssid[] = ""; // Enter Your WiFi Name
char pass[] = ""; // Enter Your Passwword
const char* server = "api.thingspeak.com";

unsigned long previousMillis = 0; // voor de timer van de ventilator zodat hij aan blijft nadat het onder het vochtniveau is.
unsigned long startMillis;  // 
const unsigned long naDraai = 90000; // na draai timer die je zelf kan instellen 

#define DHTTYPE DHT22 // initializeren van de temp en vochtigheids sensor
#define DHTPIN 14  // pin van de vochtigheidssensor
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timerSensor; // timer gebruik makend van de blynk functionaliteit
#define relais 16 // pin van de relais
WiFiClient client;


void sendSensor()
{
  unsigned long currentMillis = millis();
  float h = dht.readHumidity(); // read van de vochtigheid
  float t = dht.readTemperature(); // read van de temp
    
      if (isnan(h) || isnan(t))
      {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }
      else
          {
//             Serial.print("Humidity: "); 
//             Serial.print(h);
//             Serial.print(" %\t");
//             Serial.print("Temperature: "); 
//             Serial.print(t);
//             Serial.println(" *C");           
          }  
  Blynk.virtualWrite(V0, t); // Virtual Pin V5 for Temprature, blynk app configuratie
  Blynk.virtualWrite(V1, h); // Virtual Pin V6 for Humidity
  
if(h >= 30) // als vochtigheid > 30 (dit kan je zelf instellen) , laat het relais bekrachtigen
  {
  digitalWrite(relais, HIGH);
  } 
else if(currentMillis - previousMillis >= naDraai) // na de zelf ingestelde na draai tijd en als de vochtigheid te laag is dan gaat het relais uit 
  {
      digitalWrite(relais, LOW);
      previousMillis = currentMillis;
    
  }

  if (client.connect(server,80)) { // api connect van thingspeak
String postStr = apiKey;
postStr +="&field1=";
postStr += String(t);
postStr +="&field2=";
postStr += String(h);
postStr += "\r\n\r\n";
 
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);
 
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" degrees Celsius Humidity: ");
Serial.print(h);
Serial.println("Sending data to Thingspeak");
}
client.stop();
 

  
}
void setup()
{ 
  pinMode(relais, OUTPUT);
  Serial.begin(9600);
  dht.begin(); 
  timerSensor.setInterval(20000L, sendSensor);// delay voor thingspeak
  Blynk.begin(auth, ssid, pass);
  WiFi.begin(ssid, pass);

  WiFi.begin(ssid, pass);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, pass);
   
  while (WiFi.status() != WL_CONNECTED) 
  {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

  void loop()
{
  
  Blynk.run(); // run voor de blynk app.
  timerSensor.run();
  
}
