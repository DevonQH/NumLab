cc = g++
cflags = -O2
clibs = 

integer: integer.o
	cc integer.o -o integer

integer.o: integer.c
	cc -c integer.c $(cflags)

run:
	./integer

clean:
	rm -rf ./*.o integer
