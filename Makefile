clean:
	rm -f *.o *.bin *.iso

run: 
	nasm -f elf32 kernel/boot.s -o boot.o
	gcc -m32 -ffreestanding -c kernel/kernel.c -o kernel.o
	ld -m elf_i386 -T linker.ld -o kernel.bin boot.o kernel.o
	cp kernel.bin iso/boot/
	grub-mkrescue -o sapt.iso iso
	qemu-system-x86_64 -cdrom sapt.iso