#define INPIN D1
#define LEDPIN D10
void setup() {
  pinMode(INPIN, INPUT_PULLUP);
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  if(digitalRead(INPIN)==1){
    speed=200
  }else{
    speed=500;
  }
  digitalWrite(LEDPIN,1);
  delay(speed);
  digitalWrite(LEDPIN,0);
  delay(speed);
}
