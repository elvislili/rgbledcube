#include "calculate.h"


uint8_t Word_Swap(uint8_t temp)
{
	temp = (temp << 4) | (temp >> 4);
	temp = ((temp << 2) & 0xCC) | ((temp >> 2) & 0x33);
	temp = ((temp << 1) & 0xAA) | ((temp >> 1) & 0x55);
	return temp;
}


//short Sqrt(unsigned long M)   
//{
//    unsigned int N,i;
//    unsigned long tmp,ttp; 
//    if(M == 0)             
//        return 0;
//    N = 0;
//    tmp = (M >> 30);        
//    M <<= 2;
//    if(tmp > 1)            
//    {
//        N++;               
//        tmp -= N;
//    }
//    for(i = 15; i; i--)   
//    {
//        N <<= 1;           
//        tmp <<= 2;
//        tmp += (M >> 30);  
//        ttp = N;
//        ttp = (ttp << 1)+1;
//        M <<= 2;
//        if(tmp >= ttp)    
//        {
//            tmp -= ttp;
//            N++;
//        }       
//    }
//    return N;
//}


void Trans(void)
{
	char x,y,z;
	int16_t i = 0,j = 0;
	for(z = 0; z < 8; z++)
	{
		for(y = 0; y < 8; y++)
		{
			for(x = 6; x; x--)
			{
				i = x*3+(7-y)*24;												
				j = 192*z;														
				rgbled[rgb_order[i+0]+j] = rgbled[rgb_order[i-3+0]+j];				
				rgbled[rgb_order[i+1]+j] = rgbled[rgb_order[i-3+1]+j];			
				rgbled[rgb_order[i+2]+j] = rgbled[rgb_order[i-3+2]+j];			
			}	
		}
	}		
	for(z = 0; z < 8; z++)
	{
		for(y = 0; y < 8; y++)
		{
			i = (7-y)*24;														
			j = 192*z;															
			rgbled[rgb_order[i+0]+j] = 0;										
			rgbled[rgb_order[i+1]+j] = 0;										
			rgbled[rgb_order[i+2]+j] = 0;										
		}
	}		
}


int8_t abss(int8_t dat)
{
	int8_t tpdat = 0;
	tpdat = dat/10;
	dat = dat-tpdat*10;
	if(dat >= 5)
		tpdat++;
	return tpdat;
}


int8_t absolute(int8_t dat)
{
	if(dat <= 0)
		dat = -dat;
	else
		dat = dat;
	return dat;
}


void Max(int8_t *a,int8_t *b)
{
	if((*a) > (*b))
	{
		*a = *a ^ *b;
		*b = *b ^ *a;
		*a = *a ^ *b;	
		//*a = *a + *b - (*b = *a);
	}
}


int8_t maxt(int8_t datA,int8_t datB,int8_t datC)
{
	if(datA <= datB)
		datA = datB;
	if(datA <= datC)
		datA = datC;
	return datA;
}


void ColorPoint(int8_t X,int8_t Y,int8_t Z,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut)
{
	int count_i = 0,count_j = 0;
	X %= 8;													
	Y %= 8;													
	Z %= 8;													
	red   %= 16;										
	green %= 16;											
	blue  %= 16;											
	count_i = X*3+(7-Y)*24;									
	count_j = 192*Z;										
	if(Add_Cut)												
	{
		rgbled[rgb_order[count_i+0]+count_j] = red;			
		rgbled[rgb_order[count_i+1]+count_j] = green;		
		rgbled[rgb_order[count_i+2]+count_j] = blue;		
	}
	else													
	{
		rgbled[rgb_order[count_i+0]+count_j] = 0;			
		rgbled[rgb_order[count_i+1]+count_j] = 0;			
		rgbled[rgb_order[count_i+2]+count_j] = 0;			
	}
}

const int Funnel_dat[128] =
{
0,1,2,3,4,5,6,7,15,23,31,39,47,55,63,62,61,60,59,58,57,56,48,40,32,24,16,8,
73,74,75,76,77,78,86,94,102,110,118,117,116,115,114,113,105,97,89,81,	
146,147,148,149,157,165,173,172,171,170,162,154,	
219,220,228,227,
283,284,292,291,
338,339,340,341,349,357,365,364,363,362,354,346,
393,394,395,396,397,398,406,414,422,430,438,437,436,435,434,433,425,417,409,401,
448,449,450,451,452,453,454,455,463,471,479,487,495,503,511,510,509,508,507,506,505,504,496,488,480,472,464,456
};


void Funnel_Shape(int8_t number,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut)
{
	int8_t x = 0,y = 0,z = 0;
	number %= 128;
	x = Funnel_dat[number]%8;
	y = Funnel_dat[number]%64/8;
	z = Funnel_dat[number]/64;
	ColorPoint(x,y,z,red,green,blue,Add_Cut);
}


