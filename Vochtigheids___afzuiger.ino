#include "BlynkSimpleEsp8266.h"
#include "DHT.h"
#include "Adafruit_Sensor.h"
#include <ESP8266WiFi.h>
String apiKey = "4BE2313OW8ZDU5UM"; // voor thingspeak
char auth[] = "_7wI68g9Oz2iJ_TIaJ528NItwC8gchf9"; // voor de blynk app
char ssid[] = "HKWLAN01"; // Enter Your WiFi Name
char pass[] = "%ketelaarWLAN02%"; // Enter Your Passwword
const char* server = "api.thingspeak.com";

#define DHTTYPE DHT22
#define DHTPIN 14 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timerSensor; // timer gebruik makend van de blynk functionaliteit
#define led 15
WiFiClient client;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
    
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
  
if(h >= 50)
  {
  digitalWrite(led, HIGH);
  } 
else 
  {
  digitalWrite(led, LOW);
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
  //pinMode(led2, OUTPUT);
  pinMode(led, OUTPUT);
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
  
  Blynk.run();
  timerSensor.run();
  
}
