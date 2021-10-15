obj-m += myDriver.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
install:
	sudo insmod myDriver.ko
remove:
	sudo rmmod myDriver.ko
run_dmesg:
	sudo dmesg -C
	sudo insmod myDriver.ko
	sudo rmmod myDriver.ko
	dmesg -t > dmesg.txt