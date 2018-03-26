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
	nop

__vector_fiq:
	nop

