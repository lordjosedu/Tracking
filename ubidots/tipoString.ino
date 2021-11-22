void enviarDatosString(float longitud, float latitud,float velocidad, float satelites){
  //      "{"dato1":xxxx,"dato2":yyyy}";
  //      "{\"dato1\":xxxx,\"dato2\":yyy}";
  char str_val_1[30];
  char str_val_2[30];
  char str_val_3[30];
  
  dtostrf(longitud, 8, 6, str_val_1);
  dtostrf(latitud, 8, 6, str_val_2);
  dtostrf(velocidad, 4, 2, str_val_3);
  
/* String aux  = "{\"longitud\":";
         aux +=  str_val_1; 
         aux += ",\"latitud\":"; 
         aux +=  str_val_2;
         aux += ",\"velocidad\":"; 
         aux +=  str_val_3;       
         aux += ",\"satelites\":"; 
         aux +=  satelites;       
         aux += "}";*/
         String aux  = "{\"position\":{";
         aux += "\"latitude\":"; 
         aux +=  str_val_2;
         aux += ",\"longitude\":"; 
         aux +=  str_val_1;       
         aux += "}";
         aux += ",\"velocidad\":";
         aux +=  str_val_3; 
         aux += ",\"satelites\":"; 
         aux +=  satelites;
         aux += "}";
         
  String strUbidots  = "POST /api/v1.6/devices/gps HTTP/1.1\r\n";
         strUbidots += "Host: 169.55.61.243\r\n";
         strUbidots += "User-Agent: SIM900/1.1\r\n";
         strUbidots += "X-Auth-Token: " + X_Auth_Token + "\r\n";
         strUbidots += "Content-Type: application/json\r\n";
         strUbidots += "Content-Length: " + String(aux.length()) + "\r\n";
         strUbidots += "\r\n" + aux + "\r\n";
  Serial.println("************* STRING ************* ");
  Serial.print(strUbidots);  
  int tam = strUbidots.length();
  String strTam;
  strTam =+ tam; 

  Serial.println("AT+CIPSTART=\"TCP\",\"169.55.61.243\",80");
  Serial1.println("AT+CIPSTART=\"TCP\",\"169.55.61.243\",80");
  unsigned long timeEnviarDato = millis();
  while(1){
    if(Serial1.find("CONNECT OK")){
      Serial.println(F("CONNECT OK"));
      server = true;
      break;
    }
    if((unsigned long)(millis() - timeEnviarDato)>5000){
      Serial.println(F("NO CONNECT"));
      server = false;
      timeEnviarDato = millis();
      break;
    }
  }
  
  if(server){
    Serial.println("AT+CIPSEND="+strTam);
    Serial1.println("AT+CIPSEND="+strTam);
    timeEnviarDato = millis();
    while(1){
      if(Serial1.find(">")){
        Serial.println(F(">"));
        Serial.println(strUbidots);
        Serial1.print(strUbidots);
        break;
      }
      if((unsigned long)(millis() - timeEnviarDato)>5000){
        Serial.println(F("NO >"));
        timeEnviarDato = millis();
        break;
      }
    }
  } 
  strTam = "";
  server = false;
  String strDat;
  int s = 0;
  unsigned long timeReceiveData = millis();
  while(1){
    if(Serial1.available()){
      char dat = Serial1.read();
      strDat += dat;
      if (dat == '\n'){
        s++;
        Serial.print(strDat);
        //Serial.println(s);
        strDat = "";
      }
      if(s>=23){
        Serial.println(F("Datos recibidos del servidor"));
        break;
      } 
    }
    if((unsigned long)(millis() - timeReceiveData)>6000){
      Serial.println(F("No hay datos recibidos del servidor"));
      timeReceiveData = millis();
      break;
    }
  }
  Serial1.println("AT+CIPCLOSE");
  delay(500);
  Serial1.println("AT+CIPSHUT");
  delay(500);
}
