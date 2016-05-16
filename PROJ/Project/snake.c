
#include "SNAKE.h"

Coordinate Snake[Snake_Long+1];																				


int8_t Add_X = 0,Add_Y = 0,Add_Z = 0;            															
#define Start_Long 	3																						
uint8_t New_Long = 0;																						


uint8_t Collide(void)
{
	int i;
	
	for(i = 2; i < New_Long; i++)																	
	{
		if(Snake[1].Sx == Snake[i].Sx && Snake[1].Sy == Snake[i].Sy && Snake[1].Sz == Snake[i].Sz)								
			return 1;
	} 	
	if(Snake[1].Sx >= 0 && Snake[1].Sx <= 7 && Snake[1].Sy >= 0 && Snake[1].Sy <= 7 && Snake[1].Sz >= 0 && Snake[1].Sz <= 7)	
		return 0 ;
	else 
		return 1;	  											
}

void Snake_Start(void)
{
	int i = 0;
	New_Long = Start_Long;																					
	for(i = 0; i < Snake_Long; i++)
	{
		Snake[i].Sx = 0;
		Snake[i].Sy = 0;										
		Snake[i].Sz = 0;																					
	}	
	Snake[1].Sx = 1;
	Snake[1].Sy = 0;														
	Snake[1].Sz = 0;																						

	Snake[2].Sx = 0;
	Snake[2].Sy = 0;														
	Snake[2].Sz = 0;																						
	
	Add_X = 0;
	Add_Y = 0;            												
	Add_Z = 0;            																					
}


void Snake_Above(void)
{
	int i = 1;
Back:
	srand(TIM2->CNT);																						
	Snake[0].Sx = (char)(rand()%8);																			
	Snake[0].Sy = (char)(rand()%8);																				
	Snake[0].Sz = (char)(rand()%8);																				

	i = 1;
	while(i <= New_Long) 																					
	{
		if(Snake[i].Sx == Snake[0].Sx && Snake[i].Sy == Snake[0].Sy && Snake[i].Sz == Snake[0].Sz)			
			goto Back;																						
		i++;
	}        											
}


void Snake_Feed(void)
{
	if(Snake[1].Sx == Snake[0].Sx && Snake[1].Sy == Snake[0].Sy && Snake[1].Sz == Snake[0].Sz)				
	{
		New_Long++;																							
		if(New_Long != Snake_Long+1)																		
			Snake_Above();																					
		else if(New_Long == Snake_Long+1) 																	
		{
			New_Long = Start_Long;																			
			Snake_Start();																					
			Snake_Above();																					
		}
	}
}


void Snake_Move(void)
{
	int i = 0;
	if(0 != Add_X || 0 != Add_Y || 0 != Add_Z)																
	{
		for(i = New_Long-1; i; i--)													
		{
			Snake[i].Sx = Snake[i-1].Sx;
			Snake[i].Sy = Snake[i-1].Sy;						
			Snake[i].Sz = Snake[i-1].Sz;																	
		}   
		Snake[1].Sx = Snake[2].Sx+Add_X;
		Snake[1].Sy = Snake[2].Sy+Add_Y;                    				
		Snake[1].Sz = Snake[2].Sz+Add_Z;                    												
	}
}


void Snake_Show(int8_t snake_red,int8_t snake_green,int8_t snake_blue,int8_t feeed_red,int8_t feeed_green,int8_t feeed_blue)
{
	int i;
	ClearALL();																								
	for(i = 1; i < New_Long; i++)																			
		ColorPoint(Snake[i].Sx,Snake[i].Sy,Snake[i].Sz,snake_red,snake_green,snake_blue,1);
	ColorPoint(Snake[0].Sx,Snake[0].Sy,Snake[0].Sz,feeed_red,feeed_green,feeed_blue,1);						
}



