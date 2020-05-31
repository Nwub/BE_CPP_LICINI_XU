#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"
#include <fstream>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorScreen : public Device{
protected:
    // memorise l'affichage de l'ecran
  char buf[I2C_BUFFER_SIZE];

public:
  // constructeur
  I2CActuatorScreen ();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//objet type : capteur de base
class Sensor: public Device{
protected:
  //incertitudes
  int alea;
  //période d'échantillonnage
  int s_time;
public:
  //constructeur
  Sensor(int d);
  //thread
  virtual void run();
};

//capteur ambiant de type analogique
class AnalogAmbiantSensor: public Sensor {  
private:
  //valeur mesurée
  int *val;
public:
  //constructeur
  AnalogAmbiantSensor(int t, int *v);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};


//capteur du niveau de batterie du système
class BatteryLevelSensor : public Sensor{
private:
  //valeur mesurée
  int val;
public:
  //constructeur
  BatteryLevelSensor(int t);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

//capteur du niveau d'eau du système
class WaterLevelSensor : public Sensor{
private:
  //valeur mesurée
  int val;
public:
  //constructeur
  WaterLevelSensor(int t);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//objet type : actionneur de base
class Actuator: public Device{
protected:
  //délai
  int delay;
public:
  //constructeur
  Actuator(int d);
  //thread
  virtual void run();
};

//actionneur digital : une led
class DigitalActuatorRGLED: public Actuator {
private:
  //état de la led : rouge ou verte en fonction de la batterie
  boolean state;
public:
  //modification externe
  int *lum;
  //constructeur
  DigitalActuatorRGLED(int d, int *l);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};

//système d'arrosage
class IrrigationSystem: public Actuator {
private:
  //temps d'arrosage
  int w_time;
public:
  //modification externe
  int *hum;
  //constructeur
  IrrigationSystem(int d, int *h);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
enum W_mode {OFF,ON,WINTER,SUMMER,PERIOD};

//module de contrôle du mode d'arrosage
class UserSystemControl : public Device{
private:
  //mode d'arrosage choisi
  W_mode mod;
public:
  //constructeur
  UserSystemControl();
  //thread
  virtual void run();
};

#endif
