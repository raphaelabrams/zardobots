//Hello World!
//Raphael Abrams, March 2024

#define LEDPIN D8 //which physical pin is the servo attached to

void setup() {
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
    digitalWrite(LEDPIN,1);
    delay(1000);
    digitalWrite(LEDPIN,0);
    delay(1000);
}