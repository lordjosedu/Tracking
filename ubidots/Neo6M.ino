
void gps_data () {

  if (gps.location.isUpdated())
  {
    Serial.print(F("Lat="));
    Serial.print(gps.location.lat(), 6);
    anArray[0] = gps.location.lat();
    Serial.print(F(" Long="));
    Serial.println(gps.location.lng(), 6);
    anArray[1] = gps.location.lng();
  } if (gps.speed.isUpdated())
  {
    Serial.print(F("km/h="));
    Serial.println(gps.speed.kmph());
    anArray[2] = gps.speed.kmph();
  } if (gps.satellites.isUpdated())
  {
    Serial.print(F("Value="));
    Serial.println(gps.satellites.value());
    anArray[3] = gps.satellites.value();
  } if(anArray[0] == 0 && anArray[1] == 0){
    Serial.println("No GPS");
    counter = 0; 
  }
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (Serial2.available())
      gps.encode(Serial2.read());
  } while (millis() - start < ms);
  counter = counter + 1;
  Serial.println(counter);
}
