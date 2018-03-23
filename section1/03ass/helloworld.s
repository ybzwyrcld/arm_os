.arch	armv4					@armv4体系结构
.global	helloworld				@helloworld符号对连接器可见

.equ	REG_FIFO, 0x50000020	@宏定义, s3c2410串口发送缓存寄存器地址

.text		@以下归为代码段
.align 2	@代码字节对齐为2Byte

helloworld:
	ldr 	r1,=REG_FIFO	@常量装载伪指令, 将REG_FIFO赋值给r1
	adr 	r0,.L0			@地址装载伪指令, 将符号.L0加载到r0中

.L2:
	ldrb	r2,[r0],#0x1	@内存装载指令, 立即数后变址寻址,r2=[r0], r0+0x1
	str		r2,[r1]			@内存存储指令, 将r2寄存器的值存储到r1寄存器所指向的地址处
	cmp		r2,#0x0			@两个操作数相减, 改变CPSR寄存器零标志位
	bne		.L2				@根据CPSR寄存器零标志位判断, 若不等于则跳转到符号.L2处

.L1:
	b		.L1				@while(1)循环 

.align 2
.L0:
	.ascii "helloworld\n\0"		@在内存中定义字符串"helloworld\n"
