#include <unistd.h>
#include "core_simulation.h"

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(0,INPT);
  pinMode(1,INPT);
  pinMode(2,INPT);
  pinMode(3,INPT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,INPT);
  pinMode(7,INPT);
  pinMode(8,OUTPUT);
}

// la boucle de controle arduino
void Board::loop(){
  char buf[100];
  int val_t=0;
  int val_l=0;
  int val_h=0;
  int val_b=0;
  int val_w=0;
  static int cpt=0;
  //static int bascule=0;
  int mode=0;

  // lecture sur la pin 1 : capteur de temperature
  val_t=analogRead(1);
  sprintf(buf,"temperature : %d",val_t);
  Serial.println(buf);
  // lecture sur la pin 2 : capteur de luminosité
  val_l=analogRead(2);
  sprintf(buf,"luminosite : %d",val_l);
  Serial.println(buf);
  // lecture sur la pin 3 : capteur de pression
  val_h=analogRead(3);
  sprintf(buf,"humidite : %d",val_h);
  Serial.println(buf);

  // lecture sur la pin 6 : niveau de batterie
  val_b=analogRead(6);
  sprintf(buf,"**Battery Level %d",val_b);
  Serial.println(buf);
  // lecture sur la pin 7 : niveau d'eau
  val_w=analogRead(7);
  sprintf(buf,"**Water Level %d",val_w);
  Serial.println(buf);

  sleep(1);

  // Led du niveau de batterie rouge si batterie faible 
  if(val_b<20){
    digitalWrite(4,HIGH);
  }else{
    digitalWrite(4,LOW);
  }
  // Led du niveau d'eau rouge si niveau faible
  if(val_w<20){ 
    digitalWrite(5,HIGH);
  }else{
    digitalWrite(5,LOW);
  }

  sleep(1);

  // lecture sur la pin 0 : mode d'arrosage
  mode=analogRead(0);
  sprintf(buf,".....Mode %d.....",mode);
  Serial.println(buf);

  // système d'arrosage automatique (algorithme trop simpliste)
  int sum = val_t + val_l + val_h;
  if(mode==1){
    analogWrite(8,3);
  }else if(mode==2){
    if(1000+10+0<sum && sum<5000+30+80) analogWrite(8,20);
  }else if(mode==3){
    if(800+4+10<sum && sum<2000+30+60) analogWrite(8,7);
  }else if(mode==4){
    if(cpt%10800==0) analogWrite(8,15);
  }else{
    analogWrite(8,0);
  }

  cpt++;
  sleep(2);
  cout << endl << "============================================= ITERATION : " << cpt << endl << flush;
}