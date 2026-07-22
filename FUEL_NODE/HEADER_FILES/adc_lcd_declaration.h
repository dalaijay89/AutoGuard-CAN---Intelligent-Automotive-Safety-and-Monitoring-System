void write_lcd(unsigned char data);
void cmd_lcd(unsigned char cmd);
void char_lcd(unsigned char ascii);
void Init_lcd(void);
void str_lcd(unsigned char* ptr);
void unsigned_lcd(unsigned int n);
void float_lcd(float f,unsigned int n);

void read_adc(unsigned int chno,unsigned int* adcDval,float* ear);
void Init_adc(void);
void delay_ms(int d);
void delay_us(int d);
void delay_s(int d);
