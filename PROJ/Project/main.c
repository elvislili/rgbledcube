/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "led.h"
#include "timer.h"
#include "calculate.h"
#include "snake.h"
#include "adc.h"
#include "fft.h"
#include "usart.h"
#include "ir_nec.h"
#include "W25Qxx.h"

uint16_t strCount = 0;	

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
uint32_t EXTI_Line;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


int main(void)
{  
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();
  
  /* Configure all unused GPIO port pins in Analog Input mode (floating input
     trigger OFF), this will reduce the power consumption and increase the device
     immunity against EMI/EMC *************************************************/

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE |RCC_APB2Periph_GPIOF | 
                         RCC_APB2Periph_GPIOG, ENABLE);  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_Init(GPIOG, &GPIO_InitStructure);  

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | 
                         RCC_APB2Periph_GPIOG, DISABLE);  
  
  /* Global initialization ends above.*/
  /* -------------------------------------------------------------------------- */

  /* Please add your project initialization code below */
   GPIO_Configuration();																				
	NVIC_Configuration();																				
	USART_Configuration(460800);																		
	IR_ENC_Init();																						
	
	W25X_GPIO_Config();         																		
	W25X_Init();                																		

	if(SPI_Flash_ReadID() == 0XEF16)																	
	{																									
		SPI_Flash_Read(W25QxxTempAA,0,3);   															
		W25QxxFrame = W25QxxTempAA[2];																	
		W25QxxSection = W25QxxTempAA[0]+(W25QxxTempAA[1] << 8);											
	}  

	fft_ADC_Init();																						
    Timer2_Init(ScanFosc,ScanTime);           															
//    Timer3_Init(7200,100);           																	
//    Timer4_Init(720,10);																				          						
    Timer3_Init(12800,60);           																	
    Timer4_Init(1280,10);																				          						
		
	O_OE_SET; 																							

	while(1)
    {
		if(0 == Cube_MODE)
		{
			if(1 == W25Q64_Write_Flag)																	
			{
				if(SPI_Flash_ReadID() != 0XEF16)																		
					Usart_Send_Data('N');																			
				else																					
				{
					W25Q64_Write_Flag = 0;																
					SPI_Flash_Erase_Sector(strCount);													 
					SPI_Flash_Write(SPI_Buffer,strCount*4096,3840+3);									
					strCount++;																			
					if(strCount == (SPI_Buffer[0]+(SPI_Buffer[1] << 8)))								
					{																					
						strCount = 0;																	
						SPI_Flash_Read(W25QxxTempAA,0,3);   											
						W25QxxFrame = W25QxxTempAA[2];													
						W25QxxSection = W25QxxTempAA[0]+(W25QxxTempAA[1] << 8);							

						TIM_Cmd(TIM2,ENABLE);                                          					
						TIM_Cmd(TIM3,ENABLE);                                          					
//						TIM_Cmd(TIM4,ENABLE);                                          					
						TIM_Cmd(TIM5,ENABLE);                                          					
					}
					else																				
						Usart_Send_Data('O');															
				}
			}
		}	
		else if(1 == Cube_MODE)
		{
			fft_Data();																					
			fft_Convert(fftData);																		
			fft_powerMag();																				
			fft_Display();																				
		}		
	}
}


