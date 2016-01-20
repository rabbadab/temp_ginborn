// This #include statement was automatically added by the Particle IDE.
#include "OneWire/OneWire.h"
#include "spark-dallas-temperature/spark-dallas-temperature.h"
#include "SparkCorePolledTimer/SparkCorePolledTimer.h"

#define ONE_WIRE_BUS D4 // Data wire is plugged into pin D0 on the particle
#define TEMPERATURE_PRECISION 12         // DS18B20 Thermometer Stuff
OneWire oneWire(ONE_WIRE_BUS);          // DS18B20 Thermometer Stuff
DallasTemperature sensors(&oneWire);    // DS18B20 Thermometer Stuff


SparkCorePolledTimer updateTimer(25000); //Create a timer object and set it's timeout in milliseconds
void OnTimer(void); //Prototype for timer callback method

DeviceAddress Thermometer1 = { 0x28, 0xD2, 0x18, 0xF1, 0x4, 0x0, 0x0, 0x96 };
DeviceAddress Thermometer2 = { 0x28, 0x1E, 0x20, 0xF2, 0x4, 0x0, 0x0, 0x46 };
DeviceAddress Thermometer3 = { 0x28, 0xE5, 0xDB, 0xF1, 0x4, 0x0, 0x0, 0x92 };
DeviceAddress Thermometer4 = { 0x28, 0xFF, 0x9E, 0x93, 0x61, 0x15, 0x2, 0x95 };
DeviceAddress Thermometer5 = { 0x28, 0xFF, 0xB, 0x81, 0x61, 0x15, 0x2, 0xCF };


double InTempC = -1;
double Temp1 = -1;
double Temp2 = -1;
double Temp3 = -1;
double Temp4 = -1;
double Temp5 = -1;

void update18B20Temp(DeviceAddress deviceAddress, double &tempC);


char resultstr[256]; //String to store the sensor data

void setup(){
  Serial.begin(9600);
  updateTimer.SetCallback(OnTimer);

    // DS18B20 initialization
    sensors.begin();
    sensors.setResolution(Thermometer1, TEMPERATURE_PRECISION);
    sensors.setResolution(Thermometer2, TEMPERATURE_PRECISION);
    sensors.setResolution(Thermometer3, TEMPERATURE_PRECISION);
    sensors.setResolution(Thermometer4, TEMPERATURE_PRECISION);
    sensors.setResolution(Thermometer5, TEMPERATURE_PRECISION);



    delay(5000); // Allow board to settle

  Particle.variable("result", resultstr, STRING);  //Spark variable "result" to store sensor data string

}

void loop()
  {
    updateTimer.Update();
  }

void OnTimer(void)
    { //Handler for the timer, will be called automatically
        // DS18B20
    sensors.requestTemperatures();

    update18B20Temp(Thermometer1, InTempC);
    if ( InTempC > -123)
      {
      Temp1 = InTempC;
      }else{
        update18B20Temp(Thermometer1, InTempC);
        Temp1 = InTempC;
    }
    delay(3000);

    update18B20Temp(Thermometer2, InTempC);
      if ( InTempC > -123)
        {
          Temp2 = InTempC;
        }else{
          update18B20Temp(Thermometer2, InTempC);
          Temp2 = InTempC;
        }
    delay(3000);

    update18B20Temp(Thermometer3, InTempC);
      if ( InTempC > -123)
        {
          Temp3 = InTempC;
        }else{
          update18B20Temp(Thermometer3, InTempC);
          Temp3 = InTempC;
        }
    delay(3000);

    update18B20Temp(Thermometer4, InTempC);
      if ( InTempC > -123)
        {
          Temp4 = InTempC;
        }else{
          update18B20Temp(Thermometer4, InTempC);
          Temp4 = InTempC;
        }
    delay(3000);

    update18B20Temp(Thermometer5, InTempC);
      if ( InTempC > -123)
        {
          Temp5 = InTempC;
        }else{
          update18B20Temp(Thermometer5, InTempC);
          Temp5 = InTempC;
        }
    delay(3000);

    sprintf(resultstr, "{\"Temp1\":%f,\"Temp2\":%f,\"Temp3\":%f,\"Temp4\":%f,\"Temp5\":%f}", Temp1, Temp2, Temp3, Temp4, Temp5); //Write sensor data to string

    updateTimer.Update();    // new stuff
}

void update18B20Temp(DeviceAddress deviceAddress, double &tempC)
  {
    tempC = sensors.getTempC(deviceAddress);
  }
