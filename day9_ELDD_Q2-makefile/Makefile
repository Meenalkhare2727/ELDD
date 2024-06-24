
obj-m = pchar.o

modules:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/sunbeam/Desktop/linux/ M=`pwd` modules
	
copy:
	scp pchar.ko debian@192.168.6.2:/home/debian/
clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/sunbeam/Desktop/linux/ M=`pwd` clean		
	
	
	

.PHONY: all clean

