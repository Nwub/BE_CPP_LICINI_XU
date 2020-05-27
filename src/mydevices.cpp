
#include "mydevices.h"

using namespace std;

int luminosite_environnement = 200; //LUX
int temperature_environnement = 25; //°C
float pression_environnement = 1.013; //bar
int humidite_environemment = 40; //%

//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d):Device(),temps(d){
  val=temperature_environnement;
  alea=1;
}

void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW)
      cout << "((((eteint))))\n";
    else
    cout << "((((allume))))\n";
    sleep(temps);
    }
}

// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){
  }

void I2CActuatorScreen::run(){
  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :"<< buf << endl;
    }
    sleep(1);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AnalogSensorLuminosity::AnalogSensorLuminosity(int d):Device(),temps(d){
  val = luminosite_environnement;
  alea = 1;
}

void AnalogSensorLuminosity::run(){
  while(1){
    val = luminosite_environnement;
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}


IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int d):Device(),temps(d){
  state = HIGH;
}

void IntelligentDigitalActuatorLED::run(){
  int old_state = state;
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if(state==HIGH && old_state==LOW){
      luminosite_environnement = luminosite_environnement + 50;
      old_state=state;
    }else if(state== LOW && old_state==HIGH){
      luminosite_environnement = luminosite_environnement - 50;
      old_state=state;
    }
    sleep(temps);
  }
}


ExternalDigitalSensorButton::ExternalDigitalSensorButton():Device(){
  state = LOW;
}

void ExternalDigitalSensorButton::run(){
  while(1){
    if(ifstream("on.txt")){
      state = HIGH;
    }else{
      state = LOW;
    }
    if(ptrmem!=NULL)
    *ptrmem=state;
    sleep(5);
  }
}