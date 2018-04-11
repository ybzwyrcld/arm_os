.section .startup	@ .section声明以下代码属于.startup段
.code 32	@ 编译生成32bit指令集代码
.align 0	

.global _start		@ _start符号对连接器可见
@ 声明外部变量
.extern __vector_reset
.extern __vector_undefine
.extern __vector_swi
.extern __vector_prefetch_abort
.extern __vector_data_abort
.extern __vector_resevered
.extern __vector_irq
.extern __vector_fiq


_start:	
  ldr		pc, _vector_reset		@ 跳转到_vector_reset段出继续执行
  @ 以下为异常发生时才会跳转到对应段继续执行
  ldr		pc, _vector_undefine
  ldr		pc, _vector_swi
  ldr		pc, _vector_prefetch_abort
  ldr		pc, _vector_data_abort
  ldr		pc, _vector_resevered
  ldr		pc, _vector_irq
  ldr		pc, _vector_fiq


.align 4

_vector_reset:				.word 	__vector_reset
_vector_undefine:			.word 	__vector_undefine
_vector_swi:				.word 	__vector_swi
_vector_prefetch_abort:		.word 	__vector_prefetch_abort
_vector_data_abort:			.word 	__vector_data_abort
_vector_resevered:			.word 	__vector_resevered
_vector_irq:				.word 	__vector_irq
_vector_fiq:				.word 	__vector_fiq
