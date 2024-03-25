#include "FFT.h" // include the library
//#include "FFT_signal.h"

#define FFT_N 128 // Must be a power of 2
#define TOTAL_TIME .128 //The time in which data was captured. This is equal to FFT_N/sampling_freq
float fft_input[FFT_N];
float fft_output[FFT_N];
float fft_signal[FFT_N];

void setup() {
  delay(1000);
  Serial.begin(115200); // use the serial port
  delay(1000);
}

void loop() {
  char print_buf[300];
  fft_config_t *real_fft_plan = fft_init(FFT_N, FFT_REAL, FFT_FORWARD, fft_input, fft_output);
  while(1){

//    for(uint16_t i = 0; i < FFT_N; i++){
//      fft_signal[i] = analogRead(A0);
//      delayMicroseconds(100);
//    }
  float max_magnitude = 0;
  float fundamental_freq = 0;

    for (int k = 0 ; k < FFT_N ; k++){
      real_fft_plan->input[k] = analogRead(A0);//(float)fft_signal[k];
      delayMicroseconds(50);
    }
    long int t1 = micros();
    // Execute transformation
    fft_execute(real_fft_plan);
    

    int ii=100;
    for (int i=1; i<FFT_N; i++){      
      Serial.print(i);
//      if(i!=1){Serial.print(ii);}
          Serial.print(" ");
      Serial.print(real_fft_plan->input[i]);
          Serial.print(" ");
      float mag = sqrt(pow(real_fft_plan->output[2*i],2) + pow(real_fft_plan->output[2*i+1],2))/1;
      Serial.print(mag);
//      Serial.print(real_fft_plan->output[i]);
          Serial.println("");
          delay(10);

    }
/*    // Print the output
    for (int k = 1 ; k < real_fft_plan->size / 2 ; k++){
      //The real part of a magnitude at a frequency is followed by the corresponding imaginary part in the output
      float mag = sqrt(pow(real_fft_plan->output[2*k],2) + pow(real_fft_plan->output[2*k+1],2))/1;
      float freq = k*1.0/TOTAL_TIME;
      if(mag > max_magnitude){
          max_magnitude = mag;
          fundamental_freq = freq;
      }
    }
    long int t2 = micros();
    
    Serial.println();
    //Multiply the magnitude of the DC component with (1/FFT_N) to obtain the DC component
    sprintf(print_buf,"DC component : %f g\n", (real_fft_plan->output[0])/10000/FFT_N);  // DC is at [0]
    Serial.println(print_buf);

    //Multiply the magnitude at all other frequencies with (2/FFT_N) to obtain the amplitude at that frequency
    sprintf(print_buf,"Fundamental Freq : %f Hz\t Mag: %f g\n", fundamental_freq, (max_magnitude/10000)*2/FFT_N);
    Serial.println(print_buf);

    Serial.print("Time taken: ");Serial.print((t2-t1)*1.0/1000);Serial.println(" milliseconds!");
*/    
//    // Clean up at the end to free the memory allocated
//    fft_destroy(real_fft_plan);
  }  
}
