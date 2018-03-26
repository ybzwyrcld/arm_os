.PHONY: clean

CC=arm-elf-gcc
LD=arm-elf-ld
OBJCOPY=arm-elf-objcopy
LIB_DIR=/opt/toolchain/arm-elf/lib/gcc/arm-elf/4.4.3

CFLAGS=-O2 -g
ASFLAGS=-O2 -g
LDFLAGS=-static -nostartfiles -nostdlib -T benos.lds -Ttext 0x30000000

OBJECTS=abnormal.o boot.o start.o init.o 

.c.o:
	$(CC) $(CFLAGS) -c $<

.s.o:
	$(CC) $(ASFLAGS) -c $<

benos: $(OBJECTS)
	$(LD) $(LDFLAGS) $? -o $@ -L $(LIB_DIR) -lgcc
	$(OBJCOPY) -O binary $@ benos.bin

clean:
	rm -rf *.o benos benos.bin
