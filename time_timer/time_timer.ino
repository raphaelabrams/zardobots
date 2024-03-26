//servo_test
//Raphael Abrams, March 2024

void servo(int pin, int angle);

#define SERVOPIN D7 //which physical pin is the servo attached to
#define SERVO_PULSE_MIN 500 //the shortest pulsewidth for servo control
#define SERVO_PULSE_MAX 2600 //the longest pulsewidth for servo control
#define ANGLEMIN -150 //angle measured in degrees
#define ANGLEMAX 150 //''
#define PULSESPACING 30 //how long the delay begtween servo control pulses

//------------------------------------------------------------------------------------------------
void setup() {
  pinMode(SERVOPIN, OUTPUT);
  delay(1000);
  Serial.begin(115200); // use the serial port
  Serial.println("Hello!");
}

//------------------------------------------------------------------------------------------------

#define HOME 0
#define MAXTIME 180

void loop() {


      Serial.println("small task timer")
      servoMultiple(SERVOPIN,HOME,10);



}

void servoMultiple (int pin, int angle, int reps){
  for (reps;reps>0;reps--){
    servo(pin,angle);
  }
}

#define GAPTIME 30
void servo(int pin, int angle){
  angle = map(angle,ANGLEMIN,ANGLEMAX,SERVO_PULSE_MIN,SERVO_PULSE_MAX);
  digitalWrite(pin, HIGH); 
  delayMicroseconds(angle); //servo pulse high side duration
  digitalWrite(pin, LOW);
  delay(GAPTIME);
}
