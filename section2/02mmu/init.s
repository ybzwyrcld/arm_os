@ 宏定义, 根据s3c2410手册定义常量
.equ  DISABLE_FIQ,  0X40
.equ  DISABLE_IRQ,  0X80
.equ  SVC_MOD,      0X13
.equ  IRQ_MOD,      0X12
.equ  FIQ_MOD,      0X11
.equ  ABT_MOD,      0X17
.equ  UND_MOD,      0X1b
.equ  SYS_MOD,      0X1f

@ 内存基地址为0x30000000, 大小为8M
.equ  MEM_SIZE,   0x800000
.equ  TEXT_BASE,  0x30000000

@ 定义异常模式栈, 从内存最高地址-4开始往低内存地址,每个栈大小为1K
.equ  _SVC_STACK,   (TEXT_BASE+MEM_SIZE-4)
.equ  _IRQ_STACK,   (_SVC_STACK-0x400)
.equ  _FIQ_STACK,   (_IRQ_STACK-0x400)
.equ  _ABT_STACK,   (_FIQ_STACK-0x400)
.equ  _UND_STACK,   (_ABT_STACK-0x400)
.equ  _SYS_STACK,   (_UND_STACK-0x400)

.text    @ 文本段开始
.code 32   @ 32bit指令集代码

.global  __vector_reset
.extern  plat_boot
.extern  __bss_start__
.extern  __bss_end__

@ 各个模式栈初始化
__vector_reset:
  msr  cpsr_c, #(DISABLE_IRQ|DISABLE_FIQ|SVC_MOD)
  ldr  sp, =_SVC_STACK

  msr  cpsr_c, #(DISABLE_IRQ|DISABLE_FIQ|IRQ_MOD)
  ldr  sp, =_IRQ_STACK

  msr  cpsr_c, #(DISABLE_IRQ|DISABLE_FIQ|FIQ_MOD)
  ldr  sp, =_FIQ_STACK

  msr  cpsr_c, #(DISABLE_IRQ|DISABLE_FIQ|ABT_MOD)
  ldr  sp, =_ABT_STACK

  msr  cpsr_c, #(DISABLE_IRQ|DISABLE_FIQ|UND_MOD)
  ldr  sp, =_UND_STACK

  msr  cpsr_c, #(DISABLE_IRQ|DISABLE_FIQ|SYS_MOD)
  ldr  sp, =_SYS_STACK

@ 清理bss段
_clear_bss:
  ldr  r1, _bss_start_
  ldr  r3, _bss_end_
  mov  r2, #0x0	

loop:
  cmp  r1, r3	
  beq  _main  @ 若bss段清理完成, 跳出循环
  str  r2, [r1], #0x4
  b    loop

_main:
  b    plat_boot  @ 跳转到plat_boot函数

_bss_start_:  .word  __bss_start__
_bss_end_:    .word  __bss_end__

.end
