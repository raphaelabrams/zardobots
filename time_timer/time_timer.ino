//time timer
//Raphael Abrams, March 2024

//#define ECHO  //if you want serial feedback, uncomment and use a serial monitor

#define INPIN D0 //physical pin for button
#define SERVOPIN D7 //which physical pin is the servo attached to
#define LEDPIN D8 //which physical pin is the servo attached to
#define SERVO_PULSE_MIN 500 //the shortest pulsewidth for servo control
#define SERVO_PULSE_MAX 2600 //the longest pulsewidth for servo control
#define ANGLEMIN -150 //angle measured in degrees
#define ANGLEMAX 150 //''
#define PULSESPACING 30 //how long the delay begtween servo control pulses
#define PUSHED 0 //status of the button, a low voltage indicates button press
#define TIMERMIN 0 //the lowest number of seconds to count down.
#define TIMERMAX 180 //what's the longest the time possible for the timing cycle
#define BUILDPAUSE 2 //higher number slows down the increase in timing cycle when pressing button
#define TICK 1000 //length of a "second"
#define INDICATEMIN 0 //angles to display the timer
#define INDICATEMAX 120 
#define ALERTLOW 10 //low end of wiggling alert at the end of the timing cycle
#define ALERTHIGH 40 //high end of wiggling alert at the end of the timing cycle
#define JIGGLE 4 //overshoot of servo by a few degrees to make time ticking more visible
#define TRUE 1 //for logic tests

void servo(int pin, int angle);
void servoMultiple (int pin, int angle, int reps);

//------------------------------------------------------------------------------------------------
void setup() {
  pinMode(SERVOPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(INPIN, INPUT_PULLUP); //enable input weak pullup if there's no pullup resistor on the switch
  delay(1000); //wait a second for voltages and ports to settle
  #ifdef ECHO
  Serial.begin(115200);
  Serial.println("small task timer");
  #endif
  servoMultiple(SERVOPIN,INDICATEMIN,6); //drive the servo to start position
}

//------------------------------------------------------------------------------------------------
void loop() {
  static int countdown=0; //accumulator for countdown
  static int armed=0; //flag for alarm
  digitalWrite(LEDPIN,0); //turn off LED
  if(digitalRead(INPIN)==PUSHED){ //get status of input switch
    #ifdef ECHO
    Serial.println("RESET TIMER");
    #endif
    countdown=0; //reset the countdown timer
    servoMultiple(SERVOPIN,INDICATEMIN,3); //move servo to start position
    while(digitalRead(INPIN)==PUSHED){
      armed=TRUE;
      countdown++; //add seconds to countdown
      countdown = constrain(countdown,TIMERMIN,TIMERMAX); //no too many!
      #ifdef ECHO
      Serial.print("timer is now set to"); Serial.print(countdown); Serial.println("seconds");
      #endif
      //servo is in degrees, timer is in seconds, convert seconds to degrees for the servo
      int display= map(countdown, TIMERMIN, TIMERMAX, INDICATEMIN, INDICATEMAX);
      servo(SERVOPIN,display); //point to the angle that represents the selected time
      digitalWrite(LEDPIN,1); //flash the led
      delay(BUILDPAUSE); //longer delay makes the timer slower to increment
      digitalWrite(LEDPIN,0);
    }
  }
  //at this point the button has been released
  if(armed==TRUE && countdown>0){ 
    int display= map(countdown, TIMERMIN, TIMERMAX, INDICATEMIN, INDICATEMAX);
    servo(SERVOPIN,display+JIGGLE);
    servo(SERVOPIN,display);
    countdown--;
    delay(TICK);
    #ifdef ECHO
    ECHO Serial.print("t minus "); Serial.println(countdown); Serial.println("...  "); 
    #endif
  }
  if(armed==1 && countdown==0){
    armed=0;
    digitalWrite(LEDPIN,1);
    for (int x=20;x>0;x--){
      #ifdef ECHO
      Serial.println("BOOM!");
      #endif
      servo(SERVOPIN,ALERTHIGH);
      servo(SERVOPIN,ALERTLOW);      
    }
    servoMultiple(SERVOPIN,INDICATEMIN,5);
  }
}

void servoMultiple (int pin, int angle, int reps){
  for (reps;reps>0;reps--){
    servo(pin,angle);
  }
}

#define GAPTIME 30  //milliseconds between pulses
void servo(int pin, int angle){
  angle = map(angle,ANGLEMIN,ANGLEMAX,SERVO_PULSE_MIN,SERVO_PULSE_MAX);
  digitalWrite(pin, HIGH); 
  delayMicroseconds(angle); //servo pulse high side duration
  digitalWrite(pin, LOW);
  delay(GAPTIME);
}
