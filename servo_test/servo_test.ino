//servo_test
//Raphael Abrams, March 2024

void servo(int pin, int angle);

#define SERVOPIN D7 //which physical pin is the servo attached to
#define SERVO_PULSE_MIN 500 //the shortest pulsewidth for servo control
#define SERVO_PULSE_MAX 2600 //the longest pulsewidth for servo control
#define ANGLEMIN -150 //angle measured in degrees
#define ANGLEMAX 150 //''
#define TESTDELAY 10 //higher is slower
#define WAITTIME 2000 //pause at beginning and end for two seconds
#define PULSESPACING 30 //how long the delay begtween servo control pulses

//------------------------------------------------------------------------------------------------
void setup() {
  pinMode(SERVOPIN, OUTPUT);
  delay(1000);
  Serial.begin(115200); // use the serial port
  Serial.println("Hello!");
}

//------------------------------------------------------------------------------------------------
void loop() {
  Serial.print("Starting angle:"); Serial.println(ANGLEMIN);
  for(int w=0; w<40; w++){
      servo(SERVOPIN,ANGLEMIN);
  }
  delay(WAITTIME);
  for(int i=ANGLEMIN;i<=ANGLEMAX;i+=10){
    Serial.print("angle:");Serial.println(i);
    for(int w=0; w<5; w++){
      servo(SERVOPIN,i);
    }
    delay(TESTDELAY);
  } 
  delay(WAITTIME);
}

void servo(int pin, int angle){
  angle = map(angle,ANGLEMIN,ANGLEMAX,SERVO_PULSE_MIN,SERVO_PULSE_MAX);
  digitalWrite(pin, HIGH); 
  delayMicroseconds(angle); //servo pulse high side duration
  digitalWrite(pin, LOW);
  delay(PULSESPACING);
}
