

//Lightfollower//
//Raphael Abrams, March 2024

#define SENSOR A0
#define SERVOPIN D7

void centering_loop(int speed, int direction, int anglemin, int anglemax, int framedelay, int deadband);
void servo(int pin, int angle);


#define ADCRESOLUTION 4096
#define ERRORCLIP 40
#define TRIM -200
void centering_loop(int speed, int direction, int anglemin, int anglemax, int framedelay, int deadband){
  static int errorangle = 0;
  signed int error = analogRead(SENSOR);  //the voltage coming from the light probe
  error+=TRIM;
  error= map(error, 0,ADCRESOLUTION, anglemin, anglemax);
  error *= direction; //make direction negative 1 to reverse direction of movement if required
  error/=speed; //reduce the amount of error accumulated per frame to control response speed
  error = constrain(error, -ERRORCLIP, +ERRORCLIP); //limit the error per frame to avoid oscillations
  if(abs(error)<=deadband){ //quiet the motor when at center
    error=0;
  }
  errorangle += error; //add error to accumulator
  errorangle = constrain(errorangle, anglemin, anglemax); //send the pulse to the servo!
  servo(SERVOPIN,errorangle);
  delay(framedelay);
}

#define SERVO_PULSE_MIN 600
#define SERVO_PULSE_MAX 2300
void servo(int pin, int angle){
  angle = map(angle,-90,90,SERVO_PULSE_MIN,SERVO_PULSE_MAX);
  Serial.println(angle);
  digitalWrite(pin, HIGH); 
  delayMicroseconds(angle); //servo pulse high side duration
  digitalWrite(pin, LOW);
}

//------------------------------------------------------------------------------------------------
void setup() {
  pinMode(SERVOPIN, OUTPUT);
  pinMode(SENSOR,INPUT);
  delay(1000);
  Serial.begin(115200); // use the serial port
}

//------------------------------------------------------------------------------------------------
void loop() {

  //args, in order:
  //response speed divider (larger is slower) 2
  //invert (0 or 1)
  //servo minimum angle -90 
  //servo maximum angle 90 
  //frame delay (in mS) 30
  //deadband, in degrees 2
  centering_loop(4, 1, -90, 90, 30, 1); 
}


