.arch	armv4					@armv4体系结构
.global	_start					@_start符号对连接器可见

.equ	REG_FIFO, 0x50000020	@宏定义, s3c2410串口发送缓存寄存器地址

.text		@以下归为代码段
.align 2	@代码字节对齐为2Byte

_start:
	ldr 	r0,=REG_FIFO	@常量装载伪指令, 将REG_FIFO赋值给r1
	adr 	r1,.L0			@地址装载伪指令, 将符号.L0加载到r0中
	bl		helloworld		@跳转到helloworld函数, 传参r0与r1, 保存返回地址

.L1:
	b		.L1				@while(1)循环 

.align 2
.L0:
	.ascii "helloworld\n\0"		@在内存中定义字符串"helloworld\n"
