ENTRY(_start)
SECTIONS
{
	. = 0x00000000;
	.text :{
		start.o(.text)
		helloworld.o(.text)
	}
	. = ALIGN(32);
	.data :{
		*(.data)
	}
	. = ALIGN(32);
	.bss :{
		*(.bss)
	}
}
