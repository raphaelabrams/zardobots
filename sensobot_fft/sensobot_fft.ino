
#include "KickFFT.h"
void loop(){

  const uint16_t samples = 128;
  uint32_t mag[samples] = {0};
  uint16_t startIndex = 0;
  uint16_t endIndex = 0;
  int16_t input[samples]={0};
  for(uint16_t i = 0; i < samples; i++){
    input[i] = analogRead(A0);
    delay(10);
  }
  KickFFT<int16_t>::fft(Fs, 0, Fs/2, samples, input, mag, startIndex, endIndex);
  for(uint16_t i = 0; i < samples; i++){
    Serial.print(i);
    Serial.print(" ");
    Serial.print(mag[i]);
    Serial.print(" "); 
    Serial.print(input[i]);
    Serial.println();
    delay(1);
  }
}
