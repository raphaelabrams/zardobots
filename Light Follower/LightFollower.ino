

//Centering loop///////////////
//Raphael Abrams, March 2024
//public domain, attribution appreciated but not required
#include "bandpassFilter.c"
#include "KickFFT.h"
#define SENSOR A0
#define SERVOPIN 9
#define ADCRESOLUTION 4096
#define CENTER  ADCRESOLUTION/2
void centering_loop(int speed, int direction, int servomin, int servomax, int framedelay, int deadband){
  static int servoangle= 1200;
  signed int error = analogRead(SENSOR);  //the voltage coming from the light probe
  error -= CENTER;
  error *= direction; //make direction negative 1 to reverse direction of movement if required
  error/=speed; //reduce the amount of error accumulated per frame to control response speed
  error = constrain(error, -550, +550); //limit the error per frame to avoid oscillations
  if(abs(error)<=deadband){ //quiet the motor when at center
    error=0;
  }
  servoangle += error; //add error to accumulator
  servoangle = constrain(servoangle, servomin, servomax); //send the pulse to the servo!
  digitalWrite(SERVOPIN, HIGH); 
  delayMicroseconds(servoangle); //servo pulse high sidfe duration
  digitalWrite(SERVOPIN, LOW);
  delay(framedelay);
}

bandpassFilter bandyboy;

//------------------------------------------------------------------------------------------------
void setup() {
  pinMode(SERVOPIN, OUTPUT);
  pinMode(0,INPUT);
  Serial.begin(115200);
  bandpassFilter_init(&bandyboy);
  
}

//------------------------------------------------------------------------------------------------
void loop() {
  //response speed divider (larger is slower) 2
  //invert (0 or 1)
  //servo minimum pulse (uS) 600
  //servo maximum pulse (uS) 2300
  //frame delay (in mS) 30
  //deadband 20
  centering_loop(12, 1, 600, 2300, 30, 20); 
/*
  int inputsignal = analogRead(SENSOR);
  inputsignal-=CENTER;
  bandpassFilter_put(&bandyboy, inputsignal);
  int outputsignal=0; 
  outputsignal = bandpassFilter_get(&bandyboy);

  static int envelope=0;
  if (abs(outputsignal)>envelope){
    envelope=abs(outputsignal);
  }
  else{
    envelope-=10;
  }
  if (envelope<0){
    envelope=0;
  }
  Serial.print(inputsignal);
  Serial.print(",");
  Serial.print(outputsignal);
  Serial.print(",");
  Serial.print(envelope);
  Serial.print(",");
  Serial.print(-2048);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.println(4095);

  delay(10);
*/
}


