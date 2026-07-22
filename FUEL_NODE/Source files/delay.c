void delay_us(int d)
{
	d=d*12;
	while(d--);
}
void delay_ms(int d)
{
	d=d*12000;
	while(d--);
}
void delay_s(int d)
{
	d=d*12000000;
	while(d--);
}
