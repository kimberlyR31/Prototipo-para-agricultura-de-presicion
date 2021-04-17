#include <Wire.h>
#include "Adafruit_HDC1000.h"
#include <AP3216_WE.h>

//Se configura una instancia de los sensores
Adafruit_HDC1000 hdc = Adafruit_HDC1000();
AP3216_WE myAP3216 = AP3216_WE();

double VectorTemperatura[10];
double VectorLuz[10];
double VectorHumedad[10];


void setup() {

  //Sensor de Humedad y Temperatura
  //Se inicializa la comunicación serial y se válida que se esté comunicando el sensor
  Serial.begin(9600);
  //Serial.println("HDC100x test");
  
  
  // se comprueba si el sensor está conectado y el Arduino lo puede encontrar
  if (!hdc.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }

  //Sensor de Luz
  Wire.begin();
  myAP3216.init();
  myAP3216.setLuxRange(RANGE_20661);
  myAP3216.setPSGain(2);
  myAP3216.setNumberOfLEDPulses(1);
  myAP3216.setPSMeanTime(PS_MEAN_TIME_50);
  myAP3216.setPSThresholds(300, 800);
  myAP3216.setPSIntegrationTime(1);
  myAP3216.setPSInterruptMode(INT_MODE_HYSTERESIS);
  delay(1000);
}

void loop(){

  FuncionLuz();
  FuncionTemperatura();
  FuncionHumedad();
  FuncionImprimirDatos();
  FuncionPromedio();

}

void FuncionLuz(){
  
  //Sensor de Luz
  //Inicializa las variables que toma el sensor 
  float als = myAP3216.getAmbientLight();
  unsigned int prox = myAP3216.getProximity();
  unsigned int ir = myAP3216.getIRData(); // Ambient IR light
  bool isNear = myAP3216.objectIsNear();
  bool irIsValid = !myAP3216.irDataIsOverflowed();
  
  //Se llena el vector con los datos del sensor de luz
  for(int i=0; i<10; i++){
    VectorLuz[i]=als;
    delay(500);
  }
  
  //Serial.print("Lux: "); Serial.print(als);
  
}

void FuncionTemperatura(){
  
  //Sensor de Temperatura
  
  //Se llena el vector con los datos del sensor de temperatura
  for(int i=0; i<10; i++){
    VectorTemperatura[i]=hdc.readTemperature();
    delay(500);
  }
 
  /*Serial.print("\t\tTemp: "); Serial.print(hdc.readTemperature());
  Serial.print("\t\tHum: "); Serial.println(hdc.readHumidity());
  delay(1000);*/

}

void FuncionHumedad(){

  //Sensor de Humedad
  
  //Se llena el vector con los datos del sensor de humedad
  for(int i=0; i<10; i++){
    VectorHumedad[i]=hdc.readHumidity();
    delay(500);
  }  
  
}

void FuncionPromedio(){
  double sumaLuz =0;
  double sumaTemp =0;
  double sumaHume =0;
  
  for(int i=0; i<10; i++){
    sumaLuz += VectorLuz[i];
  }
  
  for(int i=0; i<10; i++){
    sumaTemp += VectorTemperatura[i];
  }
  
  for(int i=0; i<10; i++){
    sumaHume += VectorHumedad[i];
  }
  Serial.print("El promedio de la luz es: "); Serial.print(sumaLuz/10);
  Serial.print("\t\tEl promedio de la Temp es: "); Serial.print(sumaTemp/10);
  Serial.print("\tEl promedio de la Hume es: "); Serial.println(sumaHume/10);
}


void FuncionImprimirDatos(){
  
  Serial.println("................................................................................................................ ");
  for(int i=0; i<10; i++){
    Serial.print("El valorde la luz es: "); Serial.print(VectorLuz[i]);
    Serial.print("\t\tEl valor de la temp es: "); Serial.print(VectorTemperatura[i]);
    Serial.print("\t\tEl valor de la hume es:" ); Serial.println(VectorHumedad[i]);
  }
  
}
