
#include "ADC.H"
		   

void fft_ADC_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1,ENABLE);	 
 
//	RCC_ADCCLKConfig(RCC_PCLK2_Div6);                                  
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);                                   
	                       
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		               
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);                                                

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	               
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	                   
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	               
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	            
	ADC_InitStructure.ADC_NbrOfChannel = 1;	                          
	ADC_Init(ADC1, &ADC_InitStructure);	                              
 
	ADC_Cmd(ADC1, ENABLE);	                                           
	ADC_ResetCalibration(ADC1);	                                       
	while(ADC_GetResetCalibrationStatus(ADC1));	                        
	ADC_StartCalibration(ADC1);		                                 
	while(ADC_GetCalibrationStatus(ADC1));		                        
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		                       
}				  


uint16_t Get_ADC(uint8_t ch)   
{
  	
	ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_1Cycles5);			    
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);		                      
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));						
	return ADC_GetConversionValue(ADC1);	                           
}





























