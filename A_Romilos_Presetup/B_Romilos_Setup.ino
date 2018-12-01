void setup(){
  pinMode(WSPEED, INPUT_PULLUP);; // Input from windspeed sensor
  pinMode(RAIN, INPUT_PULLUP); // Input from rain gauge sensor
  pinMode(STAT1, OUTPUT); //Status LED Blue
  pinMode(STAT2, OUTPUT); //Status LED Green  
  pinMode(MQ2_Digital,INPUT); // Input from mq2 digital pin
  pinMode(MQ3_Digital,INPUT); // Input from mq3 digital pin
  pinMode(MQ5_Digital,INPUT); // Input from mq5 digital pin
  pinMode(MQ7_Digital,INPUT); // Input from mq7 digital pin
  pinMode(LIGHT, INPUT); // Input from light sensor
  pinMode(REFERENCE_3V3, INPUT);  // Input from 
  pinMode(mq2_Analog,INPUT); // Input from mq2 analog pin
  pinMode(mq3_Analog,INPUT); // Input from mq3 analog pin
  pinMode(mq5_Analog,INPUT); // Input from mq5 analog pin  
  pinMode(mq7_Analog,INPUT); // Input from mq7 analog pin

  Serial.begin(9600);

  if (!Ethernet.begin(mac))
  {
     Serial.println(F("failed"));
  } 
  else 
   {
     Serial.println(Ethernet.localIP());
   }
  delay(2000);

  //Configure the pressure sensor
  myPressure.begin(); // Get sensor online
  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags

  //Configure the humidity sensor
  myHumidity.begin();
  seconds = 0;
  lastSecond = millis();

  // attach external interrupt pins to IRQ functions
  attachInterrupt(0, rainIRQ, FALLING);
  attachInterrupt(1, wspeedIRQ, FALLING);

  // turn on interrupts
  interrupts();
}
