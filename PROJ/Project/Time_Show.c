
#include "time_show.h"


void flash0(uint8_t flashorder)
{
	if(++SpeedSum >= 5)																	//control speed
	{
		SpeedSum = 0;																	//spped=0
		if(0 == NumCount)
			ClearALL();																	
		switch(NumCount/64)
		{
			case 0:
			case 1:
				randomColor(&Color_red,&Color_green,&Color_blue);						
				Funnel_Shape(NumCount,Color_red,Color_green,Color_blue,1);				//funnel shape
			break;
			case 2:
			case 3:
				Funnel_Shape(NumCount-128,0,0,0,0);										
			break;
			case 4:
				randomColor(&Color_red,&Color_green,&Color_blue);			
				Funnel_Shape(NumCount-256,Color_red,Color_green,Color_blue,1);		
				Funnel_Shape(383-NumCount,Color_red,Color_green,Color_blue,1);			
			break;
			case 5:
				Funnel_Shape(383-NumCount,0,0,0,0);									
				Funnel_Shape(NumCount-256,0,0,0,0);									
			break;
			case 6:
				if(NumCount < 392)
					ColorPoint(0,NumCount-384,0,Color_red,Color_green,Color_blue,1);	
				else
					Line(0,0,NumCount-391,0,7,NumCount-391,Color_red,Color_green,Color_blue,1);	
			break;
		}

		if(++NumCount >= 399)															
		{
			NumCount = 0;
			pictrue_order = flashorder;													
		}
	}
}


void flash1(uint8_t flashorder)
{
	if(++SpeedSum >= 10)															
	{
		SpeedSum = 0;																
		if(0 == NumCount)
		{
			ClearALL();														
			randomColor(&Color_red,&Color_green,&Color_blue);						
		}
		Line_Change(NumCount,Color_red,Color_green,Color_blue);						
		if(++NumCount >= 32)												
		{
			NumCount = 0;
			pictrue_order = flashorder;												
		}
	}
}


void flash2(uint8_t flashorder)
{
	if(++SpeedSum >= 6)																
	{
		SpeedSum = 0;																	
//		if(0 == NumCount)
//		{
//			ClearALL();															
//			randomColor(&Color_red,&Color_green,&Color_blue);							
//		}
		switch(NumCount/15)
		{
			case 0:
				if(0 != NumCount)
					Page(NumCount-1,0,0,0,0,0);										
				Page(NumCount,Color_red,Color_green,Color_blue,1,0);			
			break;
			case 1:
				if(15 != NumCount)
					Page(30-NumCount,0,0,0,0,4);									
				Page(29-NumCount,Color_red,Color_green,Color_blue,1,4);					
			break;
			case 2:
				if(30 != NumCount)
					Page(NumCount-31,0,0,0,0,5);									
				Page(NumCount-30,Color_red,Color_green,Color_blue,1,5);					
			break;
			case 3:
				if(45 != NumCount)
					Page(60-NumCount,0,0,0,0,3);									
				Page(59-NumCount,Color_red,Color_green,Color_blue,1,3);					
			break;
			case 4:
				if(60 != NumCount)
					Page(NumCount-61,0,0,0,0,2);										
				Page(NumCount-60,Color_red,Color_green,Color_blue,1,2);					
			break;
			case 5:
				if(75 != NumCount)
					Page(90-NumCount,0,0,0,0,6);									
				Page(89-NumCount,Color_red,Color_green,Color_blue,1,6);			
			break;
			case 6:
				if(90 != NumCount)
					Page(NumCount-91,0,0,0,0,7);									
				Page(NumCount-90,Color_red,Color_green,Color_blue,1,7);				
			break;
			case 7:
				if(105 != NumCount)
					Page(120-NumCount,0,0,0,0,1);								
				Page(119-NumCount,Color_red,Color_green,Color_blue,1,1);			
			break;
			default:
				if(NumCount < 127)
					Line(0,0,127-NumCount,0,7,127-NumCount,Color_red,Color_green,Color_blue,0);	
				else
					ColorPoint(0,NumCount-127,0,Color_red,Color_green,Color_blue,0);	
			break;
		}
		if(++NumCount >= 134)															
		{
			NumCount = 0;
			pictrue_order = flashorder;													
		}
	}
}	
	

