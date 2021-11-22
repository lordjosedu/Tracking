#include <SoftwareSerial.h>
#include <TinyGPS++.h>

static const uint32_t GPSBaud = 9600;
static const uint32_t GSMBaud = 9600;
TinyGPSPlus gps;
unsigned long last = 0UL;

boolean server = false;
unsigned long timeEnviarDato = 0;
String X_Auth_Token = "BBFF-NvydzqXDENAQyfB5cerIm975ypgeBI";

float anArray[4];
int counter = 0;
String inData;
char inchar; 

void setup() {
  Serial.begin(9600);
  Serial1.begin(GSMBaud);
  iniciarSim900();
  delay(3000);
  Serial.println("SIM900 CONFIGURADO");
  Serial2.begin(GPSBaud);
  delay(3000);
  Serial.println("GPS CONFIGURADO");
  
}

void loop() {
    smartDelay(1000);
    gps_data();
  if (counter >= 60) {
    enviarDatosString(anArray[1], anArray[0], anArray[2], anArray[3]);
    counter = 0;
  }
}
