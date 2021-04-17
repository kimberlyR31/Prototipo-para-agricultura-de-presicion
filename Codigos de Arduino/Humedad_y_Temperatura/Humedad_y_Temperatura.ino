//Se importan las librerías
#include <Wire.h>
#include "Adafruit_HDC1000.h"

//Se configura una instancia del sensor
Adafruit_HDC1000 hdc = Adafruit_HDC1000();

void setup() {
  //Se inicializa la comunicación serial y se válida que se esté comunicando el sensor
  Serial.begin(9600);
  Serial.println("HDC100x test");
  
// se comprueba si el sensor está conectado y el Arduino lo puede encontrar
  if (!hdc.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
}


void loop() {
  //Imprime los valores que toma el sensor
  Serial.print("Temp: "); Serial.print(hdc.readTemperature());
  Serial.print("\t\tHum: "); Serial.println(hdc.readHumidity());
  delay(500);
}