void flash3(uint8_t flashorder)
{
	if(++SpeedSum >= 10)																
	{
		SpeedSum = 0;																
		if(0 == NumCount)
		{
			ClearALL();																
			randomColor(&Color_red,&Color_green,&Color_blue);						
		}
		
		if(NumCount < 8)
			ColorPoint(NumCount,7,7,Color_red,Color_green,Color_blue,1);				
		else if(NumCount < 15)
			Line(0,7,14-NumCount,7,7,14-NumCount,Color_red,Color_green,Color_blue,1);	
		else if(NumCount < 41)
			Change_PlaneXY(NumCount-15,Color_red,Color_green,Color_blue);				
		if(++NumCount >= 41)														
		{
			NumCount = 0;
			pictrue_order = flashorder;												
		}
	}
}


void flash4(uint8_t flashorder)
{
	if(++SpeedSum >= 15)															
	{
		SpeedSum = 0;																	
		if(0 == NumCount)
		{
			ClearALL();																	
			randomColor(&Color_red,&Color_green,&Color_blue);							
		}
		Box_Change(NumCount,Color_red,Color_green,Color_blue,0);						
		if(++NumCount >= 108)															
		{
			NumCount = 0;
			pictrue_order = flashorder;												
		}
	}
}


void flash5(uint8_t flashorder)
{
	if(++SpeedSum >= 5)																
	{
		SpeedSum = 0;															
		if(15 == NumCount)
		{
			ClearALL();																	
			randomColor(&Color_red,&Color_green,&Color_blue);							
		}
		if(NumCount < 7)
			Line(0,0,7-NumCount,7,0,7-NumCount,Color_red,Color_green,Color_blue,0);	
		else if(NumCount < 15)
			ColorPoint(14-NumCount,0,0,Color_red,Color_green,Color_blue,0);				
		else if(NumCount < 23)
			ColorPoint(NumCount-15,NumCount-15,0,Color_red,Color_green,Color_blue,1);	
		else if(NumCount < 30)
			Line(0,0,NumCount-22,7,7,NumCount-22,Color_red,Color_green,Color_blue,1);	
		else if(NumCount < 285)
			DNA_Change(NumCount-30,Color_red,Color_green,Color_blue);					
		if(++NumCount >= 285)															
		{
			NumCount = 0;
			pictrue_order = flashorder;													
		}
	}
}


void flash6(uint8_t flashorder)
{
	if(++SpeedSum >= 10)															
	{
		SpeedSum = 0;																
		if(0 == NumCount)
		{
			ClearALL();																	
			randomColor(&Color_red,&Color_green,&Color_blue);							
		}
		Waveform(NumCount,Color_red,Color_green,Color_blue);						
		if(++NumCount >= 204)															
		{
			NumCount = 0;
			pictrue_order = flashorder;													
		}
	}
}


void flash7(uint8_t flashorder)
{
	if(++SpeedSum >= 5)																
	{
		SpeedSum = 0;																	
		if(0 == NumCount%77)
		{
			ClearALL();																
			randomColor(&Color_red,&Color_green,&Color_blue);						
		}
		print(NumCount,Dat_print+NumCount/77*8,Color_red,Color_green,Color_blue,1,0);	
		if(++NumCount >= 1155)														
		{
			NumCount = 0;
			pictrue_order = flashorder;											
		}
	}
}


void flash8(uint8_t flashorder)
{
	if(++SpeedSum >= 15)															
	{
		SpeedSum = 0;																
		if(0 == NumCount)
		{
			ClearALL();																
			randomColor(&Color_red,&Color_green,&Color_blue);							
		}
		Mov_Show(NumCount,MathSum,Color_red,Color_green,Color_blue,1);					
		if(++NumCount >= 152)													
		{
			NumCount = 0;
			pictrue_order = flashorder;													
		}
	}
}