void Line(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut)
{
	int8_t mDat = 0,SumX = 0,SumY = 0,SumZ = 0,poorX = 0,poorY = 0,poorZ = 0;
	int8_t i = 0;	
	poorX = x2-x1;
	poorY = y2-y1;
	poorZ = z2-z1;
	mDat  = maxt(absolute(poorX),absolute(poorY),absolute(poorZ));
	SumX  = x1*10;
	SumY  = y1*10;
	SumZ  = z1*10;
	poorX = poorX*10/mDat;
	poorY = poorY*10/mDat;
	poorZ = poorZ*10/mDat;
	for(i = 0; i < mDat; i++)
	{
		ColorPoint(abss(SumX),abss(SumY),abss(SumZ),red,green,blue,Add_Cut);
		SumX = SumX+poorX;
		SumY = SumY+poorY;
		SumZ = SumZ+poorZ;
	}
	ColorPoint(x2,y2,z2,red,green,blue,Add_Cut);
}
const uint8_t roll[28]=
{
0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x71,0x72,0x73,0x74,0x75,0x76,
0x77,0x67,0x57,0x47,0x37,0x27,0x17,0x07,0x06,0x05,0x04,0x03,0x02,0x01
};

void Rotat(int16_t number,int8_t red,int8_t green,int8_t blue)
{
	char x1,y1,x2,y2,j,i;
	number %= 72;
	if(number < 36)
	{
		ClearALL();																		
		i = number;
		for(j = 0; j < 8; j++)
		{
			x1 = roll[(i+j)%28] & 0x0f;
			y1 = roll[(i+j)%28] & 0xf0;
			y1 = y1 >> 4;
			x2 = roll[(i+j+14)%28] & 0x0f;
			y2 = roll[(i+j+14)%28] & 0xf0;
			y2 = y2 >> 4;
			Line(x1,y1,j,x2,y2,j,red,green,blue,1);
		}
	}
	else if(number < 72)
	{
		ClearALL();																		
		i = number-36;
		for(j = 0; j < 8; j++)
		{
			x1 = roll[27-(i+j)%28] & 0x0f;
			y1 = roll[27-(i+j)%28] & 0xf0;
			y1 = y1 >> 4;
			x2 = roll[27-(i+j+14)%28] & 0x0f;
			y2 = roll[27-(i+j+14)%28] & 0xf0;
			y2 = y2 >> 4;
			Line(x1,y1,j,x2,y2,j,red,green,blue,1);
		}
	}
}


void Line_Change(int8_t number,int8_t red,int8_t green,int8_t blue)
{
	int8_t j = 0;
	static int8_t datB[8];
	number %= 32;
	if(0 == number)
		for(j = 7; j < 15; j++)
			datB[j-7] = j;
	if(number < 16)
	{
		for (j = 0; j < 8;j++)
			if((datB[j] < 8) & (datB[j] >= 0))
				Line(0,datB[j],j,7,datB[j],j,red,green,blue,1);
		for(j = 0; j < 8; j++)
			if(((datB[j]+1) < 8) & (datB[j] >= 0))
				Line(0,datB[j]+1,j,7,datB[j]+1,j,red,green,blue,0);
		for(j = 0;j < 8;j++)
			if(datB[j] > 0)
				datB[j]--;
	}
	else if(number < 32)
	{
		if(16 == number)
			for(j = 0; j < 8; j++)
				datB[j] = 1-j;

		for(j = 0; j < 8; j++)
			if((datB[j] < 8) & (datB[j] >= 0))
				Line(0,datB[j],j,7,datB[j],j,red,green,blue,1);

		for(j = 0; j < 8; j++)
			if(((datB[j]-1) < 7) & (datB[j] > 0))
				Line(0,datB[j]-1,j,7,datB[j]-1,j,red,green,blue,0);
		for(j = 0; j < 8; j++)
			if(datB[j] < 7)
				datB[j]++;
	}
}


