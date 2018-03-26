typedef void (*init_func)(void);

/* s3c2410 串口发送缓存寄存器地址 */
#define UFCON0	((volatile unsigned int *)(0x50000020))

void helloworld(void)
{
	const char *p="helloworld\n";

	while(*p != 0){
		*UFCON0=*p++;
	}
}

static init_func init[] = {
	helloworld,
	0,
};

void plat_boot(void)
{
	int i;
	for(i=0; init[i]; ++i)
		init[i]();
	
	while(1);
}