const uint8_t Circle[29]={
0,1,2,3,4,5,6,7,15,23,31,39,47,55,63,62,61,60,59,58,57,56,48,40,32,24,16,8,0
};

void flash9(uint8_t flashorder)
{
	char i,j;
	if(++SpeedSum >= 15)															
	{
		SpeedSum = 0;																
		if(0 == NumCount)
		{
			ClearALL();															
			randomColor(&Color_red,&Color_green,&Color_blue);						
		}
		if(NumCount < 50)
		{
			switch(NumCount/29)
			{
				case 0:
					if(NumCount > 7)
					i = Circle[NumCount-8]%8;
					j = Circle[NumCount-8]/8;
					Line(i,j,0,i,j,7,0,0,0,0);									
				case 1:
					i = Circle[NumCount%29]%8;
					j = Circle[NumCount%29]/8;
					Line(i,j,0,i,j,7,Color_red,Color_green,Color_blue,1);			
				break;
			}
		}
		else if(NumCount < 56)
		{
			i = NumCount-49;
			Line(1,0,i,6,0,i,0,0,0,0);												
			Line(1,7,i,6,7,i,0,0,0,0);												
			Line(0,1,i,0,6,i,0,0,0,0);												
			Line(7,1,i,7,6,i,0,0,0,0);												
		}
		else if(NumCount < 62)
		{
			i = (NumCount-54)/2;
			Box(i,i,i,7-i,7-i,7-i,Color_red,Color_green,Color_blue,0,0);				
		}
		else if(NumCount < 70)
		{
			i = (69-NumCount)/2;
			Box(i,i,i,7-i,7-i,7-i,0,0,0,0,0);									
		}
			
		if(++NumCount >= 70)														
		{
			NumCount = 0;
			pictrue_order = flashorder;												
		}
	}
}


void flash10(uint8_t flashorder)
{
	char i,j;
	int mm,kk;
	if(++SpeedSum >= 15)																
	{
		SpeedSum = 0;																	
		if(0 == NumCount%20)
			randomColor(&Color_red,&Color_green,&Color_blue);							
			
		for(j = 0; j < 8; j++)
		{
			mm = 192*j;
			for(i = 0; i < 64; i++)
			{
				kk = 3*i;
				if(Shape[i+NumCount%154*64] & (0x80 >> j))
				{
					rgbled[rgb_order[kk+0]+mm] = Color_red; 			
					rgbled[rgb_order[kk+1]+mm] = Color_green;			
					rgbled[rgb_order[kk+2]+mm] = Color_blue;	
				}	
				else
				{
					rgbled[rgb_order[kk+0]+mm] = 0; 			
					rgbled[rgb_order[kk+1]+mm] = 0;			
					rgbled[rgb_order[kk+2]+mm] = 0;	
				}
			}				
		}		
		
		if(++NumCount >= 308)														
		{
			NumCount = 0;
			pictrue_order = flashorder;													
		}
	}
}


void flash11(uint8_t flashorder)
{
	char i,j;
	int mm,kk;
	if(++SpeedSum >= 15)																
	{
		SpeedSum = 0;																
		if(0 == NumCount%20)
			randomColor(&Color_red,&Color_green,&Color_blue);							
			
		for(j = 0; j < 8; j++)
		{
			mm = 192*j;
			for(i = 0; i < 64; i++)
			{
				kk = 3*i;
				if(Waveled[i+NumCount%29*64] & (0x80 >> j))
				{
					rgbled[rgb_order[kk+0]+mm] = Color_red; 			
					rgbled[rgb_order[kk+1]+mm] = Color_green;			
					rgbled[rgb_order[kk+2]+mm] = Color_blue;	
				}	
				else
				{
					rgbled[rgb_order[kk+0]+mm] = 0; 			
					rgbled[rgb_order[kk+1]+mm] = 0;			
					rgbled[rgb_order[kk+2]+mm] = 0;	
				}
			}				
		}		
		
		if(++NumCount >= 116)															
		{
			NumCount = 0;
			pictrue_order = flashorder;											
		}
	}
}


