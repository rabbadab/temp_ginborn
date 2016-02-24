// This #include statement was automatically added by the Particle IDE.
#include "OneWire.h"
#include "spark-dallas-temperature.h"
#include "SparkCorePolledTimer.h"

#include "blynk.h"
#include "BlynkSimpleParticle.h"

#define BLYNK_DEBUG // Uncomment this to see debug prints
#define BLYNK_PRINT Serial

#define ONE_WIRE_BUS D4 // Data wire is plugged into pin D0 on the particle
#define TEMPERATURE_PRECISION 12         // DS18B20 Thermometer Stuff
OneWire oneWire(ONE_WIRE_BUS);          // DS18B20 Thermometer Stuff
DallasTemperature sensors(&oneWire);    // DS18B20 Thermometer Stuff

//Blynk auth
// Live
//char auth[] = "b5bcca6aed404a20be878d56789f23dc";
// Test
char auth[] = "d66adc2e61ad4ced926d032b486f28de";

SparkCorePolledTimer updateTimer(5000); //Create a timer object and set it's timeout in milliseconds
void OnTimer(void); //Prototype for timer callback method

DeviceAddress Thermometer1 = { 0x28, 0xD2, 0x18, 0xF1, 0x4, 0x0, 0x0, 0x96 };
DeviceAddress Thermometer2 = { 0x28, 0x1E, 0x20, 0xF2, 0x4, 0x0, 0x0, 0x46 };
DeviceAddress Thermometer3 = { 0x28, 0xE5, 0xDB, 0xF1, 0x4, 0x0, 0x0, 0x92 };
DeviceAddress Thermometer4 = { 0x28, 0xFF, 0x9E, 0x93, 0x61, 0x15, 0x2, 0x95 };
DeviceAddress Thermometer5 = { 0x28, 0xFF, 0xB, 0x81, 0x61, 0x15, 0x2, 0xCF };
DeviceAddress Thermometer6 = { 0X28, 0xFF, 0x2A, 0x5F, 0x72, 0x15, 0x1, 0xA2 };
DeviceAddress Thermometer7 = { 0x28, 0xFF, 0xC5, 0x97, 0x72, 0x15, 0x1, 0x32 };
DeviceAddress Thermometer8 = { 0X28, 0xFF, 0x8D, 0xE0, 0x72, 0x15, 0x1, 0xCB };

double InTempC = -1;
double Temp1 = -1;
double Temp2 = -1;
double Temp3 = -1;
double Temp4 = -1;
double Temp5 = -1;
double Temp6 = -1;
double Temp7 = -1;
double Temp8 = -1;

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
    sensors.setResolution(Thermometer6, TEMPERATURE_PRECISION);
    sensors.setResolution(Thermometer7, TEMPERATURE_PRECISION);
    sensors.setResolution(Thermometer8, TEMPERATURE_PRECISION);

    delay(5000); // Allow board to settle

//Blynk auth
    Blynk.begin(auth);

    Particle.variable("result", resultstr, STRING);  //Spark variable "result" to store sensor data string

}

void loop()
  {
    Blynk.run();
    updateTimer.Update();
  }

void OnTimer(void)
    { //Handler for the timer, will be called automatically
        // DS18B20
    sensors.requestTemperatures();

    update18B20Temp(Thermometer1, InTempC);
      Temp1 = InTempC;
    //  Blynk.virtualWrite(1, Temp1);
    //  delay(1000);

    update18B20Temp(Thermometer2, InTempC);
      Temp2 = InTempC;
  //    Blynk.virtualWrite(2, Temp2);
  //    delay(1000);

    update18B20Temp(Thermometer3, InTempC);
      Temp3 = InTempC;
  //    Blynk.virtualWrite(3, Temp3);
    //  delay(1000);

    update18B20Temp(Thermometer4, InTempC);
      Temp4 = InTempC;
  //    Blynk.virtualWrite(4, Temp4);
  //    delay(1000);

    update18B20Temp(Thermometer5, InTempC);
      Temp5 = InTempC;
    update18B20Temp(Thermometer6, InTempC);
      Temp6 = InTempC;
    update18B20Temp(Thermometer7, InTempC);
      Temp7 = InTempC;
    update18B20Temp(Thermometer8, InTempC);
      Temp8 = InTempC;
  //    Blynk.virtualWrite(5, Temp5);
    //  delay(1000);

    sprintf(resultstr, "{\"Temp1\":%f,\"Temp2\":%f,\"Temp3\":%f,\"Temp4\":%f,\"Temp5\":%f,\"Temp6\":%f,\"Temp7\":%f,\"Temp8\":%f}", Temp1, Temp2, Temp3, Temp4, Temp5, Temp6, Temp7, Temp8); //Write sensor data to string

    updateTimer.Update();    // new stuff
}

void update18B20Temp(DeviceAddress deviceAddress, double &tempC)
  {
    tempC = sensors.getTempC(deviceAddress);

    if ( Temp1 < 90 && Temp1 > -120) {
        Blynk.virtualWrite(1, Temp1);
  //      Serial.println(Temp1);
    }
    if ( Temp2 < 90 && Temp2 > -120) {
        Blynk.virtualWrite(2, Temp2);
    }
    if ( Temp3 < 90 && Temp3 > -120) {
        Blynk.virtualWrite(3, Temp3);
    }
    if ( Temp4 < 90 && Temp4 > -120) {
        Blynk.virtualWrite(4, Temp4);
    }
    if ( Temp5 < 90 && Temp5 > -120) {
        Blynk.virtualWrite(5, Temp5);
    }
    if ( Temp6 < 90 && Temp6 > -120) {
        Blynk.virtualWrite(6, Temp6);
    }
    if ( Temp7 < 90 && Temp7 > -120) {
        Blynk.virtualWrite(7, Temp7);
    }
    if ( Temp8 < 90 && Temp8 > -120) {
        Blynk.virtualWrite(8, Temp8);
    }
  }
