// Sheila Firmware

/*
author: Adevan Neves Santos
dia: 18/01/2024
**/

#include "CO2Sensor.h"
#include "MQ7.h"
#include <DHT11.h>


// init MQ7 device
MQ7 mq7(34, 5);
CO2Sensor co2Sensor(35, 0.09, 100);
DHT11 dht11(4);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial connection
  }

  Serial.println("");   // blank new line

  Serial.println("Calibrating MQ7");
  mq7.calibrate();    // calculates R0
  co2Sensor.calibrate();
  Serial.println("Calibration done!");
}
 
void loop() {
  delay(1000);
  
  int temperature = dht11.readTemperature();
  delay(50);
  int humidity = dht11.readHumidity();
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT &&
        humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT)
    {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }
  Serial.print("CO: PPM = "); 
  Serial.print(mq7.readPpm());
  Serial.print(" CO2: PPM = "); 
  Serial.print(co2Sensor.read());
 
  Serial.println("");   // blank new line
}
