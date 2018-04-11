#define  TIMER_BASE  (0xd1000000)  // TIMER基地址
#define  TCFG0   ((volatile unsigned int *)(TIMER_BASE + 0x0))  // 一级分频器 15:8
#define  TCFG1   ((volatile unsigned int *)(TIMER_BASE + 0x4))  // 二级分频器 19:16
#define  TCON    ((volatile unsigned int *)(TIMER_BASE + 0x8))  // 配置TIMER4 22:20
#define  TCNTB4  ((volatile unsigned int *)(TIMER_BASE + 0x3c)) // TIMER4被减数值

void timer_init(void)
{
//	*TCFG0 |= 0x800;
	*TCFG0 |= (0xff<<8);  // 1/256分频
	*TCFG1 |= (0x3<<16);  // 1/16分频
	*TCON &= (~(0x7<<20));  // 关闭timer4
	*TCON |= (0x0<<22);  // 设置timer4不自动加载
	*TCON |= (0x1<<21);  // 手动更新timer4
	*TCNTB4 = 0xffff;  // 设置timer4计数器
	*TCON |= (0x1<<20);  // 打开timer4
	*TCON &= (~(0x1<<21));  // 关闭timer4手动更新

	umask_int(14); // 设置中断号 
	enable_irq();  // 使能中断
}
