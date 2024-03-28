//Hello World!
//Raphael Abrams, March 2024
#define INPIN D1
#define LEDPIN D10

void setup() {
  pinMode(INPIN, INPUT_PULLUP);
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
    digitalWrite(LEDPIN,1);
    delay(1000);
    digitalWrite(LEDPIN,0);
    delay(1000);
}