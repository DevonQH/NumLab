cc = gcc
cflags = -O2
clibs = 

decomp: decomp.o
	cc decomp.o -o decomp

decomp.o: decomp.c
	cc -c decomp.c $(cflags)

run:
	./decomp

clean:
	rm -rf ./*.o decomp
