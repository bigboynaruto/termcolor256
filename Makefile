CC=gcc
CFLAGS=-Iinclude

vpath %.c src
vpath %.h include

example1: example1.o

example2: example2.o

example3: example3.o

clean:
	rm -f *.o example*
