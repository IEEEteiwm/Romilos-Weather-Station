void printWeather()
{
  Serial.println();
  Serial.print("$,Wind_Direction=");
  Serial.print(Wind_Direction);
  Serial.print(",windspeedmph=");
  Serial.print(Wind_Speed_mph, 1);
  Serial.print(",humidity=");
  Serial.print(humidity, 1);
  Serial.print(",Temperature_C=");
  Serial.print(Temperature_C, 1);
  Serial.print(",Rain_inches=");
  Serial.print(Rain_inches, 2);
  Serial.print(",pressure=");
  Serial.print(Pressure_Pa, 2);
  Serial.print(",light_lvl=");
  Serial.print(light_V, 2);
//========================================__MQ-X__========================================
  if(digitalRead(MQ2_Digital)==LOW){Serial.print(",MQ-2 leakage=");Serial.print(analogRead(mq2_Analog));}
  else{Serial.print(",MQ-2 not leak");}
  if(digitalRead(MQ3_Digital)==LOW){Serial.print(",MQ-3 leakage=");Serial.print(analogRead(mq3_Analog));}
  else{Serial.print(",MQ-3 not leak");}
  if(digitalRead(MQ5_Digital)==LOW){Serial.print(",MQ-5 leakage=");Serial.print(analogRead(mq5_Analog));}
  else{Serial.print(",MQ-5 not leak");}
  if(digitalRead(MQ7_Digital)==LOW){Serial.print(",MQ-7 leakage=");Serial.print(analogRead(mq7_Analog));}
  else{Serial.print(",MQ-7 not leak");}
//========================================================================================
}
