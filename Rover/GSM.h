

		
		#define UART1_TX (1 << 16)
		#define UART1_RX (1 << 18)
		#define UART1_GSM_ALL (UART1_TX | UART1_RX)
		
		#define LED1 (1<<4)
		#define LED2 (1<<5)
		#define LED3 (1<<6)
		#define LED4 (1<<7)
		#define LED_ALL (LED1 | LED2 | LED3 | LED4)
		
			//void delay(long int count);
			void gsm_send_msg(char *str);
		  void string_uart_trns_gsm(char *str);
		  void GSM_UART1_init(void);
		  void put_char_gsm(char c);
		  char uart_recv_gsm(void);
			char * int_to_string(long int y);