void Page(int8_t number,int8_t red,int8_t green,int8_t blue,int8_t Add_Cut,int8_t way)
{
	int8_t i = 0;
	number %= 15;
	way %= 8;
	if(number < 8)
	{
		for(i = 0; i < 8; i++)
		{
			switch(way)
			{
				case 0:														
					Line(0,i,0,0,i,7-number,red,green,blue,Add_Cut);
					Line(0,i,7-number,number,i,7,red,green,blue,Add_Cut);
				break;
				case 1:														
					Line(0,i,7,0,i,number,red,green,blue,Add_Cut);
					Line(0,i,number,number,i,0,red,green,blue,Add_Cut);
				break;
				case 2:														
					Line(7,i,0,7,i,7-number,red,green,blue,Add_Cut);
					Line(7,i,7-number,7-number,i,7,red,green,blue,Add_Cut);
				break;
				case 3:														
					Line(7,i,7,7,i,number,red,green,blue,Add_Cut);
					Line(7,i,number,7-number,i,0,red,green,blue,Add_Cut);
				break;
				case 4:														
					Line(i,0,0,i,0,7-number,red,green,blue,Add_Cut);
					Line(i,0,7-number,i,number,7,red,green,blue,Add_Cut);
				break;
				case 5:														
					Line(i,0,7,i,0,number,red,green,blue,Add_Cut);
					Line(i,0,number,i,number,0,red,green,blue,Add_Cut);
				break;
				case 6:														
					Line(i,7,0,i,7,7-number,red,green,blue,Add_Cut);
					Line(i,7,7-number,i,7-number,7,red,green,blue,Add_Cut);
				break;
				case 7:														
					Line(i,7,7,i,7,number,red,green,blue,Add_Cut);
					Line(i,7,number,i,7-number,0,red,green,blue,Add_Cut);
				break;
			}
		}
	}
	else if(number < 15)
	{
		for(i = 0; i < 8; i++)
		{
			switch(way)
			{
				case 0:														
					Line(0,i,0,number-7,i,0,red,green,blue,Add_Cut);
					Line(number-7,i,0,7,i,14-number,red,green,blue,Add_Cut);
				break;
				case 1:														
					Line(0,i,7,number-7,i,7,red,green,blue,Add_Cut);
					Line(number-7,i,7,7,i,number-7,red,green,blue,Add_Cut);
				break;
				case 2:														
					Line(7,i,0,14-number,i,0,red,green,blue,Add_Cut);
					Line(14-number,i,0,0,i,14-number,red,green,blue,Add_Cut);
				break;
				case 3:														
					Line(7,i,7,14-number,i,7,red,green,blue,Add_Cut);
					Line(14-number,i,7,0,i,number-7,red,green,blue,Add_Cut);
				break;
				case 4:														
					Line(i,0,0,i,number-7,0,red,green,blue,Add_Cut);
					Line(i,number-7,0,i,7,14-number,red,green,blue,Add_Cut);
				break;
				case 5:														
					Line(i,0,7,i,number-7,7,red,green,blue,Add_Cut);
					Line(i,number-7,7,i,7,number-7,red,green,blue,Add_Cut);
				break;
				case 6:														
					Line(i,7,0,i,14-number,0,red,green,blue,Add_Cut);
					Line(i,14-number,0,i,0,14-number,red,green,blue,Add_Cut);
				break;
				case 7:														
					Line(i,7,7,i,14-number,7,red,green,blue,Add_Cut);
					Line(i,14-number,7,i,0,number-7,red,green,blue,Add_Cut);
				break;
			}
		}
//		for(i = 0; i < 8; i++)
//		{
//			Line(0,i,0,14-number,i,14-number,red,green,blue,Add_Cut);
//			Line(14-number,i,14-number,7,i,14-number,red,green,blue,Add_Cut);
//		}
	}
}

int8_t Get_Point[3];


void GetPoint(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,int8_t Number)
{
	int8_t mDat = 0,SumX = 0,SumY = 0,SumZ = 0,poorX = 0,poorY = 0,poorZ = 0;
	poorX = x2-x1;
	poorY = y2-y1;
	poorZ = z2-z1;
	mDat  = maxt(absolute(poorX),absolute(poorY),absolute(poorZ));
	SumX  = x1*10;
	SumY  = y1*10;
	SumZ  = z1*10;
	poorX = poorX*10/mDat;
	poorY = poorY*10/mDat;
	poorZ = poorZ*10/mDat;
	Get_Point[0] = SumX+poorX*Number;
	Get_Point[1] = SumY+poorY*Number;
	Get_Point[2] = SumZ+poorZ*Number;
}


void PlaneXY(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
			 int8_t red,int8_t green,int8_t blue,int8_t Add_Cut,int8_t fill)
{
	int8_t i = 0;
	Max(&z1,&z2);
	if(fill)
	{
		for(i = z1; i <= z2; i++)
			Line(x1,y1,i,x2,y2,i,red,green,blue,Add_Cut);
	} 
	else
	{
		Line(x1,y1,z1,x2,y2,z1,red,green,blue,Add_Cut);
		Line(x1,y1,z2,x2,y2,z2,red,green,blue,Add_Cut);
		Line(x2,y2,z1,x2,y2,z2,red,green,blue,Add_Cut);
		Line(x1,y1,z1,x1,y1,z2,red,green,blue,Add_Cut);
	}
}


