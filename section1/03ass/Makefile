.PHONY: clean

CROSS_COMPILE=arm-elf-

all: helloworld.bin

helloworld.o: helloworld.s
	$(CROSS_COMPILE)as $^ -o $@ 

helloworld.elf: helloworld.o
	$(CROSS_COMPILE)ld -e helloworld -T helloworld.lds $^ -o $@

helloworld.bin: helloworld.elf
	$(CROSS_COMPILE)objcopy -O binary $^ $@


clean:
	rm -rf *.o helloworld.elf helloworld.bin
