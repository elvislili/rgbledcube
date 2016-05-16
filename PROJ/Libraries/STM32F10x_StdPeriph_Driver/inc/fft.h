
#ifndef _fft_H
#define _fft_H

#include "stm32f10x.h"
#include "fft_tab.h"
#include "math.h"
#include "adc.h"
#include "led.h"

typedef struct									
{ 
	float real;
	float imag;
}compx;
					   
//#define fft_64 																			
#define fft_128 																		
//#define fft_256 																		
//#define fft_512 																		
//#define fft_1024 																		

#ifdef fft_64
#define fft_N 64
#endif
#ifdef fft_128
#define fft_N 128
#endif
#ifdef fft_256
#define fft_N 256
#endif
#ifdef fft_512
#define fft_N 512
#endif
#ifdef fft_1024
#define fft_N 1024
#endif	 

extern compx fftData[fft_N];    														
extern uint16_t fftIn[fft_N];    														
extern uint8_t fftOut[fft_N/2];    														
extern uint8_t sqrt_M(uint16_t temp);													

#define M sqrt_M(fft_N)																	

void fft_Convert(compx *xin);															
void fft_powerMag(void);																
void fft_Data(void);																	
void fft_Display(void);																	


#endif




