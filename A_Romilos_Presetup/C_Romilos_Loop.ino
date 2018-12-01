void loop(){
  //Keep track of which minute it is
  if(millis() - lastSecond >= 1000)  
  {
    digitalWrite(STAT1, HIGH); //Blink stat LED
    lastSecond += 1000;
    int mq2_value=analogRead(mq2_Analog);
    int mq3_value=analogRead(mq3_Analog);
    int mq5_value=analogRead(mq5_Analog);
    int mq7_value=analogRead(mq7_Analog);    
    float currentSpeed = get_wind_speed();
    Wind_Speed_mph = currentSpeed; //update global variable for windspeed when using the printWeather() function
    int currentDirection = get_wind_direction();
    calcWeather();
    printWeather();//#debug
    digitalWrite(STAT1, LOW); //Turn off stat LED
  } //if
  delay(100);
  
  Ethernet.maintain();
  /* Sending values to Ubidots */
    client.add(VARIABLE_LABEL_1, Temperature_C);
    client.add(VARIABLE_LABEL_2, Wind_Direction);
    client.add(VARIABLE_LABEL_3, Wind_Speed_mph);
    client.add(VARIABLE_LABEL_4, humidity);
    client.add(VARIABLE_LABEL_5, Rain_inches);
  client.sendAll();
    client.add(VARIABLE_LABEL_6, Pressure_Pa);
    client.add(VARIABLE_LABEL_7, light_V);
    client.add(VARIABLE_LABEL_8, mq2_Analog);
    client.add(VARIABLE_LABEL_9, mq3_Analog);
    client.add(VARIABLE_LABEL_10, mq5_Analog);    
  client.sendAll();
    client.add(VARIABLE_LABEL_11, mq7_Analog);      
  client.sendAll();
  delay(5000);
} //void loop
