void readDatosString(){
         
  String strUbidots  = "GET /api/v1.6/devices/gps/relay/lv HTTP/1.1\r\n";
         strUbidots += "Host: industrial.api.ubidots.com\r\n";
         strUbidots += "User-Agent: SIM900/1.1\r\n";
         strUbidots += "X-Auth-Token: " + X_Auth_Token + "\r\n";
         strUbidots += "Content-Type: application/json\r\n\r\n";

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
        //Serial.println(F(">"));
        //Serial.println(strUbidots);
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
        //Serial.print(strDat);
        //Serial.println(s);
        //strDat = "";
      }
      if(s>=21){
        Serial.println(strDat);
        int len = strDat.length();
        Serial.println(len);
        Serial.println(strDat[408]);
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
