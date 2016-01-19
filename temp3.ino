// This #include statement was automatically added by the Particle IDE.
#include "OneWire/OneWire.h"
#include "spark-dallas-temperature/spark-dallas-temperature.h"
#include "SparkCorePolledTimer/SparkCorePolledTimer.h"
#include "blynk/blynk.h"
#include "blynk/BlynkSimpleParticle.h"

//#define BLYNK_DEBUG // Uncomment this to see debug prints
//#define BLYNK_PRINT Serial

#define ONE_WIRE_BUS D4 // Data wire is plugged into pin D0 on the particle
#define TEMPERATURE_PRECISION 12         // DS18B20 Thermometer Stuff
OneWire oneWire(ONE_WIRE_BUS);          // DS18B20 Thermometer Stuff
DallasTemperature sensors(&oneWire);    // DS18B20 Thermometer Stuff

SparkCorePolledTimer updateTimer(25000); //Create a timer object and set it's timeout in milliseconds
void OnTimer(void); //Prototype for timer callback method

//float main, mainRaw, aux, auxRaw, acc, accRaw, light, lightRaw;

char auth[] = "b5bcca6aed404a20be878d56789f23dc";

//temp stuff
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
//end temp stuff

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
//    sensors.setResolution(Thermometer4, TEMPERATURE_PRECISION);


delay(5000); // Allow board to settle

//pinMode(A0, INPUT);
//pinMode(A1, INPUT);
//pinMode(A2, INPUT);
//pinMode(A5, INPUT);
Blynk.begin(auth);
Particle.variable("result", resultstr, STRING);  //Spark variable "result" to store sensor data string
//Particle.publish("result", resultstr);
}

void loop()
{


Blynk.run();
updateTimer.Update();
}

void OnTimer(void) { //Handler for the timer, will be called automatically



        // DS18B20
    sensors.requestTemperatures();
    update18B20Temp(Thermometer1, InTempC);
    Temp1 = InTempC;
    Serial.println(Temp1);
  //  Particle.publish("temperature1", Temp1);
    delay(5000);
    update18B20Temp(Thermometer2, InTempC);  
    Temp2 = InTempC;  
//    Serial.println(Temp2);
    delay(5000);
    update18B20Temp(Thermometer3, InTempC);  
    Temp3 = InTempC;
//    Serial.println(Temp3);
    delay(5000);
    update18B20Temp(Thermometer4, InTempC);  
    Temp4 = InTempC;
//    Serial.println(Temp4);
    delay(5000);
    update18B20Temp(Thermometer5, InTempC);  
    Temp5 = InTempC;
//    Serial.println(Temp5);
    delay(5000);
    sprintf(resultstr, "{\"Temp1\":%f,\"Temp2\":%f,\"Temp3\":%f,\"Temp4\":%f,\"Temp5\":%f}", Temp1, Temp2, Temp3, Temp4, Temp5); //Write sensor data to string

//left out due to updatetimer in      delay(5000); // READ DELAY - TOOK THIS OUT AND IT GOT JUMPY WITH -127'S C AND 196'S F


updateTimer.Update();    // new stuff
}

void update18B20Temp(DeviceAddress deviceAddress, double &tempC)
{
  tempC = sensors.getTempC(deviceAddress);
//}

if ( tempC < 90 && tempC > -120) {
    Blynk.virtualWrite(0, tempC);
}
if ( Temp1 < 90 && Temp1 > -120) {
    Blynk.virtualWrite(1, Temp1); 
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

// read analog ports
/*mainRaw = analogRead(A0);
auxRaw = analogRead(A1);
accRaw = analogRead(A2);
//lightRaw = analogRead(A5);

main = map(mainRaw, 0, 4096, 0, 1865);
aux = map(auxRaw, 0, 4096, 0, 1865);
acc = map(accRaw, 0, 4096, 1000, 1865);
//light = map(lightRaw, 0, 4096, 1000, 1500);

main = (main / 100);
aux = (aux / 100);
acc = (acc / 100);
//light = (light / 100);

Blynk.virtualWrite(10, main);
Blynk.virtualWrite(11, aux);
Blynk.virtualWrite(12, acc);
//Blynk.virtualWrite(25, light);

}