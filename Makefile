all:
	make -C main
	make -C modules
	
clean:
	make -C main clean
	make -C modules clean
