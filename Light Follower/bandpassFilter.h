#ifndef BANDPASSFILTER_H_
#define BANDPASSFILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 100 Hz

fixed point precision: 32 bits

* 0 Hz - 3 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

* 3.2 Hz - 4 Hz
  gain = 6
  desired ripple = 10 dB
  actual ripple = n/a

* 4.2 Hz - 50 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

*/

#define BANDPASSFILTER_TAP_NUM 585

typedef struct {
  int history[BANDPASSFILTER_TAP_NUM];
  unsigned int last_index;
} bandpassFilter;

void bandpassFilter_init(bandpassFilter* f);
void bandpassFilter_put(bandpassFilter* f, int input);
int bandpassFilter_get(bandpassFilter* f);

#endif