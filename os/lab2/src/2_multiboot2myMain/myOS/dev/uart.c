extern unsigned char inb(unsigned short int port_from);
extern void outb (unsigned short int port_to, unsigned char value);

//串口地址
#define uart_base 0x3F8

void uart_put_char(unsigned char c){
    outb (uart_base, c);
}

unsigned char uart_get_char(void){    
    return inb (uart_base);  
}

void uart_put_chars(char *str){ 
	//判断字符串尾
    while(*str!='\0'){
        uart_put_char(*str);
        str++;
    }
}