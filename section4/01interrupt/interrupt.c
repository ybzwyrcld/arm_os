#define INT_BASE   (0xca000000)  // 中断基地址.
#define INTMASK    (INT_BASE+0x8)  // 中断屏蔽寄存器, 对应位写0使用该中断.
#define INTOFFSET  (INT_BASE+0x14)  // 中断偏移寄存器, 查看是哪个中断请求.
#define INTPND     (INT_BASE+0x10)  // 中断请求寄存器, 最终同一时刻只有一个中断源通过优先级仲裁.
#define SRCPND     (INT_BASE+0x0)  // 源请求寄存器, 可多个中断源同时产生.

void enable_irq(void)
{
    // 清除cpsr寄存器的I位, 全局使能中断
	asm volatile (
		"mrs  r4, cpsr\n\t"
		"bic  r4, r4, #0x80\n\t"
		"msr  cpsr, r4\n\t"
		:
		:
		:"r4"
	);

}

void umask_int(unsigned int offset)
{
	*((volatile unsigned int *)INTMASK) &= ~(1<<offset);
}

void common_irq_handler(void)
{
	unsigned int tmp = *((volatile unsigned int *)INTOFFSET);
    print("INTOFFSET = %d\t", *((volatile unsigned int *)INTOFFSET));
	*((volatile unsigned int *)INTPND) |= tmp;  // 对应位写1, 清除中断请求
	*((volatile unsigned int *)SRCPND) |= tmp;  // 对应位写1, 清除中断源
	// 清除INTPND和SRCPND对应位后,硬件会自动清除INTOFFSET对应位

    print("timer4 irq handler!\n");
}