void Change_PlaneXY(int8_t number,int8_t red,int8_t green,int8_t blue)
{
	int8_t j = 0;
	static int8_t datC[4];
	number %= 36;
	
	if(number < 8)
	{
		if(0 == number)
			for(j = 7; j < 11; j++)
				datC[j-7] = j;
		for(j = 0; j < 4; j++)
		{
			if(datC[j] < 8)
				PlaneXY(j,datC[j],j,7-j,datC[j],7-j,red,green,blue,1,0);
			if(datC[j] < 7)
				PlaneXY(j,datC[j]+1,j,7-j,datC[j]+1,7-j,red,green,blue,0,0);
		}
		for(j = 0; j < 4; j++)
			if(datC[j] > 3)
				datC[j]--;
	}
	else if(number < 11)
	{
		if(8 == number)
			for(j = 0; j < 4; j++)
				datC[j] = 5-j;

		for(j = 1; j < 4; j++)
		{
			if(datC[j] < 4)
				PlaneXY(j,datC[j],j,7-j,datC[j],7-j,red,green,blue,1,0);
			if(datC[j] < 3)
				PlaneXY(j,datC[j]+1,j,7-j,datC[j]+1,7-j,red,green,blue,0,0);
		}
		for(j = 0;j < 4; j++)
			if(datC[j] > 0)
				datC[j]--;
	}
	else if(number < 14)
	{
		if(11 == number)
			for(j = 1;j < 4; j++)
				datC[j] = 4-j;

		for(j = 1; j < 4; j++)
		{
			if(datC[j] >= 0)
				PlaneXY(j,datC[j],j,7-j,datC[j],7-j,red,green,blue,1,0);
			if(datC[j] > 0)
				PlaneXY(j,datC[j]-1,j,7-j,datC[j]-1,7-j,red,green,blue,0,0);
		}
		for(j = 1; j < 4; j++)
			if(datC[j] < 3)
				datC[j]++;
	}
	else if(number < 17)
	{
		if(14 == number)
			for(j = 0; j < 4; j++)
				datC[j] = j+1;

		for(j = 1;j < 4; j++)
		{
			if(datC[j] > 3)
				PlaneXY(j,datC[j],j,7-j,datC[j],7-j,red,green,blue,1,0);
			if(datC[j] > 3)
				PlaneXY(j,datC[j]-1,j,7-j,datC[j]-1,7-j,red,green,blue,0,0);
		}
		for(j = 0; j < 4; j++)
			datC[j]++;
	}
	else if(number < 20)
	{
		if(17 == number)
			for(j = 3; j < 6; j++)
				datC[j-2] = j;

		for(j = 1; j < 4; j++)
		{
			PlaneXY(j,datC[j],j,7-j,datC[j],7-j,red,green,blue,1,0);
			PlaneXY(j,datC[j]+1,j,7-j,datC[j]+1,7-j,red,green,blue,0,0);
		}
		for(j = 0; j < 4; j++)
			if(datC[j] > 3)
				datC[j]--;
	}
	else if(number < 23)
	{
		if(20 == number)
			for(j = 0; j < 4; j++)
				datC[j] = 5-j;

		for(j = 1; j < 4; j++)
		{
			if(datC[j] < 4)
				PlaneXY(j,datC[j],j,7-j,datC[j],7-j,red,green,blue,1,0);
			if(datC[j] < 3)
				PlaneXY(j,datC[j]+1,j,7-j,datC[j]+1,7-j,red,green,blue,0,0);
		}
		for(j = 0; j < 4; j++)
			if(datC[j] > 0)
				datC[j]--;
	}
	else if(number < 26)
	{
		if(23 == number)
		{
			for(j = 0; j < 4; j++)
				datC[j] = 3-j;
			datC[0]=2;
		}
		for(j = 0; j < 3; j++)
		{
			if(datC[j] >= 0)
				PlaneXY(j,datC[j],j,7-j,datC[j],7-j,red,green,blue,1,0);
			if(datC[j] >= 0)
				PlaneXY(j,datC[j]+1,j,7-j,datC[j]+1,7-j,red,green,blue,0,0);
		}
		for(j = 0; j < 4; j++)
			if(j < 5-(25-number))
				datC[j]--;
	}
	else if(number < 36)
	{
		if(26 == number)
			for(j = 0; j < 4; j++)
				datC[j] = j-2;

		for(j = 0; j < 4; j++)
		{
			if(datC[j] >= 0)
				PlaneXY(j,datC[j],j,7-j,datC[j],7-j,red,green,blue,1,0);
			if(datC[j] >= 0)
				PlaneXY(j,datC[j]-1,j,7-j,datC[j]-1,7-j,red,green,blue,0,0);
		}
		for(j = 0; j < 4; j++)
			if(datC[j] < 7)
				datC[j]++;
	}
}


void PlaneYZ(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
			 int8_t red,int8_t green,int8_t blue,int8_t Add_Cut,int8_t fill)
{
	int8_t i = 0;
	Max(&x1,&x2);
	if(fill)	
	{
		for(i = x1; i <= x2; i++)
			Line(i,y1,z1,i,y2,z2,red,green,blue,Add_Cut);
	}
	else
	{
		Line(x1,y1,z1,x1,y2,z2,red,green,blue,Add_Cut);
		Line(x2,y1,z1,x2,y2,z2,red,green,blue,Add_Cut);
		Line(x1,y2,z2,x2,y2,z2,red,green,blue,Add_Cut);
		Line(x1,y1,z1,x2,y1,z1,red,green,blue,Add_Cut);
	}
}