void flash12(uint8_t flashorder)
{
	char i,j;
	int kk,nn,mm;
	if(++SpeedSum >= 15)															
	{
		SpeedSum = 0;																	
			
		for(j = 0; j < 8; j++)
		{
			mm = 192*j;
			nn = 32*j;
			for(i = 0; i < 32; i++)
			{
				kk = 6*i;
				rgbled[rgb_order[kk+0]+mm] =  Dmax[768*NumCount+i+nn] & 0x0f;						
				rgbled[rgb_order[kk+3]+mm] = (Dmax[768*NumCount+i+nn] >> 4)& 0x0f;					
				rgbled[rgb_order[kk+1]+mm] =  Dmax[768*NumCount+i+nn+256] & 0x0f;					
				rgbled[rgb_order[kk+4]+mm] = (Dmax[768*NumCount+i+nn+256] >> 4)& 0x0f;		
				rgbled[rgb_order[kk+2]+mm] =  Dmax[768*NumCount+i+nn+512] & 0x0f;					
				rgbled[rgb_order[kk+5]+mm] = (Dmax[768*NumCount+i+nn+512] >> 4)& 0x0f;			
			}				
		}					

		if(++NumCount >= 275)														
		{
			NumCount = 0;
			pictrue_order = flashorder;												
		}
	}
}


const uint8_t BoxDat[]={
0x00,0x00,0x00,0x77,0x77,0x00,0x77,0x00,0x77,0x00,0x77,0x77,0x10,0x10,0x10,0x76,0x76,0x01,0x76,0x10,0x76,0x00,0x76,0x76,
0x20,0x20,0x20,0x75,0x75,0x02,0x75,0x20,0x75,0x00,0x75,0x75,0x30,0x30,0x30,0x74,0x74,0x03,0x74,0x30,0x74,0x00,0x74,0x74,
0x41,0x30,0x30,0x74,0x74,0x30,0x74,0x30,0x74,0x30,0x74,0x74,0x52,0x30,0x30,0x74,0x74,0x30,0x74,0x30,0x74,0x30,0x74,0x74,
0x63,0x30,0x30,0x74,0x74,0x30,0x74,0x30,0x74,0x30,0x74,0x74,0x74,0x30,0x30,0x74,0x74,0x30,0x74,0x30,0x74,0x30,0x74,0x74,
0x74,0x30,0x30,0x74,0x74,0x30,0x74,0x41,0x74,0x30,0x74,0x74,0x74,0x30,0x30,0x74,0x74,0x30,0x74,0x52,0x74,0x30,0x74,0x74,
0x74,0x30,0x30,0x74,0x74,0x30,0x74,0x63,0x74,0x30,0x74,0x74,0x74,0x30,0x30,0x74,0x74,0x30,0x74,0x74,0x74,0x30,0x74,0x74,
0x74,0x30,0x30,0x63,0x74,0x30,0x74,0x74,0x74,0x30,0x74,0x74,0x74,0x30,0x30,0x52,0x74,0x30,0x74,0x74,0x74,0x30,0x74,0x74,
0x74,0x30,0x30,0x41,0x74,0x30,0x74,0x74,0x74,0x30,0x74,0x74,0x74,0x30,0x30,0x30,0x74,0x30,0x74,0x74,0x74,0x30,0x74,0x74,
0x74,0x30,0x30,0x30,0x74,0x30,0x74,0x74,0x74,0x30,0x63,0x74,0x74,0x30,0x30,0x30,0x74,0x30,0x74,0x74,0x74,0x30,0x52,0x74,
0x74,0x30,0x30,0x30,0x74,0x30,0x74,0x74,0x74,0x30,0x41,0x74,0x74,0x30,0x30,0x30,0x74,0x30,0x74,0x74,0x74,0x30,0x30,0x74,
0x75,0x20,0x20,0x20,0x75,0x20,0x75,0x75,0x75,0x20,0x20,0x75,0x76,0x10,0x10,0x10,0x76,0x10,0x76,0x76,0x76,0x10,0x10,0x76,
0x77,0x00,0x00,0x00,0x77,0x00,0x77,0x77,0x77,0x00,0x00,0x77,0x00,0x00,0x00,0x10,0x10,0x10,0x20,0x20,0x20,0x30,0x30,0x30,
0x40,0x40,0x40,0x50,0x50,0x50,0x60,0x60,0x60,0x70,0x70,0x70,0x70,0x70,0x70,0x71,0x71,0x71,0x72,0x72,0x72,0x73,0x73,0x73,
0x74,0x74,0x74,0x75,0x75,0x75,0x76,0x76,0x76,0x77,0x77,0x77,0x07,0x07,0x07,0x06,0x07,0x07,0x05,0x07,0x07,0x04,0x07,0x07,
0x03,0x07,0x07,0x02,0x07,0x07,0x01,0x07,0x07,0x00,0x07,0x07,0x00,0x77,0x77,0x10,0x67,0x67,0x20,0x57,0x57,0x30,0x47,0x47,
0x40,0x37,0x37,0x50,0x27,0x27,0x60,0x17,0x17,0x70,0x07,0x07,0x70,0x07,0x07,0x71,0x06,0x06,0x72,0x05,0x05,0x73,0x04,0x04,
0x74,0x03,0x03,0x75,0x02,0x02,0x76,0x01,0x01,0x77,0x00,0x00,0x07,0x00,0x00,0x07,0x01,0x00,0x07,0x02,0x00,0x07,0x03,0x00,
0x07,0x04,0x00,0x07,0x05,0x00,0x07,0x06,0x00,0x07,0x07,0x00,0x77,0x77,0x00,0x76,0x76,0x01,0x75,0x75,0x02,0x74,0x74,0x03,
0x73,0x73,0x04,0x72,0x72,0x05,0x71,0x71,0x06,0x70,0x70,0x07,0x70,0x70,0x07,0x60,0x60,0x17,0x50,0x50,0x27,0x40,0x40,0x37,
0x30,0x30,0x47,0x20,0x20,0x57,0x10,0x10,0x67,0x00,0x00,0x77,0x00,0x00,0x07,0x00,0x00,0x06,0x00,0x00,0x05,0x00,0x00,0x04,
0x00,0x00,0x03,0x00,0x00,0x02,0x00,0x00,0x01,0x00,0x00,0x00,
};


