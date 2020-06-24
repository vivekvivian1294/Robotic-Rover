		
		// NOTE
		//ADD GSM.h file before compiling
		
		
		
		#include<lpc214x.h>
		#include<string.h>
		#include"GSM.h"
		
		char b[20];
		
		void delay(long int count);
		char *AT = "AT\r\n"	;
		char *AT_CMGF = "AT+CMGF=1\r\n";
		char *AT_CMGS="AT+CMGS=\"+919972255570\"\r\n";
		char *BOOKING_SMS = "BOOKING NO = 1234"; //NA
	 char *LEAK_SMS = "GAS LEAKED";//NA
		//char cntl_Z = 0x1A;
		char *OK = "OK";
		char *ERROR = "ERROR";
		char *READY = "RDY";
		
		char temp[15];
		void GSM_UART1_init(void)
			{
				//PINSEL0 = (PINSEL0 & ~(3 << 16)) | (1 << 16);
				//PINSEL0 = (PINSEL0 & ~(3 << 18)) | (1 << 18);
				//PINSEL0 = (PINSEL0 & ~((3 << UART1_TX)|(3 << UART1_RX))) | UART_ALL;	// FOR UART0 AND UART1
				PINSEL0 = (PINSEL0 & ~(0XF << 16)) | UART1_GSM_ALL;	// FOR UART0 AND UART1
				U1LCR = 0X80;
				U1DLL = 97;
				U1LCR = 0X03;
			}
			
/*------------------------------------------------------------------------------------------------
FUNCTION NAME : SENDING MESSAGE THROUGH GSM --> UART1
-------------------------------------------------------------------------------------------------*/

	 void string_uart_trns_gsm(char *str)
		{
		   while(*str)
		   {
		   	while(!(U1LSR & (1 << 5)));
			U1THR = *str;
			str++;
		   }
		}

		void put_char_gsm(char c)
		{
		while(!(U1LSR & (1 << 5)));
		U1THR = c;
		}

		char uart_recv_gsm(void)
		{
		while(!(U1LSR & (1 << 0)));		
		return(U1RBR);
		} 

/*-----------------------------------------------------------------------------------------------------
	FUNCTION DEFINITIONS --->GSM
--------------------------------------------------------------------------------------------------------*/
	

		void gsm_response(char ca,int no)
		{
			char c;	
			int i = 0; 
			do
				{
					i = 0;
					c=uart_recv_gsm();
					temp[i] = c;

				}while((c != ca) && c != 'E');
				do
				{	
					i++;
					c=uart_recv_gsm();
					temp[i] = c;
					
				}while(i != no);

				IOSET0 = (LED_ALL);	//TEST
				delay(3000);
				IOCLR0 = (LED_ALL);	//TE EN
				delay(3000);
		}
/*------------------------------------------------------------------------------------------------------*/
		void gsm_send_msg(char *str)
			{	
				IOSET0 = (LED_ALL);	//TEST
				delay(3000);
				IOCLR0 = (LED_ALL);	//TE EN
				delay(3000);

			do
				{
					
					delay(5000);
					string_uart_trns_gsm(AT);
					gsm_response('O',1);
						temp[2] = '\0';

				}while(strcmp(temp,OK) != 0);
				

				 
					 	delay(5000);
					string_uart_trns_gsm(AT_CMGF);
						

				   
				   	delay(6000);
			
					string_uart_trns_gsm(AT_CMGS);



					delay(5000);
				   	string_uart_trns_gsm(str);
				
					put_char_gsm(0x1a);
					  	delay(3000);

//						IOSET0 = (LED_ALL);	//TEST
//				delay(3000);
//				IOCLR0 = (LED_ALL);	//TE EN
//				delay(3000);
					
			}
/*----------------------------------------------------------------------------------------------
				DELAY
----------------------------------------------------------------------------------------------------*/
			
//			void delay(long int count)
//				{
//					int i,j;
//					for(i=0;i<count;i++)
//					for(j=0;j<5000;j++);
//				}
				
/*-------------------------------------------------------------------------------------
				intiger to string function
---------------------------------------------------------------------------------------*/
			char * int_to_string(long int y)
{
	
		char a[20];
	 int i = 0,j = 0,temp = 0;
		while(y)
		{
			a[i] = ((y %  10)+48);
			i++;
			y /= 10;
		}	
		i--;
		temp = i;
		for(j = 0;j <= temp; i--,j++)
		{
			b[j] = a[i];
		}
		b[j] = '\0';
	
		return b;
}

	
	  
