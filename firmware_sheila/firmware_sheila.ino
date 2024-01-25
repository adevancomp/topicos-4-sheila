// Sheila Firmware

/*
author: Adevan Neves Santos
day: 18/01/2024

Data e Hora,Concentração de CO,Concentração de CO2,Umidade (%),Temperatura (°C)

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

  Serial.println("Calibrating MQ7 and co2 sensor");
  mq7.calibrate();    // calculates R0
  co2Sensor.calibrate();
  Serial.println("Calibration done!");
}
 
void loop() {
  delay(1000);
  
  double temperature = dht11.readTemperature();
  delay(50);
  double humidity = dht11.readHumidity();
  delay(10);
  double co = mq7.readPpm();
  delay(10);
  double co2 = co2Sensor.read();
  
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT &&
        humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT)
    {
        /*Data e Hora,Concentração de CO,Concentração de CO2,Umidade (%),Temperatura (°C)*/
        Serial.print("2023-12-01 00:00:00");
        Serial.print(",");
        Serial.print(co);
        Serial.print(",");
        Serial.print(co2);
        Serial.print(",");
        Serial.print(humidity);
        Serial.print(",");
        Serial.print(temperature);
        Serial.println(""); // linha em branco
    }
}
