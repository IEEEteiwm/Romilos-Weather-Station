void calcWeather()
{
  Wind_Direction = get_wind_direction(); // Calculates wind direction
  humidity = myHumidity.readHumidity();// Calculates humidity
 // Temperature_C = (myPressure.readTempF()-32)*5/9;  // Calc temperature from pressure sensor
  Temperature_C = myHumidity.readTemperature();  // Calc temperature from humidity sensor
  Pressure_Pa = myPressure.readPressure();  // Calculates pressure
  light_V = get_light_level(); // Calculates light level
} //calcWeather

float get_light_level()
{
  float operatingVoltage = analogRead(REFERENCE_3V3);
  float lightSensor = analogRead(LIGHT);
  operatingVoltage = 3.3 / operatingVoltage; //The reference voltage is 3.3V
  lightSensor = operatingVoltage * lightSensor;
  return(lightSensor);
} //get_light_level

float get_wind_speed()
{
  float deltaTime = millis() - lastWindCheck; //750ms
  deltaTime /= 1000.0; //Covert to seconds
  float windSpeed = (float)windClicks / deltaTime; //3 / 0.750s = 4
  windClicks = 0; //Reset and start watching for new wind
  lastWindCheck = millis();
  windSpeed *= 1.492; //4 * 1.492 = 5.968MPH
  return(windSpeed);
} //get_wind_speed

int get_wind_direction()
{
  unsigned int adc;
  adc = analogRead(WDIR); // get the current reading from the sensor
  if (adc < 380) return (113);
  if (adc < 393) return (68);
  if (adc < 414) return (90);
  if (adc < 456) return (158);
  if (adc < 508) return (135);
  if (adc < 551) return (203);
  if (adc < 615) return (180);
  if (adc < 680) return (23);
  if (adc < 746) return (45);
  if (adc < 801) return (248);
  if (adc < 833) return (225);
  if (adc < 878) return (338);
  if (adc < 913) return (0);
  if (adc < 940) return (293);
  if (adc < 967) return (315);
  if (adc < 990) return (270);
  return (-1); // error, disconnected?
} //get_wind_direction
