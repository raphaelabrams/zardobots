#define INPIN D0
//#define INPIN A0

void setup() {
  //pinMode(INPIN, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  Serial.println(analogRead(INPIN));
  //Serial.println(digitalRead(INPIN));
  delay(1000);
}
