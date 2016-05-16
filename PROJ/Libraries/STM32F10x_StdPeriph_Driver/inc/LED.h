
#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"
#include "stdlib.h"

extern uint8_t Cube_MODE;													
extern uint8_t pictrue_order;												
extern uint8_t W25Q64_Write_Flag;											
extern uint8_t SPI_Buffer[4096];											
extern uint8_t Read_Buf[768];												
extern uint8_t W25QxxTempAA[3];												
extern uint8_t W25QxxFrame;													
extern uint8_t W25QxxAddress;												
extern uint16_t W25QxxSection;												
extern uint16_t NowSection;													
extern uint32_t randCount;													
extern int16_t SpeedSum,NumCount;											
extern int8_t Color_red,Color_green,Color_blue;								
extern int8_t light_red,light_green,light_blue;								
    
#define	rgb_OE_SET    	GPIOB->BSRR = 1<<15    
#define	rgb_ST_SET    	GPIOB->BSRR = 1<<14    
#define	rgb_CLK_SET   	GPIOB->BSRR = 1<<13    
#define	rgb_DATA_SET  	GPIOB->BSRR = 1<<12   

#define	O_CLK_SET   	GPIOC->BSRR = 1<<9    
#define	O_ST_SET    	GPIOC->BSRR = 1<<8    
#define	O_OE_SET    	GPIOC->BSRR = 1<<7    
#define	O_DATA_SET  	GPIOC->BSRR = 1<<6   

    
#define	rgb_OE_RESET    GPIOB->BRR = 1<<15    
#define	rgb_ST_RESET    GPIOB->BRR = 1<<14    
#define	rgb_CLK_RESET   GPIOB->BRR = 1<<13    
#define	rgb_DATA_RESET  GPIOB->BRR = 1<<12   

#define	O_CLK_RESET   	GPIOC->BRR = 1<<9    
#define	O_ST_RESET    	GPIOC->BRR = 1<<8    
#define	O_OE_RESET    	GPIOC->BRR = 1<<7    
#define	O_DATA_RESET  	GPIOC->BRR = 1<<6   

#define ScanTime 		45													
#define ScanFosc 		300													
//#define ScanFosc 		200													

extern uint8_t rgbled[1536];												
extern const uint8_t rgb_order[192];										

void randomColor(int8_t *gray_red,int8_t *gray_green,int8_t *gray_blue);	
void ClearALL(void);														
void ClearRGB(char Crgb,int8_t rank);										
void AxesConvert(void);														
void GPIO_Configuration(void);          									
void NVIC_Configuration(void);												
void Anode(uint8_t temp);               									
void Send_Data(uint8_t rgbBit,uint8_t layer);								



#endif

