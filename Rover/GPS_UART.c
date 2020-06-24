/*GPS WORKING CODE FOR FORMAT "$GPRMC,1000403.999,V,2400.0000,N,12100.0000"*/


		#include<lpc214x.h>
		#include<string.h>
		#include "GPS_UART.h"
		#include "lcd.h"
		#include "GSM.h"
		char gps_rec_char;
				int neglect_char = 12;
				int lat = 0;
				int lon = 0;
				int i = 0;
				char lat_lon[50];
				int p=0,q =0;
				char lati[20],logtd[20];
		void uart_init(void)
		{
		PINSEL0 = ((PINSEL0 & ~0XF)|((1 << 0)|(1 << 2)));
		U0LCR = 0X80;
		U0DLL = 97;
		U0LCR = 0X03;
		}
		void string_uart_trns(char *str)
		{
		   while(*str)
		   {
		   	while(!(U0LSR & (1 << 5)));
			U0THR = *str;
			str++;
			//delay(1000);
		   }
		}
		void put_char(char c)
		{
		while(!(U0LSR & (1 << 5)));
		U0THR = c;
		}
		char uart_recv(void)
		{
				char c;
				while(!(U0LSR & (1 << 0)));
				c = U0RBR;
				return c;
				
		} 
//		void delay(long int n)
//			{
//					int p,q;
//					for(p = 0;p < n;p++)
//					for(q = 0;q < 5000;q++);	
//			}
			
			
			void gps(void)
				{
						
						while(1)
					{
						gps_rec_char = uart_recv();
						if(gps_rec_char == '$')
								{
								//	IOSET0 = (1 << 4);
								//	data(gps_rec_char);
									gps_rec_char = uart_recv();
									if(gps_rec_char == 'G')
										{
												//put_char(gps_rec_char);
											//data(gps_rec_char);
											//cmd(0x01);
											gps_rec_char = uart_recv();
											if(gps_rec_char == 'P')
												{
													//put_char(gps_rec_char);
													//data(gps_rec_char);
													gps_rec_char = uart_recv();
													if(gps_rec_char == 'R')
														{
															//put_char(gps_rec_char);
														//	data(gps_rec_char);
															gps_rec_char = uart_recv();
															if(gps_rec_char == 'M')
																{
																	//put_char(gps_rec_char);
														//		data(gps_rec_char);
																	gps_rec_char = uart_recv();
																	if(gps_rec_char == 'C')
																		{
                                //       data(gps_rec_char);
																			//put_char(gps_rec_char);
																	//		cmd(0xc0);
																			
																			
																			while(neglect_char)
																				{
																					gps_rec_char = uart_recv();
																				//	data(gps_rec_char);
																					//put_char(gps_rec_char);
																					neglect_char--;
																				}
																				
																			//	cmd(0x01);
																					gps_rec_char = uart_recv();
																					if((gps_rec_char == 'A') || (gps_rec_char == 'V'))
																						{
																							//put_char(gps_rec_char);
																						//	data(gps_rec_char);
																							
																							gps_rec_char = uart_recv();
																						//	data(gps_rec_char);
																							//put_char(gps_rec_char);
																							
																							while(lat < 9)
																								{
																									
																									gps_rec_char = uart_recv();
																								//	data(gps_rec_char);
																									//put_char(gps_rec_char);
																									lat_lon[i] = gps_rec_char;
																									lat++;
																									i++;
																									
																								}
																								//cmd(0x01);
																									gps_rec_char = uart_recv();
																								  //data(gps_rec_char);
																								
																								// put_char(gps_rec_char);
																									gps_rec_char = uart_recv();
																									if(gps_rec_char == 'N')
																									 {
																										
																												//put_char(gps_rec_char);
																										  //  data(gps_rec_char);
																												gps_rec_char = uart_recv();
																										
																										//		data(gps_rec_char);
																										 //put_char(gps_rec_char);
																												while(lon < 10)
																													{
																														gps_rec_char = uart_recv();
																														//data(gps_rec_char);
																														//put_char(gps_rec_char);
																														lat_lon[i] = gps_rec_char;
																														lon++;
																														i++;
																													}
																												
																													if(i > 18)
																													{
																														lat_lon[i] = '\0';
																														break;
																													}
																									 }
																						}
																				
																		}
																}	
														}
												}
									 }
								}
				  }
					
			string_uart_trns_gsm(lat_lon);
						
				cmd(0x01);
					for(p = 0; p < 9;p++)
						{
							lati[p] = lat_lon[p];
						}
						lati[p] = '\0';
						for(q = 0; q < 10;q++)
						{
							logtd[q] = lat_lon[p];
							p++;
						}
						logtd[q] = '\0';
					display_string(lati);// displaying on lcd
						gsm_send_msg(lati);// sending message
						cmd(0xc0);
						display_string(logtd);//dispalying on lcd
						gsm_send_msg(logtd);// sending message
					
				}
				
				