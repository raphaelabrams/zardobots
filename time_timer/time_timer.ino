//time timer
//Raphael Abrams, March 2024

//#define ECHO

#define INPIN D0
#define SERVOPIN D7 //which physical pin is the servo attached to
#define LEDPIN D8 //which physical pin is the servo attached to
#define SERVO_PULSE_MIN 500 //the shortest pulsewidth for servo control
#define SERVO_PULSE_MAX 2600 //the longest pulsewidth for servo control
#define ANGLEMIN -150 //angle measured in degrees
#define ANGLEMAX 150 //''
#define PULSESPACING 30 //how long the delay begtween servo control pulses
#define PUSHED 0
#define TIMERMIN 0
#define TIMERMAX 180
#define BUILDPAUSE 2
#define COUNTDOWNINCREMENT 1000
#define INDICATEMIN 0 //angles to display the timer
#define INDICATEMAX 120 //''
#define JIGGLE 4
#define TRUE 1

void servo(int pin, int angle);
void servoMultiple (int pin, int angle, int reps);


//------------------------------------------------------------------------------------------------
void setup() {
  pinMode(SERVOPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(INPIN, INPUT_PULLUP);
  delay(1000);
  #ifdef ECHO
  Serial.begin(115200); // use the serial port
  Serial.println("small task timer");
  #endif
  servoMultiple(SERVOPIN,INDICATEMIN,10);
}

//------------------------------------------------------------------------------------------------
void loop() {
  static int countdown=0;
  static int armed=0;
  digitalWrite(LEDPIN,0);
  if(digitalRead(INPIN)==PUSHED){
  #ifdef ECHO
  Serial.println("RESET TIMER");
  #endif
    countdown=0; //reset the countdown timer
    servoMultiple(SERVOPIN,INDICATEMIN,3);
    while(digitalRead(INPIN)==PUSHED){
      armed=TRUE;
      countdown++;
      countdown = constrain(countdown,TIMERMIN,TIMERMAX);
      #ifdef ECHO
      Serial.print("timer is now set to");
      Serial.print(countdown);
      Serial.println("seconds");
      #endif
      int display= map(countdown, TIMERMIN, TIMERMAX, INDICATEMIN, INDICATEMAX);
      servo(SERVOPIN,display);
      digitalWrite(LEDPIN,1);
      delay(BUILDPAUSE);
      digitalWrite(LEDPIN,0);
    }
  }
  if(armed==TRUE && countdown>0){
    int display=0;
    display= map(countdown, TIMERMIN, TIMERMAX, INDICATEMIN, INDICATEMAX);
    servo(SERVOPIN,display+JIGGLE);
    servo(SERVOPIN,display);
    countdown--;
    delay(COUNTDOWNINCREMENT);
    #ifdef ECHO
    Serial.print("t minus ");
    Serial.println(countdown);
    Serial.println("...  ");
    #endif
  }
  if(armed==1 && countdown==0){
    armed=0;
    digitalWrite(LEDPIN,1);
    for (int x=20;x>0;x--){
      #ifdef ECHO
      Serial.println("BOOM!");
      #endif
      servo(SERVOPIN,INDICATEMIN);
      servo(SERVOPIN,INDICATEMIN+30);      
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
