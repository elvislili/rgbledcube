#include "timer.h"


void Timer4_Init(uint16_t psc,uint16_t arr)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);               

	TIM_TimeBaseStructure.TIM_Period = arr;                            
	TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);                        
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                        
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);                    
 
	TIM_ITConfig(                                       				
		TIM4,                                           			
		TIM_IT_Update  |                                			
		TIM_IT_Trigger,                                 		
		ENABLE                                          				
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;             
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 	
	NVIC_Init(&NVIC_InitStructure);                                 	

	TIM_Cmd(TIM4, ENABLE);                                          
}


void Timer3_Init(uint16_t psc,uint16_t arr)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);             

	TIM_TimeBaseStructure.TIM_Period = arr;                         
	TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);                 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                      
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;      
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                     
 
	TIM_ITConfig(                                       				
		TIM3,                                           				
		TIM_IT_Update  |                                			
		TIM_IT_Trigger,                                 				
		ENABLE                                          				
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;       
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;             
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 	
	NVIC_Init(&NVIC_InitStructure);                                 

	TIM_Cmd(TIM3, ENABLE);                                          
}


void Timer2_Init(uint16_t psc,uint16_t arr)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);              

	TIM_TimeBaseStructure.TIM_Period = arr;                            
	TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);                    
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                       
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);                   
 
	TIM_ITConfig(                                       			
		TIM2,                                           			
		TIM_IT_Update  |                                			
		TIM_IT_Trigger,                                 			
		ENABLE                                          			
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                 	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;       	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;             
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 	
	NVIC_Init(&NVIC_InitStructure);                                 	

	TIM_Cmd(TIM2, ENABLE);                                          
}












