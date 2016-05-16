
#include "stm32f10x_it.h"
#include "time_show.h"


void USART1_IRQHandler(void)
{
	static uint16_t Usart_Count = 0;	
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE) == SET)										
	{
		if(0 == Cube_MODE)																		
		{
			if(0 == Usart_Count || 1 == Usart_Count)											
			{
				TIM_Cmd(TIM2,DISABLE);                                          				
				TIM_Cmd(TIM3,DISABLE);                                          				
//				TIM_Cmd(TIM4,DISABLE);                                          				
				TIM_Cmd(TIM5,DISABLE);                                          				
			}
			SPI_Buffer[Usart_Count] = USART_ReceiveData(USART1);								
			if(++Usart_Count >= (3840+3))														
			{
				Usart_Count = 0;																
				W25Q64_Write_Flag = 1;															
			}
		}
	}
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);											
}


void TIM2_IRQHandler(void)   								
{
	static uint8_t Layer = 0;																	
	static uint8_t Digit = 0;																	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET) 											
    {
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  											
		
		if(++Layer >= 8)																		
		{
			Layer = 0;																			
			if(++Digit >= 4)																	
				Digit = 0;																		
			TIM_SetAutoreload(TIM2,ScanTime << Digit);											
		}
		
		O_OE_SET; 																				
		rgb_OE_SET;																				
		Anode(1 << Layer);																		
		Send_Data(Digit,Layer);																				
		O_OE_RESET;																				
		rgb_OE_RESET;																			
		
		randCount++;																			
	}
}


void TIM3_IRQHandler(void)   								
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET) 											
    {
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  											 

		switch(Cube_MODE)																		
		{
			case 0:
				ReadW25Q64();																	
			break;
			case 1:
			break;
			case 2:
				Cartoon();																		
			case 3:																				
			break;
			case 4:
				Snake_scrolling();																
			break;
		}
    }
}


void TIM4_IRQHandler(void)   								
{
	static uint16_t fft_Num = 0;
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET) 		
    {
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  		
		
		fftIn[fft_Num] = Get_ADC(ADC_Channel_11);
		if(++fft_Num > fft_N)
			fft_Num = 0;
    }
}



void NMI_Handler(void)
{
}


void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
