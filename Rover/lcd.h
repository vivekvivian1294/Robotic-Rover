

	#define EN (1 << 10)
	#define RW  (1 << 12)
	#define RS  (1 << 13)
	#define BUZZ (1 << 25)
	#define DATA  (0Xff << 15)
	#define port  EN | RW | RS | DATA | BUZZ
	
	void lcd_init(void);
	void cmd(char c);
	void data(char d);
	void display(long int n);
	void delay(long int count);
		void display_string(char *str);