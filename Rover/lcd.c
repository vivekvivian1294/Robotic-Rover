

	#include<LPC214X.H>
	#include<stdlib.h>
	#include<string.h>
	#include "lcd.h"
	void lcd_init(void)
		{
				IODIR0 |= port;
				cmd(0x38);
				cmd(0x0E);
				cmd(0x01);
				cmd(0x80);
		}

	void cmd(char c)
	{
	IOPIN0 = c << 15;
	IOCLR0 = RW;
	IOCLR0 = RS;
	IOSET0 = EN;
	delay(25);
	IOCLR0 = EN;
	
	}
	void data(char d)
	{
	  IOPIN0 = d << 15;
	IOCLR0 = RW;
	IOSET0 = RS;
	IOSET0 = EN;
	delay(25); 
	IOCLR0 = EN;
	} 
	void delay(long int count)
	{
	int i,j;
	for(i = 0;i < count;i++)
	for(j = 0;j < 5000;j++);
	}  
	
	void display(long int n)
		{
				if(n)
					{
						display(n/10);
						data((n%10) + 0x30);
					}
		}
	void display_string(char *str)
		{
			while(*str)
			{
				data(*str);
				str++;
			}
		}