


#include <SoftwareSerial.h>
SoftwareSerial ESPSerial(2, 3); // RX, TX
#define DEBUG true

int x1=0;


#define CW 7 // CW se define como pin # 7 //

#define CCW 8 // CCW se define como pin # 8 //

float h;
float h1;
int gato;
int valor = 1023;
const size_t LengthData = 5;
float data[LengthData];
int ESP_Status, ESPenvio_Error, i1;



void setup() {
  Serial.begin(9600);
  ESPSerial.begin(9600);
  Serial.println("INICIANDO");
  pinMode (CW, OUTPUT); // Establecer CW como salida //
  pinMode (CCW, OUTPUT); // Establecer CCW como salida //
  
}
 
void loop() {
   // Crear array de datos para enviar al mñodulo ESP8266-01
   int lectura = analogRead(A0);
   int lecturaPorcentaje = map(lectura, 1023, 0, 0, 100);
   h = analogRead(A0)* 4.11 / 1023.00;

   h1=valor-h;
   gato=h1/100;
   gato=gato*10;  
   data[0] = lecturaPorcentaje;
   envioWIFI();
   Serial.println(lectura);
   Serial.println(lecturaPorcentaje);
   /* Serial.print("La lectura es: ");
  Serial.println(lectura);
  delay(1000);*/
////Convirtiendo a Porcentaje

   if (lectura <1000 && lectura >= 400){
    Serial.println(">> EL SUELO ESTA SECO <<");
    //delay(2000);
    digitalWrite (CW, LOW); // El motor funciona en sentido horario //
   // delay (2000); // por  segundo //
  } 
 
  else if (lectura <399 && lectura >= 0){
    Serial.println(">> EL SUELO ESTA HUMEDO <<");
    //delay(2000);
    digitalWrite (CW, HIGH); // El motor funciona en sentido horario //
    //delay (2000); // por  segundo //
 }
  
  delay(200);
}


/////////////////////////////////////////////////////////////////////////////////////////////

void envioWIFI() {
  ESP_Status = 404;
  delay(1000);
  ////////////// ENVIAR y RECIBIR ESP8266-01 //////////////
  ESPSerial.write((byte*)data, LengthData * sizeof(data[0]));  // Enviar array de datos por SoftwareSerial.h
  delay(7000);
  
  if (ESPSerial.available()) {
    ESP_Status = ESPSerial.parseInt();  // Leer canal SoftwareSerial.h
    if (ESP_Status != 200) ESPenvio_Error++;
    else ESPenvio_Error = 0;
  }
  
  ////////////// ENVIAR y RECIBIR ESP8266-01 //////////////
}
  
