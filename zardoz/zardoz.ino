
#define SERVOPIN D7
#define ANALOGIN A0
#define LEDPIN D8

#define HUMHIGH 480
#define HUMLOW 420
#define ZARDOZ_IS_PLEASED 90
#define ZARDOZ_IS_DISPLEASED 0

#include "FFT.h" // include the library (its here in the folder, not a built in library)
#define FFT_N 2048 // Must be a power of 2
#define TOTAL_TIME .1250 //The time in which data was captured. This is equal to FFT_N/sampling_freq
float fft_input[FFT_N];
float fft_output[FFT_N];

void servo(int pin, int angle);

void setup() {
  delay(1000);
  Serial.begin(115200); // use the serial port
  delay(1000);
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  char print_buf[300];
  fft_config_t *real_fft_plan = fft_init(FFT_N, FFT_REAL, FFT_FORWARD, fft_input, fft_output);
  while(1){

  float max_magnitude = 0;
  float fundamental_freq = 0;

    for (int k = 0 ; k < FFT_N ; k++){
      real_fft_plan->input[k] = analogRead(ANALOGIN);//(float)fft_signal[k];
      delayMicroseconds(5);
    }
    long int t1 = micros();
    // Execute transformation
    fft_execute(real_fft_plan);
    

    // Print the output
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
    sprintf(print_buf,"DC: %f g ---", (real_fft_plan->output[0])/10000/FFT_N);  // DC is at [0]
    Serial.print(print_buf);

    //Multiply the magnitude at all other frequencies with (2/FFT_N) to obtain the amplitude at that frequency
    sprintf(print_buf,"Fund: %f Hz\t Mag: %f g. >>>", fundamental_freq, (max_magnitude/10000)*2/FFT_N);
    Serial.print(print_buf);
    Serial.print("Time taken: ");Serial.print((t2-t1)*1.0/1000);Serial.println(" milliseconds!");
    
    //ZARDOZ section
    static int angle=0;
    Serial.print("ZARDOZISHNESS: ");
    Serial.println(angle);
    servo(SERVOPIN, angle);
    if ((fundamental_freq>HUMLOW) && (fundamental_freq<HUMHIGH)){
      angle++;
    }else{
      angle--;
    }  
    angle=constrain(angle,ZARDOZ_IS_DISPLEASED,ZARDOZ_IS_PLEASED);  
    if(angle==ZARDOZ_IS_PLEASED){
      digitalWrite(LEDPIN,1);
    }else{
      digitalWrite(LEDPIN,0);
    }
  }
}


#define SERVO_PULSE_MIN 500
#define SERVO_PULSE_MAX 2600
void servo(int pin, int angle){
  angle = map(angle,-150,150,SERVO_PULSE_MIN,SERVO_PULSE_MAX);
  Serial.println(angle);
  digitalWrite(pin, HIGH); 
  delayMicroseconds(angle); //servo pulse high side duration
  digitalWrite(pin, LOW);
}