void PlaneZX(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
			 int8_t red,int8_t green,int8_t blue,int8_t Add_Cut,int8_t fill)
{
	int8_t i = 0;
	Max(&y1,&y2);

	if(fill)	
	{
		for(i = y1; i <= y2; i++)
			Line(x1,i,z1,x2,i,z2,red,green,blue,Add_Cut);
	}
	else
	{
		Line(x1,y1,z1,x2,y1,z2,red,green,blue,Add_Cut);		
		Line(x1,y2,z1,x2,y2,z2,red,green,blue,Add_Cut);		
		Line(x2,y1,z2,x2,y2,z2,red,green,blue,Add_Cut);		
		Line(x1,y1,z1,x1,y2,z1,red,green,blue,Add_Cut);
	}
}


void Box(int8_t x1,int8_t y1,int8_t z1,int8_t x2,int8_t y2,int8_t z2,
		 int8_t red,int8_t green,int8_t blue,int8_t fill,int8_t Up_Down)
{
	int8_t i = 0;
	int8_t number = absolute(z2-z1);
	if(fill)
	{
		for(i = 0; i <= number; i++)
		{
			if(Up_Down)
				PlaneXY(x1+i,y1,7-z1,x1+i,y2,7-z2,red,green,blue,1,1);
			else
				PlaneXY(x1+i,y1,z1,x1+i,y2,z2,red,green,blue,1,1);
		}
	}
	else
	{
		if(Up_Down)
		{
			PlaneXY(x1,y1,7-z1,x1,y2,7-z2,red,green,blue,1,0);
			PlaneXY(x2,y1,7-z1,x2,y2,7-z2,red,green,blue,1,0);
			Line(x1,y1,7-z1,x2,y1,7-z1,red,green,blue,1);
			Line(x1,y2,7-z1,x2,y2,7-z1,red,green,blue,1);
			Line(x1,y1,7-z2,x2,y1,7-z2,red,green,blue,1);
			Line(x1,y2,7-z2,x2,y2,7-z2,red,green,blue,1);
		}
		else
		{
			PlaneXY(x1,y1,z1,x1,y2,z2,red,green,blue,1,0);
			PlaneXY(x2,y1,z1,x2,y2,z2,red,green,blue,1,0);
			Line(x1,y1,z1,x2,y1,z1,red,green,blue,1);
			Line(x1,y2,z1,x2,y2,z1,red,green,blue,1);
			Line(x1,y1,z2,x2,y1,z2,red,green,blue,1);
			Line(x1,y2,z2,x2,y2,z2,red,green,blue,1);
		}
	}
}

const uint8_t box1[24] =
{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x16,0x26,0x36,0x46,0x56,0x66,0x65,0x64,0x63,0x62,0x61,0x60,0x50,0x40,0x30,0x20,0x10};


void Box_Change(int8_t number,int8_t red,int8_t green,int8_t blue,int8_t Up_Down)
{
	int8_t i = 0,x = 0,y = 0,t = 0;
	static int8_t datA[4];
	number %= 108;
	ClearALL();																			
	if(number < 6)
	{
		Box(0,6,6,1,7,7,red,green,blue,1,!Up_Down);
		Box(number,6,6-number,number+1,7,7-number,red,green,blue,1,!Up_Down);
		Box(number,6,6,number+1,7,7,red,green,blue,1,!Up_Down);
		Box(0,6,6-number,1,7,7-number,red,green,blue,1,!Up_Down);
		Box(0,6-number,6,1,7-number,7,red,green,blue,1,!Up_Down);
		Box(number,6-number,6-number,number+1,7-number,7-number,red,green,blue,1,!Up_Down);
		Box(number,6-number,6,number+1,7-number,7,red,green,blue,1,!Up_Down);
		Box(0,6-number,6-number,1,7-number,7-number,red,green,blue,1,!Up_Down);
	}
	else if(number < 30)
	{
		if(6 == number)
			for(i = 0; i < 4;i++)
				datA[i] = 6*i;
		
		for(i = 0; i < 4;i++)
		{
			t = datA[i] % 24;
			x = box1[t] >> 4;
			y = box1[t] & 0x0f;
			Box(x,y,0,x+1,y+1,1,red,green,blue,1,Up_Down);
			Box(x,y,6,x+1,y+1,7,red,green,blue,1,Up_Down);
		}
		for(i = 0; i < 4;i++)
			datA[i]++;
	}
	else if(number < 54)
	{
		for(i = 0; i < 4;i++)
		{
			t = datA[i] % 24;
			x = box1[t] >> 4;
			y = box1[t] & 0x0f;
			Box(x,y,0,x+1,y+1,1,red,green,blue,1,Up_Down);
			Box(x,y,6,x+1,y+1,7,red,green,blue,1,Up_Down);
		}
		for(i = 0; i < 4;i++)
			datA[i]--;
	}
	else if(number < 78)
	{
		for(i = 0; i < 4;i++)
		{
			t = datA[i] % 24;
			x = box1[t] >> 4;
			y = box1[t] & 0x0f;
			Box(x,0,y,x+1,1,y+1,red,green,blue,1,Up_Down);
			Box(x,6,y,x+1,7,y+1,red,green,blue,1,Up_Down);
		}
		for(i = 0; i < 4;i++)
			datA[i]++;
	}
	else if(number < 102)
	{
		for(i = 0; i < 4;i++)
		{
			t = datA[i] % 24;
			x = box1[t] >> 4;
			y = box1[t] & 0x0f;
			Box(x,0,y,x+1,1,y+1,red,green,blue,1,Up_Down);
			Box(x,6,y,x+1,7,y+1,red,green,blue,1,Up_Down);
		}
		for(i = 0; i < 4;i++)
			datA[i]--;
	}
	else if(number < 108)
	{
		number = 108-number;
		Box(0,6,6,1,7,7,red,green,blue,1,Up_Down);
		Box(number,6,6-number,number+1,7,7-number,red,green,blue,1,Up_Down);
		Box(number,6,6,number+1,7,7,red,green,blue,1,Up_Down);
		Box(0,6,6-number,1,7,7-number,red,green,blue,1,Up_Down);
		Box(0,6-number,6,1,7-number,7,red,green,blue,1,Up_Down);
		Box(number,6-number,6-number,number+1,7-number,7-number,red,green,blue,1,Up_Down);
		Box(number,6-number,6,number+1,7-number,7,red,green,blue,1,Up_Down);
		Box(0,6-number,6-number,1,7-number,7-number,red,green,blue,1,Up_Down);
	}
}

