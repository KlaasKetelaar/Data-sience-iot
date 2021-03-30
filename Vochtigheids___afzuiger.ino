#include "BlynkSimpleEsp8266.h"
#include "DHT.h"
#include "Adafruit_Sensor.h"
char auth[] = "_7wI68g9Oz2iJ_TIaJ528NItwC8gchf9";
char ssid[] = "HKWLAN01"; // Enter Your WiFi Name
char pass[] = "%ketelaarWLAN02%"; // Enter Your Passwword

#define DHTTYPE DHT22
#define DHTPIN 14 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timerSensor;
#define led 15



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
  Blynk.virtualWrite(V0, t); // Virtual Pin V5 for Temprature
  Blynk.virtualWrite(V1, h); // Virtual Pin V6 for Humidity
  
if(h >= 50)
  {
  digitalWrite(led, HIGH);
  } 
else 
  {
  digitalWrite(led, LOW);
  }

  
}
void setup()
{ 
  //pinMode(led2, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  dht.begin(); 
  timerSensor.setInterval(2000L, sendSensor);
  Blynk.begin(auth, ssid, pass);
}

  void loop()
{
  
  Blynk.run();
  timerSensor.run();
  
}
