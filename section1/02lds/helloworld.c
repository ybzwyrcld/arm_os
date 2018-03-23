// s3c2410 串口发送缓存寄存器地址
#define UFCON0	((volatile unsigned int *)(0x50000020))

void helloworld(void)
{
	const char *p="helloworld\n";

	while(*p != 0){
		*UFCON0=*p++;
	}

	while(1);
}
