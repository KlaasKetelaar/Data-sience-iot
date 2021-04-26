

Door Klaas Ketelaar

# Data-sience-iot


Git pagina vooor het vak Data sience & iot

mijn idee: Met een vochtigheids sensor en de blynk app/feature die je kan implementeren op een arduino de sensor uitlezen, 
ook maak ik gebruik van thingspeak voor overzichtelijke uitlezing van de sensor. 
Met deze data wil ik uiteindelijk een ventilator aansturen zodat het bij mij in de badkamer niet te vochtig wordt, 
je kan dus de vochtigheidsgraad aanpassen (dus wanneer de ventilator aan gaat) hierbij kan je rekening houden met het jaargetijde.
in de zomer is het over het algemeen minder vochtig maar stel je gaat douchen dan wil je wel dat de ventilator aan gaat.

Onderdelen: 
Wemos D1 mini (ESP-8266),  
DHT22 vochtigheids sensor,  
Relais SRD-5VDC aansturing ventilator,  
LED voor simulatie van de ventilator,  
NPN transistor  
Diode  
1K ohm weerstand en 510 ohm weertstand,  
aantal kabeltjes  

het relais heb ik aangesloten met een diode en een transistor de diode zorgt er voor dat er geen stroom de verkeerde kant opgaat,  
en de transistor zorgt er voor dat er een sterk genoeg signaal vanuit de arduino (WeMos) komt zodat het relais dit kan oppikken.  

dit is de fritzing van het projectje

![fritzing](https://user-images.githubusercontent.com/79268762/116126980-909f6500-a6c7-11eb-89b5-e5c2ed0738bd.JPG)

een simpele flow of control dat laat zien hoe alles wordt aangestuurd en verstuurd:

![IoT flow](https://user-images.githubusercontent.com/79268762/116127344-00155480-a6c8-11eb-9f8a-d1f108194fda.JPG)


dit is de thingspeak in praktijk ook heb ik nog uitgebreider uitleg gegeven in de filmpjes:

![thingspeak](https://user-images.githubusercontent.com/79268762/116127213-dbb97800-a6c7-11eb-9666-6d6db12bf850.JPG)

