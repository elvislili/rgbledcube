#ifndef _W25Qxx_H
#define _W25Qxx_H			    

#include "stm32f10x.h"

#define W25X_CS_L()          (GPIOA->BRR  = GPIO_Pin_3)
#define W25X_CS_H()          (GPIOA->BSRR = GPIO_Pin_3)

//指令表
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

//初始化
void W25X_GPIO_Config(void);         														
void W25X_Init(void);                														

//获取状态
uint16_t SPI_Flash_ReadID(void);          													
void SPI_FLASH_Write_SR(uint8_t sr);  														
void SPI_FLASH_Write_Enable(void);  														
void SPI_FLASH_Write_Disable(void);															
void SPI_Flash_Erase_Sector(uint32_t Dst_Addr);												 
void SPI_Flash_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);   			
void SPI_Flash_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);			
void SPI_Flash_Erase_Chip(void);    	  													
void SPI_Flash_Erase_Sector(uint32_t Dst_Addr);												
void SPI_Flash_Wait_Busy(void);           													



#endif

