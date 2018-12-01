/*
 * code sources:
 * sparkfun weather shield=https://learn.sparkfun.com/tutorials/arduino-weather-shield-hookup-guide-v12/all#example-firmware---weather-station
 *  ebidots/ethernet=https://github.com/ubidots/ubidots-arduino-ethernet
 *  mq sensors=http://www.waveshare.net/wiki/MQ-2_Gas_Sensor
*/



#include <Wire.h> // Every sensor except pressure and humidity
#include "SparkFunMPL3115A2.h" // Library for pressure sensor
#include "SparkFunHTU21D.h" // Library for humidity sensor
#include <Ethernet.h> // Ethernet Library
#include <SPI.h> // Ethernet Library
#include <UbidotsEthernet.h> // Ethernet Library
MPL3115A2 myPressure; // Create an instance of the pressure sensor
HTU21D myHumidity; // Create an instance of the humidity sensor

// digital I/O pins
const byte RAIN = 2;
const byte WSPEED = 3;
const byte STAT1 = 7;
const byte STAT2 = 8;
int MQ2_Digital=14; // Mq2 digital pin
int MQ3_Digital=15; // Mq3 digital pin
int MQ5_Digital=16; // Mq5 digital pin
int MQ7_Digital=17; // Mq7 digital pin

// analog I/O pins
const byte WDIR = A0;
const byte LIGHT = A1;
const byte REFERENCE_3V3 = A3;
int mq2_Analog=A6;
int mq3_Analog=A7;
int mq5_Analog=A8;
int mq7_Analog=A9;

/* Assigns the Ubidots parameters */
char const * TOKEN = "BBFF-3DFR4ALeoNl67p5yqsM8wGH1WnyiLI"; // Assign your Ubidots TOKEN
char const * VARIABLE_LABEL_1 = "tempf"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_2 = "winddir"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_3 = "windspeedmph"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_4 = "humidity"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_5 = "dailyrainin"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_6 = "Pressure_Pa"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_7 = "light_V"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_8 = "MQ2_Analog"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_9 = "MQ3_Analog"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_10 = "MQ5_Analog"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_11 = "MQ7_Analog"; // Assign the unique variable label to send the data
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress ip(192,168,6,50); 
/* initialize the instance */
Ubidots client(TOKEN);



//----------------------------------------------------------------------------------------
long lastSecond; //The millis counter to see when a second rolls by
byte seconds; //When it hits 60, increase the current minute
byte minutes; //Keeps track of where we are in various arrays of data
long lastWindCheck = 0;
volatile long lastWindIRQ = 0;
volatile byte windClicks = 0;
int Wind_Direction = 0; // [0-360 instantaneous wind direction]
float Wind_Speed_mph = 0; // [mph instantaneous wind speed]
float humidity = 0; // [%]
float Temperature_C = 0; // [temperature C]
volatile float Rain_inches = 0; // [rain inches so far today in local time]
float Pressure_Pa = 0;
float light_V = 455; //[analog value from 0 to 1023]
volatile unsigned long raintime, rainlast, raininterval, rain;



//-------------Interrupt routines (these are called by the hardware interrupts, not by the main code)-------------//
void rainIRQ(){
  raintime = millis(); // grab current time
  raininterval = raintime - rainlast; // calculate interval between this and last event
  if (raininterval > 10) // ignore switch-bounce glitches less than 10mS after initial edge
  {
    Rain_inches += 0.011; //Each dump is 0.011" of water
    rainlast = raintime; // set up for next event
  } //if
} //rainIRQ

void wspeedIRQ()
{
  if (millis() - lastWindIRQ > 10) // Ignore switch-bounce glitches less than 10ms (142MPH max reading) after the reed switch closes
  {
    lastWindIRQ = millis(); //Grab the current time
    windClicks++; //There is 1.492MPH for each click per second.
  } //if
} //wspeedIRQ