void BOX_move(uint8_t flashorder)
{
	static int8_t colorR1,colorR2,colorR3,colorR4,colorG1,colorG2,colorG3,colorG4,colorB1,colorB2,colorB3,colorB4;
	int i,j;
	if(++SpeedSum >= 10)																
	{
		SpeedSum = 0;																	
		
		if(0 == NumCount || 23 == NumCount || 63 == NumCount || 87 == NumCount)
		{
			randomColor(&Color_red,&Color_green,&Color_blue);							
			if(0 == NumCount)
			{
				randomColor(&colorR1,&colorG1,&colorB1);								
				randomColor(&colorR2,&colorG2,&colorB2);							
				randomColor(&colorR3,&colorG3,&colorB3);							
				randomColor(&colorR4,&colorG4,&colorB4);								
			}
		}
			
		ClearALL();																
		if(NumCount < 23)
		{
			i = 12*NumCount;
			Box(BoxDat[i+0] & 0x0f,BoxDat[i+1] & 0x0f,BoxDat[i+2] & 0x0f,
				BoxDat[i+0] >> 4,BoxDat[i+1] >> 4,BoxDat[i+2] >> 4,colorR1,colorG1,colorB1,1,0);				
			Box(BoxDat[i+3] & 0x0f,BoxDat[i+4] & 0x0f,BoxDat[i+5] & 0x0f,
				BoxDat[i+3] >> 4,BoxDat[i+4] >> 4,BoxDat[i+5] >> 4,colorR2,colorG2,colorB2,1,0);				
			Box(BoxDat[i+6] & 0x0f,BoxDat[i+7] & 0x0f,BoxDat[i+8] & 0x0f,
				BoxDat[i+6] >> 4,BoxDat[i+7] >> 4,BoxDat[i+8] >> 4,colorR3,colorG3,colorB3,1,0);				
			Box(BoxDat[i+9] & 0x0f,BoxDat[i+10] & 0x0f,BoxDat[i+11] & 0x0f,
				BoxDat[i+9] >> 4,BoxDat[i+10] >> 4,BoxDat[i+11] >> 4,colorR4,colorG4,colorB4,1,0);				
		}
		else if(NumCount < 167)
		{
			if(NumCount < 95)
			{
				i = 207+3*NumCount;							//i = 12*23+3*(NumCount-23);
				j = (NumCount-23)/8;
			}
			else if(NumCount < 167)
			{
				i = 3*NumCount-9;							//i = 12*23+3*(NumCount-95);
				j = (NumCount-95)/8;
			}
			switch(j)
			{
				case 2:
				case 5:
				case 8:
					ColorPoint(BoxDat[i+0],BoxDat[i+1],BoxDat[i+2],Color_red,Color_green,Color_blue,1);						
				break;
				default:
					if(NumCount < 95)
						Box(BoxDat[i+0] & 0x0f,BoxDat[i+1] & 0x0f,BoxDat[i+2] & 0x0f,
							BoxDat[i+0] >> 4,BoxDat[i+1] >> 4,BoxDat[i+2] >> 4,Color_red,Color_green,Color_blue,1,0);	
					else	
						Box(BoxDat[i+0] & 0x0f,BoxDat[i+1] & 0x0f,BoxDat[i+2] & 0x0f,
								BoxDat[i+0] >> 4,BoxDat[i+1] >> 4,BoxDat[i+2] >> 4,Color_red,Color_green,Color_blue,0,0);	
				break;
			}
		}
		
		if(++NumCount >= 167)														
		{
			NumCount = 0;
			pictrue_order = flashorder;											
		}
	}
}

