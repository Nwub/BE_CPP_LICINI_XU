#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"
#include <fstream>

//~~~~~~~~~~~~~~~~~~~~~~~~~
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
//~~~~~~~~~~~~~~~~~~~~~~~~~

//objet type : capteur de base
class Sensor: public Device{
  protected:
  //incertitudes
  int alea;
  //période d'échantillonnage
  int temps;

  public:
  //constructeur
  Sensor(int d);
  //thread
  virtual void run();
};

//objet type : actionneur de base
class Actuator: public Device{
  protected:
  //état
  int state;

  public:
  //constructeur
  Actuator();
  //thread
  virtual void run();
};

//capteur analogique de temperature
class AnalogSensorTemperature: public Sensor {  
private:
  //valeur mesurée
  int val;
public:
  //constructeur
  AnalogSensorTemperature(int t);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

//actionneur digital : une led
class DigitalActuatorLED: public Actuator {
private:
  //état LED
  boolean state;
public:
  //constructeur
  DigitalActuatorLED();
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};

//capteur de luminosité
class AnalogSensorLuminosity : public Sensor{
  private:
  //valeur mesurée
  int val;

  public:
  //constructeur
  AnalogSensorLuminosity(int t);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

//smart-LED
class IntelligentDigitalActuatorLED : public Actuator{
  private:
  //état LED
  boolean state;
  public:
  //constructeur
  IntelligentDigitalActuatorLED();
  //thread
  virtual void run();
};

//bouton externe
class ExternalDigitalSensorButton : public Sensor{
  private:
  //état bouton
  boolean state;
  public:
  //constructeur
  ExternalDigitalSensorButton(int t);
  //thread
  virtual void run();
};


#endif
