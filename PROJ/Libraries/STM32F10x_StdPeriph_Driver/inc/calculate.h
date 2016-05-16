#ifndef __calculate_H__
#define __calculate_H__

#include "LED.h"
#include "stm32f10x.h"

extern int8_t Get_Point[3];																					
extern const uint8_t Dat_print[];																			
extern const uint8_t MathSum[];																				

uint8_t Word_Swap(uint8_t temp);																			
void ColorPoint(int8_t X,int8_t Y,int8_t Z,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut);				
void Funnel_Shape(int8_t number,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut);						
void Line(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
		  int8_t red,int8_t green,int8_t blue,int8_t Add_Cut);												
void Rotat(int16_t number,int8_t red,int8_t green,int8_t blue);												
void Line_Change(int8_t number,int8_t red,int8_t green,int8_t blue);										
void Page(int8_t number,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut,int8_t way);						
void GetPoint(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,int8_t Number);					
void PlaneXY(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
			 int8_t red,int8_t green,int8_t blue,int8_t Add_Cut,int8_t fill);								
void Change_PlaneXY(int8_t number,int8_t red,int8_t green,int8_t blue);										
void PlaneYZ(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
			 int8_t red,int8_t green,int8_t blue,int8_t Add_Cut,int8_t fill);								
void PlaneZX(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
			 int8_t red,int8_t green,int8_t blue,int8_t Add_Cut,int8_t fill);								
void Box(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
		 int8_t red,int8_t green,int8_t blue,int8_t fill,int8_t Up_Down);									
void Box_Change(int8_t number,int8_t red,int8_t green,int8_t blue,int8_t Up_Down);							
void DNA_Change(int16_t number,int8_t red,int8_t green,int8_t blue);										
void Waveform(int16_t number,int8_t red,int8_t green,int8_t blue);											
void print(int number,const uint8_t *Data,int8_t red,int8_t green,int8_t blue,char m,int8_t direction);		
void Mov_Show(int number,const uint8_t *Data,int8_t red,int8_t green,int8_t blue,int8_t direction);			




#endif






