
#include "mydevices.h"

using namespace std;

int luminosite_environnement = 200; //LUX
int temperature_environnement = 25; //°C
float pression_environnement = 1.013; //bar
int humidite_environemment = 40; //%

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

//constructeur des classes Sensor
Sensor::Sensor(int d):Device(){
  temps = d;
  alea = 1;
}
void Sensor::run(){
  while(1){
    cout << "empty sensor" << endl;
    sleep(DELAY);
  }
}

//constructeur des classes Actuator
Actuator::Actuator():Device(){
  state = LOW;
}
void Actuator::run(){
  while(1){
    cout << "empty actuator" << endl;
    sleep(DELAY);
  }
}

//capteur de température ambiant
AnalogSensorTemperature::AnalogSensorTemperature(int d):Sensor(d){
  val=temperature_environnement;
}
void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//classe LED
DigitalActuatorLED::DigitalActuatorLED():Actuator(){
}
void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW)
      cout << "((((eteint))))\n";
    else
    cout << "((((allume))))\n";
    sleep(DELAY);
    }
}

//capteur de luminosité ambiante
AnalogSensorLuminosity::AnalogSensorLuminosity(int d):Sensor(d){
  val = luminosite_environnement;
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

//LED
IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED():Actuator(){
}
void IntelligentDigitalActuatorLED::run(){
  int old_state = state;
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if(state==HIGH && old_state==LOW){
      luminosite_environnement = luminosite_environnement + 50;
      old_state=state;
      cout << "[ON]" << endl << flush;
    }else if(state== LOW && old_state==HIGH){
      luminosite_environnement = luminosite_environnement - 50;
      old_state=state;
      cout << "[OFF]" << endl << flush;
    }else{
      old_state=state;
    }
    sleep(DELAY);
  }
}

//bouton externe
ExternalDigitalSensorButton::ExternalDigitalSensorButton(int t):Sensor(t){
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
