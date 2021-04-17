#include <Wire.h>
#include "Adafruit_HDC1000.h"
#include <AP3216_WE.h>
#include <ESP8266WiFi.h>

//Se configura una instancia de los sensores
Adafruit_HDC1000 hdc = Adafruit_HDC1000();
AP3216_WE myAP3216 = AP3216_WE();

double VectorTemperatura[10];
double VectorLuz[10];
double VectorHumedad[10];

double PromLuz =0;
double PromTemp =0;
double PromHume =0;
  
//Configuracion Servidor
const char* ssid = "TP-Link_E1BA";
const char* password = "63669237";
//poner la direccion IP del servidor
const char* server = "54.221.189.38";

double latitud= 6.2455678;
double longitud= -75.4678888;
//double temperatura = 23;
double temperatura = 0;
double Humedad = 0;
double Luz = 0;
int id = 1001;

WiFiClient client;

void setup() {

  //Sensor de Humedad y Temperatura
  //Se inicializa la comunicación serial y se válida que se esté comunicando el sensor
  Serial.begin(115200);
  //Serial.println("HDC100x test");

  //Conexion con el servidor

  delay(10);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
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
  //FuncionImprimirDatos();
  FuncionPromedio();
  FuncionArmarTrama();

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
  
}

void FuncionTemperatura(){
  
  //Sensor de Temperatura
  
  //Se llena el vector con los datos del sensor de temperatura
  for(int i=0; i<10; i++){
    VectorTemperatura[i]=hdc.readTemperature();
    delay(500);
  }
 
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

  PromLuz = sumaLuz/10;
  PromTemp = sumaTemp/10;
  PromHume = sumaHume/10;
  
  Serial.print("El promedio de la luz es: "); Serial.print(PromLuz);
  Serial.print("\t\tEl promedio de la Temp es: "); Serial.print(PromTemp);
  Serial.print("\tEl promedio de la Hume es: "); Serial.println(PromHume);
}


void FuncionImprimirDatos(){
  
  Serial.println("................................................................................................................ ");
  for(int i=0; i<10; i++){
    Serial.print("El valorde la luz es: "); Serial.print(VectorLuz[i]);
    Serial.print("\t\tEl valor de la temp es: "); Serial.print(VectorTemperatura[i]);
    Serial.print("\t\tEl valor de la hume es:" ); Serial.println(VectorHumedad[i]);
  }
  
}


void FuncionArmarTrama(){

  String PostData = "";
  Serial.println("datos para enviar");
  PostData = String("id="+String(id)+"; temperatura="+String(PromTemp)+"; humedad="+String(PromHume)+"; luz="+String(PromLuz));
  Serial.println(PostData);
  if ( client.connect(server,80))
  {
    Serial.println("conectado");
    client.print("POST /sensor_send_data HTTP/1.1\n");
    // poner la direccion IP del servidor 
    client.print("Host: 192.168.0.101 \n");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(PostData.length());
    client.println();
    client.println(PostData);
  } else {
    Serial.println("error de conexion");
  }
}
