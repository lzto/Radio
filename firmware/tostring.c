#include "tostring.h"

int itochar(int num,char* strb);

void ToLCDString(char* dest,char* fmt,int number,unsigned char dp)
{
	do
	{
		if(*fmt=='%')
		{
			if(dp==0)
			{
				dest+=itochar(number,dest);
			}else
			{
				dest+=itochar(number/10,dest);//>1
				*dest='.';
				dest++;
				dest+=itochar(number%10,dest);//<1
			}
		}else
		{
			*dest = *fmt;
			dest++;
		}
	}while(*(fmt++)!='\0');
	*dest = '\0';
}

int itochar(int num,char* strb)
{
	unsigned char i = 0;
	unsigned char j = 0;
	char stra[16];
	do
	{
		stra[i++]=num%10+48;
		num=num/10;
	}while(num);
	do
	{
		strb[j] = stra[i-j-1];
	}while((++j)<i);
	return j;
}