const uint8_t DNASum[28]=
{
0x00,0x20,0x40,0x60,0x80,0xa0,0xc0,0xe0,0xe4,0xe8,0xec,0xf0,0xf4,0xf8,
0xfc,0xdc,0xbc,0x9c,0x7c,0x5c,0x3c,0x1c,0x18,0x14,0x10,0x0c,0x08,0x04
};


void DNA_Change(int16_t number,int8_t red,int8_t green,int8_t blue)
{
	int8_t i = 0;
	int8_t x = 0,y = 0,x1 = 0,y1 = 0,t = 0,j = 0;
	static int8_t datD[8];
	number %= 255;
	if(0 == number)
		for(i = 0; i < 8; i++)
               datD[i] = 14;

	if(number < 85)
	{
		ClearALL();																		  
		for(j = 0; j < 8; j++)
		{
			t  = datD[j] % 28;
			x  = DNASum[t] >> 5;
			y  = (DNASum[t] >> 2) & 0x07;
			
			t  = (datD[j]-14) % 28;
			x1 = DNASum[t] >> 5;
			y1 = (DNASum[t] >> 2) & 0x07;
			Line(x,y,j,x1,y1,j,red,green,blue,1);
		}
		for(j = 0; j < 8; j++)
			if((number > j)&(j > number-71))
				datD[j]++;
	} 
	else if(number < 170)
	{
		ClearALL();																		             
		for(j = 0;j < 8; j++)
		{
			t  = datD[j] % 28;
			x  = DNASum[t] >> 5;
			y  = (DNASum[t] >> 2) & 0x07;
			t  = (datD[j]-14) % 28;
			x1 = DNASum[t] >> 5;
			y1 = (DNASum[t] >> 2) & 0x07;
			Line(x,y,j,x1,y1,j,red,green,blue,1);
		}
		for(j = 0; j < 8; j++)
			if(((number-85) > j) & (j > (number-85)-71))
				datD[j]--;
	} 
	else if(number < 199)
	{
		ClearALL();																		
		t  = datD[0] % 28;
		x  = DNASum[t] >> 5;
		y  = (DNASum[t] >> 2) & 0x07;
		t  = (datD[0]-14) % 28;
		x1 = DNASum[t] >> 5;
		y1 = (DNASum[t] >> 2) & 0x07;
		PlaneXY(x,y,0,x1,y1,7,red,green,blue,1,0);
		PlaneXY(x,y,1,x1,y1,6,red,green,blue,1,0);
		datD[0]++; 
	} 
	else if(number < 215)
	{
		ClearALL();																		
		t  = datD[0] % 28;
		x  = DNASum[t] >> 5;
		y  = (DNASum[t] >> 2) & 0x07;
		t  = (datD[0]-14) % 28;
		x1 = DNASum[t] >> 5;
		y1 = (DNASum[t] >> 2 ) & 0x07;
		PlaneXY(x,y,0,x1,y1,7,red,green,blue,1,1);
		datD[0]--; 
	} 
	else if(number < 223)
	{
		i = number-215;
		Line(i,i,0,0,0,i,red,green,blue,0);
	} 
	else if(number < 229)
	{
		i = number-222;
		Line(i,i,7,7,7,i,red,green,blue,0);
	} 
	else if(number < 236)
	{
		ClearALL();																		
		i = number-228;
		Box(7,7,7,7-i,7-i,7-i,red,green,blue,0,0);
	} 
	else if(number < 242)
	{
		ClearALL();																		
		i = number-235;
		Box(0,0,0,7-i,7-i,7-i,red,green,blue,0,0);
	} 
	else if(number < 249)
	{
		ClearALL();																		
		i = number-241;
		Box(0,0,0,i,i,i,red,green,blue,0,0);
	} 
	else if(number < 255)
	{
		ClearALL();																		
		i = number-248;
		Box(7,0,0,i,7-i,7-i,red,green,blue,0,0);
	} 
}

