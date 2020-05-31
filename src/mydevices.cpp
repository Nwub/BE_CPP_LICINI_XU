
#include "mydevices.h"

using namespace std;

int BatteryLevel = 99;
int WaterLevel = 99;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//constructeur des classes Sensor
Sensor::Sensor(int d):Device(){
  s_time = d;
  alea = 1;
}
void Sensor::run(){
  while(1){
    cout << "empty sensor" << endl;
    sleep(DELAY);
  }
}
//constructeur des classes Actuator
Actuator::Actuator(int d):Device(){
  delay = d;
}
void Actuator::run(){
  while(1){
    cout << "empty actuator" << endl;
    sleep(DELAY);
  }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//capteur d'une grandeur ambiante
AnalogAmbiantSensor::AnalogAmbiantSensor(int d, int *v):Sensor(d){
  val=v;
}
void AnalogAmbiantSensor::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=*val+alea;
    sleep(s_time);
  }
}

//capteur du niveau de batterie du système
BatteryLevelSensor::BatteryLevelSensor(int d):Sensor(d){
  val=BatteryLevel;
}
void BatteryLevelSensor::run(){
  while(1){
    val=BatteryLevel;
    alea=1-alea;
    if(ptrmem!=NULL)    
      *ptrmem=val+alea;
    sleep(s_time);
  }
}

//capteur du niveau d'eau du système
WaterLevelSensor::WaterLevelSensor(int d):Sensor(d){
  val=WaterLevel;
}
void WaterLevelSensor::run(){
  while(1){
    val=WaterLevel;
    alea=1-alea;
    if(ptrmem!=NULL)    
      *ptrmem=val+alea;
    sleep(s_time);
  }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//classe LED
DigitalActuatorRGLED::DigitalActuatorRGLED(int d, int *l):Actuator(d){
  state = LOW;
  //la led joue sur la luminosité environnante
  lum = l;
}
void DigitalActuatorRGLED::run(){
  int old_state = state;
  while(1){
    if(ptrmem!=NULL){
      state=*ptrmem;
      if (state==LOW){
        cout << "# LED : [RED] #\n";
        if(old_state==HIGH){  //modif env
          if(*lum>20) *lum -= 20; //pas de luminosité négative
          old_state = LOW;
        }
      }else{
        cout << "# LED : [GREEN] #\n";
        if(old_state==LOW){   //modif env
          *lum += 30;
          old_state = HIGH;
        }
      }
    }
    sleep(delay);
  }
}

//système d'arrosage
IrrigationSystem::IrrigationSystem(int d, int *h):Actuator(d){
  w_time = 0;
  //l'arrosage joue sur l'humidité
  hum = h;
}
void IrrigationSystem::run(){
  while(1){
    sleep(delay);
    if(ptrmem!=NULL){
      w_time=*ptrmem;
      if(w_time>0){
        if(BatteryLevel<11){  //pas d'anti-énergie
          cout << "!!! LOW on Battery !!!" << endl;
        }else{
          if(WaterLevel>w_time){  //pas d'anti-eau
            BatteryLevel -= 10;   //consommation : 10Power/use
            WaterLevel -= w_time; //consommation : 1Water/time
            *hum += w_time/2;
            cout << "# Watering : ON #" << endl;
          }else{
            cout << "!!! LOW on Water !!!" << endl;
          }
        }
      }
    }
  }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Sélecteur du mode d'arrosage
UserSystemControl::UserSystemControl():Device(){
  mod = OFF;
}
void UserSystemControl::run(){
  while(1){
    if(ptrmem!=NULL){
      //check si recharge de batterie ou d'eau
      if(ifstream("power.txt")){
        BatteryLevel = 99;
        cout << "-> Power Charged !" << endl;
      }
      if(ifstream("water.txt")){
        BatteryLevel = 99;
        cout << "-> Water Refilled !" << endl;
      }
      //on récupère le mode (pas plusieurs modes simultanés)
      if(ifstream("on.txt")){
        mod = ON;
        cout << "________setMode ON\n";
      }else if(ifstream("winter.txt")){
        mod = WINTER;
        cout << "________setMode WINTER\n";
      }else if(ifstream("summer.txt")){
        mod = SUMMER;
        cout << "________setMode SUMMER\n";
      }else if(ifstream("period.txt")){
        mod = PERIOD;
        cout << "________setMode PERIOD\n";
      }else{  //mode par défaut
        cout << "________setMode OFF" << endl;
        mod = OFF;
      }
      *ptrmem=(int)mod;
      sleep(DELAY);
    }
  }
}