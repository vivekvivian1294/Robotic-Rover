#include<lpc214x.h>
#include"led_switch.h"
#include "timer.h"
#include "ADC_0.3_temperature_sensor.h"
#include "gsm.h"
#include "GPS_UART.h"
#include <stdlib.h>
#include "lcd.h"




				


extern int flag;
long int temperature;
char *str;
int main()
{
	IODIR0 |= MOT_ALL;
	IODIR0 |= BUZZ;
	timer_init();
	adc0_init_temperature_sensor();
	uart_init();
	GSM_UART1_init();
	lcd_init();
	
	
	
	
	
	
	
	
	while(1)
	{
		IOSET0 = (MOT_1_IN_1 | MOT_2_IN_2);// MAKING IN1 AND IN4 AS HIGH
		IOCLR0 = (MOT_1_IN_2 | MOT_2_IN_1);// MAKING IN2 AND IN3 AS LOW
		
		if((IOPIN1 & IR2))
		{		
			
      IOCLR0 = (MOT_1_IN_1 | MOT_2_IN_2);// MAKING IN1 AND IN4 AS LOW
			IOSET0 = (MOT_1_IN_2 | MOT_2_IN_1);// MAKING IN2 AND IN3 AS HIGH
			delay(1000);
			
		IOCLR0 = MOT_ALL;
	}

	
		// MAKING IN1 AND IN4 AS LOW
//			IOSET0 = (MOT_1_IN_1 | MOT_2_IN_1);
//			delay(1000);
//		

				
		
		
	
		

	      
		if(flag == 1)
				{
//		       IOSET0 = BUZZ;
//					delay(500);
//		       IOCLR0 = BUZZ;
//					delay(10);
//		
//			
						temperature = adc_read_value_temperature_sensor();
						temperature /= 7;
						str = int_to_string(temperature);
					 gsm_send_msg(str);// sending temperature via GSM
					
					gps();//SENDING COORDINATES AS MESSAGE AS WELL AS DISPLAYED ON LCD
						flag = 0;
							 }   
//		}
//	}
//void delay(int count)
//{
//	int i,j;
//	for(i = 0;i < count;i++)
//	for(j = 0;j < 7000;j++);
//}
}
	}