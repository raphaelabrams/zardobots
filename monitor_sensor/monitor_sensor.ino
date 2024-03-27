#define INPIN A0

void setup() {
  delay(1000);
  Serial.begin(115200);
}

void loop() {
  Serial.println(analogRead(INPIN));
  delay(1000);
}
