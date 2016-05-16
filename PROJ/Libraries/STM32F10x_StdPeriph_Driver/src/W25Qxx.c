#include "W25Qxx.h"


void W25X_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	W25X_CS_H();
    /*Lock of the gpio */
	GPIO_PinLockConfig(GPIOA,GPIO_Pin_3);
}


void W25X_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);


	SPI_Cmd(SPI1,DISABLE);
	SPI_InitStructure.SPI_NSS 				= SPI_NSS_Soft;						
	SPI_InitStructure.SPI_Mode 				= SPI_Mode_Master;							
//	SPI_InitStructure.SPI_CPOL 				= SPI_CPOL_Low;							
//	SPI_InitStructure.SPI_CPHA 				= SPI_CPHA_1Edge;						
	SPI_InitStructure.SPI_CPOL 				= SPI_CPOL_High;						
	SPI_InitStructure.SPI_CPHA 				= SPI_CPHA_2Edge;						
	SPI_InitStructure.SPI_DataSize  		= SPI_DataSize_8b;						
	SPI_InitStructure.SPI_FirstBit  		= SPI_FirstBit_MSB;                   
	SPI_InitStructure.SPI_Direction 		= SPI_Direction_2Lines_FullDuplex;		
	SPI_InitStructure.SPI_CRCPolynomial 	= 7;									
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;			
	SPI_Init(SPI1, &SPI_InitStructure );
	SPI_Cmd(SPI1,ENABLE);                                                   	
}



uint8_t SPI_Flash_ReadWriteByte(uint8_t dat)
{
    while ((SPI1->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET)
	{
	}
	SPI1->DR = dat;
    while ((SPI1->SR & SPI_I2S_FLAG_RXNE) == (uint16_t)RESET)
	{
	}
	return (SPI1->DR);
}


    
uint16_t SPI_Flash_ReadID(void)
{
    uint16_t Temp = 0;
      
    W25X_CS_L();       
    SPI_Flash_ReadWriteByte(0x90);       											 
    SPI_Flash_ReadWriteByte(0x00);      
    SPI_Flash_ReadWriteByte(0x00);      
    SPI_Flash_ReadWriteByte(0x00);         
    Temp |= SPI_Flash_ReadWriteByte(0xFF) << 8;  
    Temp |= SPI_Flash_ReadWriteByte(0xFF);  
    W25X_CS_H();        
    return Temp;
} 

 
void SPI_Flash_Write_Enable(void)   
{
	W25X_CS_L();                            								
    SPI_Flash_ReadWriteByte(W25X_WriteEnable);      							
	W25X_CS_H();                           										 	      
} 


void SPI_FLASH_Write_Disable(void)   
{  
	W25X_CS_L();                            							
    SPI_Flash_ReadWriteByte(W25X_WriteDisable);									
	W25X_CS_H();                           										  	      
} 			    


uint8_t SPI_Flash_ReadSR(void)   
{  
	uint8_t byte=0;   
	W25X_CS_L();                            									
	SPI_Flash_ReadWriteByte(W25X_ReadStatusReg);    						
	byte = SPI_Flash_ReadWriteByte(0Xff);             							 
	W25X_CS_H();                           										 	      
	return byte;   
} 


void SPI_FLASH_Write_SR(u8 sr)   
{   
	W25X_CS_L();                            									
	SPI_Flash_ReadWriteByte(W25X_WriteStatusReg);								
	SPI_Flash_ReadWriteByte(sr);											 
	W25X_CS_H();                           											      
}   


void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01) == 0x01);   						
}  

void SPI_Flash_Erase_Chip(void)   
{                                             
    SPI_Flash_Write_Enable();                  										
    SPI_Flash_Wait_Busy();   
	W25X_CS_L();                            									
    SPI_Flash_ReadWriteByte(W25X_ChipErase);        						 
	W25X_CS_H();                           										  	      
	SPI_Flash_Wait_Busy();   				   								
}   


