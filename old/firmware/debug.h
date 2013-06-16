void put_c(unsigned char c);
unsigned char USART_Receive( void );
void put_s(unsigned char *ptr);
void dip_c(unsigned char c);
void timer0_init(void);
SIGNAL(SIG_OVERFLOW0);
void init_USART(void);
void debug(char *str);

