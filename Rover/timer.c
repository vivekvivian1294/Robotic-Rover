		#include<lpc214x.h>
	#include<string.h>
	#include "led_switch.h"

	#include "timer.h"
	
	extern int minute;
		
		 int flag;
		
		
					void timer_init(void)
						{
							 VICVectAddr3 = (long)timer_isr;
							  EXTPOLAR |= 0x00;
							  EXTMODE = 0X02;
							  VICIntSelect &= ~(1 << 4);
							  VICVectCntl3 = (1 << 5) | 4;
							  T0IR = 0X01;
							  VICVectAddr = 0;
							  VICIntEnable |= (1 << 4);
							T0PR = 0;
							T0PC = 0;
							T0MR0 = 20000000;
							T0PR = 14;
							T0MCR = 0X3;
							T0TCR = 0X01;
						}
	  
					  
					  void timer_isr(void)__irq
						{
								IOCLR0 = (MOT_1_IN_1 | MOT_1_IN_2 | MOT_2_IN_1 | MOT_2_IN_2);
								flag = 1;
								 T0IR = 0X01;
								 VICVectAddr = 0;
						}