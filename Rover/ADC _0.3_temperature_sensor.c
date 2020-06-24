
				
				
				#include<lpc214x.h>
				#include "ADC_0.3_temperature_sensor.h"
				
/*------------------------------------------------------------------------------------------------
FUNCTION NAME : MQ6 SENSOR --> ADC0 INITIALISATION
-------------------------------------------------------------------------------------------------*/		
				void adc0_init_temperature_sensor(void)
					{
						PINSEL1 |= (PINSEL1 & ~(0X3 < 28)) | (1 << 28);// FOR ADC0 CHANNEL 3 P0.30
						AD0CR = adc0_init_macro;
					} 
/*------------------------------------------------------------------------------------------------
FUNCTION NAME : READ DATA FROM MQ6 SENSOR --> ADC
				
-------------------------------------------------------------------------------------------------*/
			
			   long int adc_read_value_temperature_sensor(void)
			  	 {
				 		long int done = 1;
			   			int sample = 8;
						long int result = 0;
						long int sum = 0;
			   			while(sample)
						{
							
							 AD0CR |= START;//starting the adc conversion
							while(!(AD0GDR & (done << 31)));
							 result = (AD0GDR >> 6) & 0X3FF;
							 sum += result; // finding sum to find average	
							 sample--;
						 }
						  sum = (sum >> 3);	//rght shifting 3 is same as dividing by 8
							  return(sum);			
				 }