void Line_Cut(uint8_t mode,uint8_t size,int8_t red,int8_t green,int8_t blue)
{
	size %= 3;
	Line(2-size,3-size,mode,2-size,4+size,mode,red,green,blue,1);
	Line(3-size,2-size,mode,4+size,2-size,mode,red,green,blue,1);
	Line(3-size,5+size,mode,4+size,5+size,mode,red,green,blue,1);
	Line(5+size,3-size,mode,5+size,4+size,mode,red,green,blue,1);
}

void Line_Cut1(uint8_t mode,uint8_t size,int8_t red,int8_t green,int8_t blue)
{
	size %= 3;

//	Line(mode,0,size,mode,3,size,red,green,blue,1);
//	Line(mode,2-size,4,mode,2-size,7,red,green,blue,1);
//	Line(mode,4,7-size,mode,7,7-size,red,green,blue,1);
//	Line(mode,5+size,0,mode,5+size,3,red,green,blue,1);

	Line(0,mode,size,3,mode,size,red,green,blue,1);
	Line(2-size,mode,4,2-size,mode,7,red,green,blue,1);
	Line(4,mode,7-size,7,mode,7-size,red,green,blue,1);
	Line(5+size,mode,0,5+size,mode,3,red,green,blue,1);
}


void Line_AddCut(uint8_t flashorder)
{
	char i,j;
	int Number;
	if(++SpeedSum >= 8)																	
	{
		SpeedSum = 0;																
		
		if(0 == NumCount || 264 == NumCount)
		{
			ClearALL();																	
			randomColor(&Color_red,&Color_green,&Color_blue);							
			Color_red++;														
			if(Color_red > 15)
				Color_red = 15;
			Color_green++;
			if(Color_green > 15)
				Color_green = 15;
			Color_blue++;
			if(Color_blue > 15)
				Color_blue = 15;
		}
		
		if((NumCount >= 0 && NumCount < 192) || (NumCount >= 264 && NumCount < 456))
		{
			i = NumCount%8;
			j = NumCount/8;
			if(NumCount < 192)
				Number = NumCount/64;
			else
				Number = (NumCount-72)/64;
//				Number = (NumCount-264)/64+3;
		
			switch(Number)
			{
				case 0:
					Line(0,i,j,7,i,j,Color_red,0,0,1);									
				break;
				case 1:
					Line(0,7-i,15-j,7,7-i,15-j,Color_red,Color_green,0,1);			
				break;
				case 2:
					Line(0,i,j-16,7,i,j-16,Color_red,Color_green,Color_blue,1);		
				break;
				
				case 3:
					Line(i,0,j-33,i,7,j-33,0,0,Color_blue,1);						
				break;
				case 4:
					Line(48-j,0,7-i,48-j,7,7-i,Color_red,0,Color_blue,1);		
				break;
				case 5:
					Line(j-49,0,i,j-49,7,i,Color_red,Color_green,Color_blue,1);		
				break;
			}
		}
		else if((NumCount >= 192 && NumCount < 264) || (NumCount >= 456 && NumCount < 528))
		{
			if(NumCount < 264)
			{
				j = 2-NumCount%3;
				i = NumCount/3;
			}
			else
			{
				j = NumCount/8;
				i = NumCount%8;
			}
		
			switch(NumCount/24)
			{
				case 8:
					Line_Cut(i-64,j,0,Color_green,Color_blue);						
				break;
				case 9:
					Line_Cut(79-i,j,0,Color_green,0);							
				break;
				case 10:
					Line_Cut(i-80,j,0,0,0);											
				break;
				
				case 19:
					Line_Cut1(i,49-j,Color_red,0,Color_blue);							
				break;
				case 20:
					Line_Cut1(7-i,52-j,0,0,Color_blue);								
				break;
				case 21:
					Line_Cut1(i,55-j,0,0,0);										
				break;
			}
		}
		
		if(++NumCount >= 528)													
		{
			NumCount = 0;
			pictrue_order = flashorder;													
		}
	}
}


