obj-m += hello.o hellop.o char_d.o my_own_driver.o

all:
	make -C /lib/modules/6.12.4-test/build M=$(PWD)	modules

clean:
	make -C /lib/modules/6.12.4-test/build M=$(PWD) clean
