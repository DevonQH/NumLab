cc = gcc
cflags = 
clibs = 

interp: interp.o
	cc interp.o -o interp

interp.o: interp.c
	cc -c interp.c $(cflags)

run:
	./interp

clean:
	rm -rf *.o interp
