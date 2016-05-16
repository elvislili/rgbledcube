
#include "fft_tab.h"
#include "fft_list.h"
#include "fft.h"

compx fftData[fft_N]; 																				  
uint16_t fftIn[fft_N];    																
uint8_t fftOut[fft_N/2];    														


uint8_t sqrt_M(uint16_t temp)
{
	uint8_t m = 0;
	for(m = 1; (temp = temp/2) != 1; m++);											
	return m;
}

 



void fft_Convert(compx *xin)
{
//	uint16_t f,m,LH,nm,k;
	uint16_t i,j,L;
	uint16_t p;
	uint16_t le,B,ip;    		   
	compx t;
 	compx ws;
	
//	LH = N/2;
//	nm = N-2;    
//	j = N/2;		  
//	for(i = 1; i <= nm; i++)													
//	{
//		if(i < j)
//		{
//			t = xin[j];
//			xin[j] = xin[i];
//			xin[i] = t;
//		}																		
//		k = LH;
//		while(j >= k)
//		{
//			j = j-k;
//			k = k/2;
//		}
//		j = j+k;
//	}    
//	f = N;
//	for(m = 1; (f = f/2) != 1; m++);												

	for(L = 1;L <= M; L++) 																//fft  
	{  
//		le = mypow(2,L);																
		le = (2 << L) >> 1;
		B = le/2;	   	 
		for(j = 0; j <= B-1; j++)
		{			  
//			p = mypow(2,m-L)*j;  												   
			p = (((2 << M) >> L) >> 1)*j;
			ws.real = cos_tab[p];
			ws.imag = sin_tab[p];
			for(i = j; i <= fft_N-1; i = i+le)									
			{ 
				ip = i+B;		 
				
				t.real = xin[ip].real*ws.real-xin[ip].imag*ws.imag;
				t.imag = xin[ip].real*ws.imag+xin[ip].imag*ws.real;
				xin[ip].real = xin[i].real-t.real;
				xin[ip].imag = xin[i].imag-t.imag;
				xin[i].real  = xin[i].real+t.real;
				xin[i].imag  = xin[i].imag+t.imag;
			}
		}
	}
}


void fft_powerMag(void)
{
	int i;
	uint16_t tempfft = 0;
	for(i = 1; i < fft_N/2; i++)														
	{																					
		fftData[i].real = sqrt(fftData[i].real*fftData[i].real+fftData[i].imag*fftData[i].imag)
						  /(i == 0 ? fft_N:(fft_N/2));

//		fftOut[i] = (uint8_t)(fftData[i].real/2); 										
		tempfft = (uint8_t)fftData[i].real; 	
		if(tempfft > fftOut[i])
			fftOut[i] = tempfft;
		else
		{
			if(fftOut[i] > 0)
				fftOut[i]--;
		}
	}
}


void fft_Data(void)
{
	int i = 0;		
	for(i = 0; i < fft_N; i++)	
	{
		fftData[List[i]].real = fftIn[i];													
		fftData[List[i]].imag = 0;														
	}		
}


void fft_Display(void)
{
	char i,j;
	char k;
	int layerB;

	for(i = 0; i < 64; i++)																	
	{
//		k = i*3;
		k = (63-i)*3;
		for(j = 0; j < 8; j++)																
		{
			layerB = (7-j)*192;
			if(fftOut[i+1] > j)																
			{
				switch(i%3)
				{
					case 0:
						rgbled[rgb_order[k+0]+layerB] = 13;											
						rgbled[rgb_order[k+1]+layerB] = 0;									
						rgbled[rgb_order[k+2]+layerB] = 0;
					break;
					case 1:
						rgbled[rgb_order[k+0]+layerB] = 0;											
						rgbled[rgb_order[k+1]+layerB] = 5;									
						rgbled[rgb_order[k+2]+layerB] = 0;
					break;
					case 2:
						rgbled[rgb_order[k+0]+layerB] = 0;											
						rgbled[rgb_order[k+1]+layerB] = 0;									
						rgbled[rgb_order[k+2]+layerB] = 13;
					break;
				}
			}			
			else
			{
				rgbled[rgb_order[k+0]+layerB] = 0;											
				rgbled[rgb_order[k+1]+layerB] = 0;									
				rgbled[rgb_order[k+2]+layerB] = 0;
			}				
		}			
	}
}