void SPI_Flash_Erase_Sector(uint32_t Dst_Addr)   
{   
	Dst_Addr *= 4096;
    SPI_Flash_Write_Enable();                  									 
    SPI_Flash_Wait_Busy();   
	W25X_CS_L();                            									   
    SPI_Flash_ReadWriteByte(W25X_SectorErase);      							
    SPI_Flash_ReadWriteByte((u8)((Dst_Addr) >> 16));  					
    SPI_Flash_ReadWriteByte((u8)((Dst_Addr) >> 8));   
    SPI_Flash_ReadWriteByte((u8)Dst_Addr);  
	W25X_CS_H();                           								   	      
    SPI_Flash_Wait_Busy();   				   									
}


void SPI_Flash_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead)   
{ 
 	uint16_t i;    												    
	W25X_CS_L();                            									
    SPI_Flash_ReadWriteByte(W25X_ReadData);         							  
//    SPI_Flash_ReadWriteByte(W25X_FastReadData);         							
    SPI_Flash_ReadWriteByte((u8)((ReadAddr) >> 16));  			
    SPI_Flash_ReadWriteByte((u8)((ReadAddr) >> 8));   
    SPI_Flash_ReadWriteByte((u8)ReadAddr);   
    for(i = 0; i < NumByteToRead; i++)
        pBuffer[i] = SPI_Flash_ReadWriteByte(0XFF);   						
	W25X_CS_H();                           									  	      
}  

 
void SPI_Flash_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
    SPI_Flash_Write_Enable();                  									 
	W25X_CS_L();                            									
    SPI_Flash_ReadWriteByte(W25X_PageProgram);      							
    SPI_Flash_ReadWriteByte((u8)((WriteAddr) >> 16)); 							
    SPI_Flash_ReadWriteByte((u8)((WriteAddr) >> 8));   
    SPI_Flash_ReadWriteByte((u8)WriteAddr);   
    for(i = 0; i < NumByteToWrite; i++)
		SPI_Flash_ReadWriteByte(pBuffer[i]);							
	W25X_CS_H();                           											  	      
	SPI_Flash_Wait_Busy();					   									
} 


void SPI_Flash_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 			 		 
	uint16_t pageremain;	   
	pageremain = 256-WriteAddr%256; 								 	    
	if(NumByteToWrite <= pageremain)
		pageremain = NumByteToWrite;						
	while(1)
	{	   
		SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite == pageremain)
			break;														
	 	else 															
		{
			pBuffer += pageremain;
			WriteAddr += pageremain;	

			NumByteToWrite -= pageremain;			  						
			if(NumByteToWrite > 256)
				pageremain = 256; 												
			else 
				pageremain = NumByteToWrite; 	  								
		}
	}	    
} 

	   
u8 SPI_FLASH_BUF[4096];
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;    

	secpos = WriteAddr/4096;													
	secoff = WriteAddr%4096;													
	secremain = 4096-secoff;													

	if(NumByteToWrite <= secremain)
		secremain = NumByteToWrite;											
	while(1) 
	{	
		SPI_Flash_Read(SPI_FLASH_BUF,secpos*4096,4096);							
		for(i = 0;i < secremain; i++)												
		{
			if(SPI_FLASH_BUF[secoff+i] != 0XFF)
				break;																  
		}
		if(i < secremain)													
		{
			SPI_Flash_Erase_Sector(secpos);										
			for(i = 0; i < secremain; i++)	   								
			{
				SPI_FLASH_BUF[i+secoff] = pBuffer[i];	  
			}
			SPI_Flash_Write_NoCheck(SPI_FLASH_BUF,secpos*4096,4096);			

		}
		else 
			SPI_Flash_Write_NoCheck(pBuffer,WriteAddr,secremain);						   
		if(NumByteToWrite == secremain)
			break;																
		else																	
		{
			secpos++;																
			secoff = 0;															

		   	pBuffer += secremain;  												
			WriteAddr += secremain;													
		   	NumByteToWrite -= secremain;											
			if(NumByteToWrite > 4096)
				secremain = 4096;												
			else 
				secremain = NumByteToWrite;								
		}	 
	}	 	 
}



