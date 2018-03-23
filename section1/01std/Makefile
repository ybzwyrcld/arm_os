.PHONY: clean

CROSS_COMPILE=arm-elf-

all: helloworld.bin

helloworld.o: helloworld.c
	$(CROSS_COMPILE)gcc -c $^ -o $@

helloworld.elf: helloworld.o
	$(CROSS_COMPILE)ld -e helloworld -Ttext 0x0 $^ -o $@

helloworld.bin: helloworld.elf
	$(CROSS_COMPILE)objcopy -O binary $^ $@


clean:
	rm -rf *.o helloworld.elf helloworld.bin
