#include "core_simulation.h"
#include "mydevices.h"

//variables globales de l'environnement//
int luminosite_environnement = 1500;  //LUX
int temperature_environnement = 25;  //°C
int humidite_environnemment = 30;   //%
/////////////////////////////////////

int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogAmbiantSensor temperature(DELAY, &temperature_environnement);
  AnalogAmbiantSensor luminosity(DELAY, &luminosite_environnement);
  AnalogAmbiantSensor humidity(DELAY, &humidite_environnemment);
  DigitalActuatorRGLED led_batt(DELAY, &luminosite_environnement);
  DigitalActuatorRGLED led_wat(DELAY, &luminosite_environnement);
  BatteryLevelSensor battery(DELAY);
  WaterLevelSensor water(DELAY);
  UserSystemControl USC;
  IrrigationSystem irrigation(DELAY, &humidite_environnemment);
  //I2CActuatorScreen screen;
  
  // branchement des capteurs actionneurs
  esp8266.pin(0,USC);
  esp8266.pin(1,temperature);
  esp8266.pin(2,luminosity);
  esp8266.pin(3,humidity);
  esp8266.pin(4,led_batt);
  esp8266.pin(5,led_wat);
  esp8266.pin(6,battery);
  esp8266.pin(7,water);
  esp8266.pin(8,irrigation);
  //esp8266.i2c(1,screen);
  
  // allumage de la carte
  esp8266.run();
  return 0;
}


