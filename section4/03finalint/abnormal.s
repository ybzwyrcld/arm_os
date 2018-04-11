@ 宏定义, 根据s3c2410手册定义常量
.equ  DISABLE_FIQ,  0X40
.equ  DISABLE_IRQ,  0X80
.equ  SVC_MOD,      0X13
.equ  IRQ_MOD,      0X12
.equ  FIQ_MOD,      0X11
.equ  ABT_MOD,      0X17
.equ  UND_MOD,      0X1b
.equ  SYS_MOD,      0X1f

@ 宏定义
.macro CHANGE_TO_SVC
	msr  cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | SVC_MOD)
.endm
@.macro CHANGE_TO_IRQ
@	msr  cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | IRQ_MOD)
@.endm
@.macro enable_irq reg
@	mrs  \reg, cpsr
@	bic  \reg, \reg, #DISABLE_IRQ
@	msr  cpsr, \reg
@.endm
@.macro disable_irq reg
@	mrs  \reg, cpsr
@	orr  \reg, \reg, #DISABLE_IRQ
@	msr  cpsr, \reg
@.endm


@ 设定以下符号对于连接器可见
.global __vector_undefine
.global __vector_swi
.global __vector_prefetch_abort
.global __vector_data_abort
.global __vector_resevered
.global __vector_irq
.global __vector_fiq

.text	@ 文本段开始
.code 32	@ 编译生成32bit指令集代码

@ 异常向量表处理
__vector_undefine:
	nop		@ 空指令,占一个时钟周期

__vector_swi:
	nop

__vector_prefetch_abort:
	nop

__vector_data_abort:
	nop

__vector_resevered:
	nop

__vector_irq:
	@ r13:  栈寄存器
	@ r14:  链接寄存器
	@ spsr: 保存的程序状态寄存器
	@ common_irq_handler: 中断处理函数标号
    sub    r14,  r14, #4
    str    r14,  [r13, #-0x4]
	mrs    r14,  spsr
    str    r14,  [r13, #-0x8]
    str    r0,   [r13, #-0xc]
	mov    r0,   r13
	CHANGE_TO_SVC
    str    r14,  [r13, #-0x8]!
    ldr    r14,  [r0, #-0x4]
    str    r14,  [r13, #-0x4]
    ldr    r14,  [r0, #-0x8]
    ldr    r0,   [r0, #-0xc]
    stmdb  r13!, {r0-r3, r14}
    bl     common_irq_handler
    ldmia  r13!, {r0-r3, r14}
	msr    spsr, r14
    ldmfd  r13!, {r14, pc}^

__vector_fiq:
	nop