void Cartoon(void)
{
	switch(pictrue_order)
	{
		case 0:
			flash7(1);																
		break;
		case 1:
			flash9(2);															
		break;
		case 2:
			BOX_move(3);															
		break;
		case 3:
			flash0(4);																
		break;
		case 4:
			flash2(5);																
		break;
		case 5:
			flash4(6);															
		break;
		case 6:
			flash3(7);																	
		break;
		case 7:
			flash5(8);														
		break;
		case 8:
			flash6(9);																
		break;
		case 9:
			flash11(10);																
		break;
		case 10:
			Line_AddCut(11);														
		break;
		case 11:
			flash8(12);																	
		break;
		case 12:
			flash12(13);																
		break;
		case 13:
			flash10(0);																
		break;
	}
//			flash1(0);																	
}


void ReadW25Q64(void)
{
	if(++SpeedSum >= 10)															
	{
		SpeedSum = 0;																	
		SPI_Flash_Read(Read_Buf,4096*NowSection+768*W25QxxAddress+3,768);				
		AxesConvert();																	
		W25QxxAddress++;
		if(W25QxxAddress >= W25QxxFrame)										
		{
			W25QxxAddress = 0;															
			NowSection++;															
			
			SPI_Flash_Read(W25QxxTempAA,4096*NowSection,3);   							
			W25QxxFrame = W25QxxTempAA[2];												
			//W25QxxSection = W25QxxTempAA[0]+(W25QxxTempAA[1] << 8);					
			
			if(NowSection >= W25QxxSection)											
			{
				NowSection = 0;
				SPI_Flash_Read(W25QxxTempAA,0,3);   									
				W25QxxFrame = W25QxxTempAA[2];											
				W25QxxSection = W25QxxTempAA[0]+(W25QxxTempAA[1] << 8);				
			}
		}	
	}			
}


void Snake_scrolling(void)																
{
	if(++SpeedSum >= 40)															
	{
		SpeedSum = 0;																
		Snake_Show(10,1,0,0,10,0);												
		Snake_Move();																
		if(1 == Collide())															
		{
			Snake_Start();																
			Snake_Above();																
		}
		Snake_Feed();																	
	}
}














