
#include "usart.h"


void USART_Configuration(uint32_t usart_baudrate)
{
	USART_InitTypeDef USART_InitStructure;											
	GPIO_InitTypeDef GPIO_InitStructure;										
	NVIC_InitTypeDef NVIC_InitStructure;											
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10;									
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;						
	GPIO_Init(GPIOA,&GPIO_InitStructure);										
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9;								
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;							
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;							
	GPIO_Init(GPIOA,&GPIO_InitStructure);											
	
	USART_InitStructure.USART_BaudRate 			  = usart_baudrate;				
	USART_InitStructure.USART_StopBits 			  = USART_StopBits_1;				
	USART_InitStructure.USART_Parity 			  = USART_Parity_No;			
	USART_InitStructure.USART_Mode 				  = USART_Mode_Rx | USART_Mode_Tx;	
	USART_InitStructure.USART_WordLength 		  = USART_WordLength_8b;			
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	USART_Init(USART1,&USART_InitStructure);										
	USART_Cmd(USART1,ENABLE);													
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);								
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;							
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;					
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;								
	NVIC_Init(&NVIC_InitStructure);												
}


void Usart_Send_Data(uint8_t ch)
{
	USART_GetFlagStatus(USART1, USART_FLAG_TC); 			
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) ;
}




