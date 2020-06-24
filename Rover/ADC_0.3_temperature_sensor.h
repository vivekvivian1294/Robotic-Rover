


		#define CH (1 << 3)
		#define CLK_DIV (3 << 8)
		#define BST_ON (1 << 16)
		#define BST_OFF (0 << 16)
		#define CLK_RES (0 << 17)
		#define OPERATIONAL (1 << 21)
		#define START (1 << 24)

		#define adc0_init_macro (CH | CLK_DIV | BST_OFF | CLK_RES | OPERATIONAL)
		
		void adc0_init_temperature_sensor(void);
		long int adc_read_value_temperature_sensor(void);
		//void delay(long int count);