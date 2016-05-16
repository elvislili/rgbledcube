#include "IR_NEC.h"


void IR_ENC_Init(void)							//infrared conf
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;									
	GPIO_Init(GPIOC,&GPIO_InitStructure);												

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);                			

	TIM_TimeBaseStructure.TIM_Period = Step;                 							
//	TIM_TimeBaseStructure.TIM_Prescaler =(72-1);                       				 
	TIM_TimeBaseStructure.TIM_Prescaler =(128-1);                       			
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                        			
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;         				
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);                     				
 
	TIM_ITConfig(                                       						
		TIM5,                                           							
		TIM_IT_Update  |                                							
		TIM_IT_Trigger,                                 								
		ENABLE                                          							
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                 				
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;       					
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              				
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 					
	NVIC_Init(&NVIC_InitStructure);                                 					

	TIM_Cmd(TIM5, ENABLE);                                          		
}
unsigned char	IR_BT;		         													
unsigned char	NEC[4];		         												
unsigned int	cntStep;															
unsigned char	IRa,IRb;			 													
unsigned char	IRsync;				 												
unsigned char	BitN;                												


#define    Boot_Limit	    (((9000+4500) +2000)/Step)	  							
#define    Boot_Lower	    (((9000+4500) -2000)/Step)	  							  
#define    Bit1_Limit       ((2250 +800)/Step)	          								
#define    Bit0_Limit       ((1125 +400)/Step)			  							


void IR_NEC(void)
{ 	 
	cntStep++;		   																

	IRb = IRa;		   																	
	IRa = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0);									

	if(IRb && !IRa)				  	  													
	{
		if(cntStep > Boot_Limit)      												
			IRsync = 0;				  												
		else if(cntStep > Boot_Lower)												
		{ 
			IRsync = 1; 
			BitN = 32; 
		}																					  
		else if(IRsync)															
		{
			if(cntStep > Bit1_Limit)												
				IRsync = 0;	           
			else
			{	
				NEC[3] >>= 1;				
				if(cntStep > Bit0_Limit)
					NEC[3] |= 0x80;    											
                if(--BitN == 0)				
				{
					IRsync = 0;															
					IR_BT = 1; 														
				}
				else if((BitN & 0x07)== 0)										
				{	
					NEC[0] = NEC[1]; 
					NEC[1] = NEC[2]; 
					NEC[2] = NEC[3];   
				}
			}
		}
		cntStep = 0;   																
	}
} 


void TIM5_IRQHandler(void)   														
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update) != RESET) 								
    {
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  								

		IR_NEC();																
		if(1 == IR_BT)																	
		{
			KeyHandle();      												
			IR_BT = 0;		        											
		}
	}
}



void KeyHandle(void)
{
   switch(NEC[2])	     
   {
		case 0x0c: 
			Cube_MODE = 1;																//dft
			ClearALL();																	
			TIM_Cmd(TIM3,DISABLE);                                          		
			TIM_Cmd(TIM3,DISABLE);                                          	
			TIM_Cmd(TIM4,ENABLE);                                          		
			TIM_Cmd(TIM4,ENABLE);                                          				
			break;																
		case 0x18:  
			Cube_MODE = 2;																//Æôanimation
			SpeedSum = 0;
			NumCount = 0;
			pictrue_order = 0;											
			ClearALL();														
			TIM_Cmd(TIM3,ENABLE);                                          		
			TIM_Cmd(TIM3,ENABLE);                                          	
			TIM_Cmd(TIM4,DISABLE);                                          	
			TIM_Cmd(TIM4,DISABLE);                                          	
			break;																	
		case 0x5e:  
			Cube_MODE = 3;															
			TIM_Cmd(TIM3,DISABLE);                                          	
			TIM_Cmd(TIM3,DISABLE);                                          	
			TIM_Cmd(TIM4,DISABLE);                                          	
			TIM_Cmd(TIM4,DISABLE);                                          	
			ClearALL();																
			ClearRGB(0,1);															
			light_red = 1;
			light_green = 0;
			light_blue = 0;														
			break;															
		case 0x08:  
			if(3 == Cube_MODE)
			{
				if(light_red < 15)
					light_red++;
				ClearRGB(0,light_red);										
			}
			break;													
		case 0x1c:  
			if(3 == Cube_MODE)
			{
				if(light_green < 15)
					light_green++;
				ClearRGB(1,light_green);											
			}
			else if(4 == Cube_MODE)
			{
				Add_X = 0;
				Add_Y = 0;
				Add_Z = -1;            													
			}
			break;																
		case 0x5a:  
			if(3 == Cube_MODE)
			{
				if(light_blue < 15)
					light_blue++;
				ClearRGB(2,light_blue);									
			}
			break;																
		case 0x42:  
			if(3 == Cube_MODE)
			{
				if(light_red > 0)
					light_red--;
				ClearRGB(0,light_red);										
			}
			break;																	
		case 0x52:  
			if(3 == Cube_MODE)
			{
				if(light_green > 0)
					light_green--;
				ClearRGB(1,light_green);										
			}
			else if(4 == Cube_MODE)
			{
				Add_X = 0;
				Add_Y = 0;
				Add_Z = 1;            													
			}
			break;																
		case 0x4a:  
			if(3 == Cube_MODE)
			{
				if(light_blue > 0)
					light_blue--;
				ClearRGB(2,light_blue);											
			}
			break;																
		case 0x16:  
			Cube_MODE = 0;												
			W25QxxAddress = 0;													
			NowSection = 0;															
			ClearALL();															
			TIM_Cmd(TIM3,ENABLE);                                          		
			TIM_Cmd(TIM3,ENABLE);                                          			
			TIM_Cmd(TIM4,DISABLE);                                          		
			TIM_Cmd(TIM4,DISABLE);                                          			
			break;																	
		case 0x19:  
			if(4 == Cube_MODE)
			{
				Add_X = 0;
				Add_Y = -1;
				Add_Z = 0;            													
			}
			break;																	
		case 0x0d:  
			Cube_MODE = 4;															
			SpeedSum = 0;
			NumCount = 0;
			ClearALL();																
			TIM_Cmd(TIM3,ENABLE);                                          			
			TIM_Cmd(TIM3,ENABLE);                                          		
			TIM_Cmd(TIM4,DISABLE);                                          		
			TIM_Cmd(TIM4,DISABLE);                                          			
			Snake_Start();															
			Snake_Above();																
			Snake_Show(10,1,0,0,10,0);												
			break;																		
		case 0x07:  
			if(4 == Cube_MODE)
			{
				Add_X = -1;
				Add_Y = 0;
				Add_Z = 0;            										
			}
			break;																	
		case 0x15:  
			break;																
		case 0x09:
			if(4 == Cube_MODE)
			{
				Add_X = 1;
				Add_Y = 0;
				Add_Z = 0;            										
			}
			break;																	
		case 0x44:  
			break;																	
		case 0x40:  
			if(4 == Cube_MODE)
			{
				Add_X = 0;
				Add_Y = 1;
				Add_Z = 0;            												
			}
			break;																
		case 0x43:  
			break;																	
		case 0x45:  
			break;																	
		case 0x47:  
			break;																	
		default:
			break;
	}
}



