void iniciarSim900() {
  int respuesta = 0;
  if (enviarAT("AT", "OK", 2000) == 0) {
    delay(2000);
    while (respuesta == 0) {
      powerUp();
      respuesta = enviarAT("AT", "OK", 2000);
      Serial1.println(respuesta);
    }
  }
  while (enviarAT("AT+CREG?", "+CREG: 0,1", 1000) == 0 ) {
  }
  Serial.println(F("Conectado a la red."));
  enviarAT("AT+CLIP=1\r", "OK", 1000); // Activamos la identificacion de llamadas
  enviarAT("AT+CMGF=1\r", "OK", 1000); //Configura el modo texto para enviar o recibir mensajes
  enviarAT("AT+CNMI=2,2,0,0,0\r", "OK", 1000);
  enviarAT("AT+CGATT=1\r", "OK", 1000);
  enviarAT("AT+CSTT=\"Internet Tuenti\",\"tuenti\",\"tuenti\"", "OK", 3000); //Definimos el APN, usuario y clave a utilizar
  enviarAT("AT+CIICR", "OK", 3000); //Activamos el perfil de datos inalámbrico
  enviarAT("AT+CIFSR", "OK", 3000); //Obtenemos una direccion ip
  enviarAT("AT+CCLK?", "OK", 3000); //Obtenemos datos del RTC
  enviarAT("AT+CLTS=?", "OK", 3000); //Obtenemos local timestamp
  enviarAT("AT+CSQ", "OK", 3000); //Obtenemos calidad de red

}

int enviarAT(String ATcommand, char* resp_correcta, unsigned int tiempo) {
  int x = 0;
  bool correcto = 0;
  char respuesta[100];
  unsigned long anterior;
  memset(respuesta, '\0', 100);
  delay(100);
  while (Serial1.available() > 0) Serial1.read();
  Serial1.println(ATcommand);
  x = 0;
  anterior = millis();
  do {
    if (Serial1.available() != 0) {
      respuesta[x] = Serial1.read();
      x++;
      if (strstr(respuesta, resp_correcta) != NULL) {
        correcto = 1;
      }
    }
  } while ((correcto == 0) && ((millis() - anterior) < tiempo));
  Serial.println(respuesta);
  return correcto;
}

void sendSMS() {
  Serial1.print("AT+CMGS=");     // Send the SMS number. To whome message to send.
  Serial1.print("\"+593980237994\"");
  Serial1.println();
  delay(100);
  Serial1.print("http://maps.google.com/maps?q=loc:");
  Serial1.print(anArray[0]);
  Serial1.print(",");
  Serial1.print(anArray[1]);
  delay(100);
  Serial1.println((char)26);
  delay(100);
  Serial1.println();
}
void powerUp()
{
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  delay(1000);
  digitalWrite(9, HIGH);
  delay(2000);
  digitalWrite(9, LOW);
  delay(10000);
}