const uint8_t waveline[13]={0,1,2,0x23,5,6,7,6,5,0x23,2,1,0};
const uint8_t wave[24]=
{
0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x16,0x26,0x36,0x46,0x56,
0x66,0x65,0x64,0x63,0x62,0x61,0x60,0x50,0x40,0x30,0x20,0x10
};
const uint8_t place[63]=
{
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,0,2,4,6,8,10,12,14,
16,18,20,22,0,3,6,9,12,15,18,21,0,4,8,12,16,20,0,5,10,15,20,0,6,12,18,0,7,14,21
};
	

void Waveform(int16_t number,int8_t red,int8_t green,int8_t blue)
{
	char t,x,y;

	number %= 204;
	if(number < 78)
	{
		number %= 13;
		if(waveline[number] >> 4)
		{
			t = waveline[number] & 0x0f;
			Line(0,0,t+1,0,7,t+1,red,green,blue,1);
		}
		else 
			t = waveline[number];
		Line(0,0,t,0,7,t,red,green,blue,1);
		Trans();
	}
	else if(number < 141)
	{
		t = number-78;
		x = wave[place[t]] >> 4;
		y = wave[place[t]] & 0x0f;
		PlaneXY(0,x,y,0,x+1,y+1,red,green,blue,1,1);
		Trans();
	}
	else if(number < 204)
	{
		t = number-141;
		x = wave[place[t]] >> 4;
		y = wave[place[t]] & 0x0f;
		ColorPoint(0,x,y,red,green,blue,1);
		Trans();
	}
};
const uint8_t Dat_print[]={					
0X00,0X00,0X81,0XFF,0XFF,0X81,0X00,0X00,	//I
0X1C,0X3E,0X7E,0XFC,0XFC,0X7E,0X3E,0X1C,	//heart
0X3F,0X7F,0X80,0X80,0X80,0X80,0X7F,0X3F,	//U
0X3C,0X42,0X14,0XA1,0XA1,0X14,0X42,0X3C,	//smile face
0X00,0X73,0XE9,0X89,0X89,0X8F,0X4F,0X00,	//5
0X00,0XC6,0X86,0X89,0X99,0XB1,0XE7,0XC6,	//2
0X3C,0X7E,0X81,0X81,0X81,0X7E,0X3C,0X00,	//0
0X00,0X00,0X3C,0X3C,0X3C,0X3C,0X00,0X00,	//square
0X20,0X30,0X38,0X3C,0X3C,0X38,0X30,0X20,	//triangle
0X08,0X14,0X22,0X77,0X14,0X14,0X14,0X1C,	//arrow
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//all on
0X00,0X00,0X80,0XFF,0XFF,0X82,0X00,0X00,	//1
0X00,0X76,0XFF,0X89,0X89,0X81,0XC2,0X00,	//2
0X00,0X00,0X80,0XFF,0XFF,0X82,0X00,0X00,	//3
0X20,0XA0,0XFF,0XFF,0XA3,0X22,0X3C,0X30		//4
};


void Face(const uint8_t *Data,int8_t row,int8_t red,int8_t green,int8_t blue,int8_t direction)				
{
	uint8_t i = 0,k = 0;
	int j = 0;
	red   %= 16;																		
	green %= 16;																		
	blue  %= 16;																		
	row %= 8;
	for(i = 0; i < 64; i++)
	{
		if(direction)
		{
//			k = (7-i%8)*24+i/8*3;
			k = (7-(i & 0x07))*24+(i >> 3)*3;
			j = (7-row)*192;
		}
		else
		{
//			k = i/8*3+(7-row)*24;
//			j = (7-i%8)*192;
			k = (7-row)*24+(i >> 3)*3;
			j = (7-(i & 0x07))*192;
		}
		if(Data[i/8] & (0x80 >> (i%8)))
		{
			rgbled[rgb_order[k+0]+j] = red;													
			rgbled[rgb_order[k+1]+j] = green;											
			rgbled[rgb_order[k+2]+j] = blue;											
		}
		else
		{
			rgbled[rgb_order[k+0]+j] = 0;												
			rgbled[rgb_order[k+1]+j] = 0;												
			rgbled[rgb_order[k+2]+j] = 0;												
		}
	}
}

void Frame(const uint8_t *Data,int8_t red,int8_t green,int8_t blue,int8_t direction)				
{
	uint8_t i = 0;
	for(i = 0; i < 8; i++)
		Face(Data+i*8,i,red,green,blue,direction);
}


