
#ifndef _SNAKE_H
#define _SNAKE_H

#include "stdlib.h"
#include "led.h"
#include "calculate.h"

#define Snake_Long 	20  														

typedef struct
{
	int8_t Sx;
	int8_t Sy;
	int8_t Sz;
}Coordinate;																	

extern Coordinate Snake[Snake_Long+1];											
extern int8_t Add_X,Add_Y,Add_Z;            									

uint8_t Collide(void);															
void Snake_Start(void);															
void Snake_Above(void);															
void Snake_Feed(void);															
void Snake_Move(void);															
void Snake_Show(int8_t snake_red,int8_t snake_green,int8_t snake_blue,
				int8_t feeed_red,int8_t feeed_green,int8_t feeed_blue);			

#endif



