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

void test_mmu()
{
    char *p = "mmu init ok\n";
    
    while(*p != 0){
        *((volatile unsigned int *)(0xd0000020)) = *p++;
    }
}


static init_func init[] = {
	helloworld,
	0,
};

void plat_boot(void)
{
	extern void test_vparameter(int, ...);
	int i;
	for(i=0; init[i]; ++i){
		init[i]();
	}	

	init_sys_mmu();
	start_mmu();
	test_mmu();
	test_vparameter(3, 1, 2, 3);
	test_vparameter(1, 4);

	while(1);
}