void print(int number,const uint8_t *Data,int8_t red,int8_t green,int8_t blue,char m,int8_t direction)
{
	uint8_t p;
	char i,j,k;
	static uint8_t Dat_temp[64];
	number %= 77;
	if(0 == number)
		for(i = 0; i < 8; i++)
			Dat_temp[7*8+i] = 0xff;

	if(number < 64)
	{
		i = number/8;									
		j = number%8;									

		p = Data[i] & (0x01 << j);
		if(p)
		{
			for(k = 6; k; k--)
			{
				if(m == 1 && k == 6)
				{
				}
				else
					Dat_temp[(k+1)*8+7-i] &= (p ^ 0xff);
				Dat_temp[k*8+7-i] |= (0x01 << j);
				Frame(Dat_temp,red,green,blue,direction);
			}
			Dat_temp[1*8+7-i] = 0;
			Dat_temp[7-i] |= p;
			Frame(Dat_temp,red,green,blue,direction);
		}
//		Dat_temp[7-i]|=p;
	}
	else if(number < 68)
		Frame(Dat_temp,red,green,blue,direction);
	else if(68 == number)
		Dat_temp[0] = 0;
	else if(number < 76)
	{
		for(i = 7; i; i--)
			Dat_temp[i] = Dat_temp[i-1];
		Frame(Dat_temp,red,green,blue,direction);
	}
	else if(76 == number)
	{
		for(i = 0; i < 8; i++)
			Dat_temp[i] = 0;
	}		
}

const uint8_t MathSum[]={										
0x00,0x40,0x40,0x40,0x40,0x40,0x7E,0x00,		
0x00,0x7E,0x40,0x7E,0x40,0x40,0x7E,0x00,		
0x00,0x7C,0x46,0x42,0x42,0x46,0x7C,0x00,		
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,		
0x00,0x3C,0x62,0x40,0x40,0x61,0x3E,0x00,		
0x00,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,		
0x00,0x7C,0x42,0x7C,0x42,0x41,0x7E,0x00,		
0x00,0x7E,0x40,0x7E,0x40,0x40,0x7E,0x00,		
0x3C,0x18,0x18,0x18,0x18,0x18,0x18,0x3C,		
0x00,0x24,0x66,0xFF,0xFF,0x7E,0x3C,0x18,		
0x00,0xC3,0xC3,0xC3,0xC3,0xC3,0xFF,0x7E,		
0x1C,0x22,0x22,0x3E,0x02,0x02,0x22,0x1C,		
0x1C,0x22,0x22,0x3E,0x22,0x22,0x22,0x1C,		
0x3C,0x02,0x04,0x08,0x08,0x08,0x08,0x08,		
0x1C,0x20,0x20,0x3C,0x22,0x22,0x26,0x1C,		
0x3E,0x20,0x20,0x3C,0x02,0x02,0x26,0x1C,		
0x08,0x18,0x28,0x48,0x88,0xFE,0x0C,0x08,		
0x1C,0x22,0x02,0x1C,0x1C,0x02,0x22,0x1C,		
0x3C,0x7E,0x46,0x0C,0x18,0x30,0x60,0x7E,		
0x18,0x38,0x18,0x18,0x18,0x18,0x7E,0xFF,		
};



void Move(uint8_t *Data_Move,uint8_t d,uint8_t b,uint8_t c,uint8_t e)
{
	char i;
	for(i = 0; i < 8; i++)
	{
		Data_Move[i] = e & 0x01;
		e >>= 1;
	}
	Data_Move[7] |= (c << 1);
	Data_Move[6] |= (c & 0x80);
	for(i = 0; i < 6; i++)
		Data_Move[5-i] |= ((b << (7-i)) & 0x80);
	d = Word_Swap(d);
	Data_Move[0] |= ((d >> 1) & 0x7e);
}


void Mov_Show(int number,const uint8_t *Data,int8_t red,int8_t green,int8_t blue,int8_t direction)
{
	char i,j,k;
	static uint8_t XXX[64],temp0[8],temp1[8],temp2[8],temp3[8],temp[8];
	
	number %= 152;
	
	if(0 == number)
		for(i = 0; i < 8; i++)
			temp0[i] = temp1[i] = temp2[i] = temp3[i] = 0;
	
	if(0 == number%8)														
	{
		j = number/8;									
		for(k = 0; k < 8; k++)												
			temp[7-k] = Data[j*8+k];
	}

	for(i = 0; i < 8; i++)													
	{
		temp0[i] = (temp0[i] << 1) | (temp1[i] >> 7);
		temp1[i] = (temp1[i] << 1) | (temp2[i] >> 7);
		temp2[i] = (temp2[i] << 1) | (temp3[i] >> 7);
		temp3[i] = (temp3[i] << 1) | (temp[i] >> 7);
		temp[i] <<= 1;
		Move(XXX+i*8,temp0[i],temp1[i],temp2[i],temp3[i]);
	}
	Frame(XXX,red,green,blue,direction);
}








