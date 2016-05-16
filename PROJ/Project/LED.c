
#include "LED.h"

uint8_t Cube_MODE = 2;															
uint8_t pictrue_order = 0;													
uint8_t W25Q64_Write_Flag = 0;													
uint8_t SPI_Buffer[4096];														
uint8_t Read_Buf[768];														
uint8_t W25QxxTempAA[3];													
uint8_t W25QxxFrame = 0;														
uint8_t W25QxxAddress = 0;													
uint16_t W25QxxSection = 0;													
uint16_t NowSection = 0;													
uint32_t randCount = 0;														
int16_t SpeedSum = 0,NumCount = 0;											
int8_t Color_red = 0,Color_green = 0,Color_blue = 0;							
int8_t light_red = 1,light_green = 0,light_blue = 0;							

uint8_t rgbled[1536];													


void randomColor(int8_t *gray_red,int8_t *gray_green,int8_t *gray_blue)
{
	while(1)																
	{
		srand(5*randCount+7*TIM5->CNT);											
		*gray_red = (int8_t)(rand()%16);										
		srand(3*randCount+9*TIM5->CNT);										
		*gray_green = rand()%16;												
		srand(7*randCount+5*TIM5->CNT);										
		*gray_blue = rand()%16;													
		if(*gray_red != 0 || *gray_green != 0 || *gray_blue != 0)				
			break;
	}
}


void ClearRGB(char Crgb,int8_t rank)
{
	uint8_t i = 0,j = 0;
	Crgb %= 3;
	rank %= 16;
	for(j = 0; j < 8; j++)
		for(i = 0; i < 64; i++)
			rgbled[rgb_order[3*i+Crgb]+192*j] = rank;				
}


void Clear(uint16_t layerA)
{
	uint16_t i = 0;
	layerA = 192*layerA;
	for(i = 0; i < 192; i++)
		rgbled[i+layerA] = 0;
}


void ClearALL(void)
{
	char i = 0;
	for(i = 0; i < 8; i++)
		Clear(i);																
}


void NVIC_Configuration(void) 
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
}


void Anode(uint8_t temp)    
{
    uint8_t i = 0;

    O_ST_RESET;															   
    for(i = 0; i < 8; i++)
    {
        O_CLK_RESET;														
        if(0 == (temp >> i & 0x01))											
            O_DATA_SET;															
        else
            O_DATA_RESET;													
        O_CLK_SET;															
    }
    O_ST_SET;  															
}
	

const uint8_t rgb_order[192] = 													//R¡úG¡úB
{
15,14,13,12,11,10,9,8,7,5,6,4,2,3,1,0,23,22,21,20,19,16,18,17,
47,46,45,44,43,42,41,40,39,37,38,36,34,35,33,32,24,25,27,26,28,29,31,30,
63,62,61,60,59,58,57,56,55,53,54,52,50,51,49,48,71,70,69,68,67,64,66,65,
95,94,93,92,91,90,89,88,87,85,86,84,82,83,81,80,72,73,75,74,76,77,79,78,
111,110,109,108,107,106,105,104,103,101,102,100,98,99,97,96,119,118,117,116,115,112,114,113,
143,142,141,140,139,138,137,136,135,132,134,133,130,131,129,128,120,121,123,122,124,125,127,126,
159,158,157,156,155,154,153,152,151,148,150,149,145,144,146,147,167,166,165,164,163,160,162,161,
191,190,189,188,187,186,184,185,183,180,182,181,178,179,177,176,168,169,171,170,172,173,175,174
};


void Send_Data(uint8_t rgbBit,uint8_t layerA)
{
	uint8_t i = 0;
	uint8_t BitRGB = 0;
	uint16_t Sum = 0;
	rgbBit &= 0x03;																//limit to 4 bit
	layerA &= 0x07;																//limit to 8 level
	Sum = layerA*192;															
	BitRGB = 0x01 << rgbBit;													
	rgb_ST_RESET;																
	for(i = 0; i < 192; i++)
	{
		rgb_CLK_RESET;															
		if(rgbled[i+Sum] & BitRGB)
			rgb_DATA_SET;													
		else
			rgb_DATA_RESET;														
		rgb_CLK_SET;															   
	}		
	rgb_ST_SET;																
}


void AxesConvert(void)
{				
	char i,j;
	int nn,mm,kk;
	for(j = 0; j < 8; j++)
	{
		mm = 192*j;
		nn = 32*j;
		for(i = 0; i < 32; i++)
		{
			kk = 6*i;
			rgbled[rgb_order[kk+0]+mm] =  Read_Buf[i+nn] & 0x0f;						
			rgbled[rgb_order[kk+3]+mm] = (Read_Buf[i+nn] >> 4)& 0x0f;						
			rgbled[rgb_order[kk+1]+mm] =  Read_Buf[256+i+nn] & 0x0f;						
			rgbled[rgb_order[kk+4]+mm] = (Read_Buf[256+i+nn] >> 4)& 0x0f;					
			rgbled[rgb_order[kk+2]+mm] =  Read_Buf[512+i+nn] & 0x0f;						
			rgbled[rgb_order[kk+5]+mm] = (Read_Buf[512+i+nn] >> 4)& 0x0f;					
		}				
	}					
}	


void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB |  \
                            RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
   
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}






