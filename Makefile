CC=gcc
CFLAGS=-W -Wall -pedantic
SRC=main.c
all: test
test: ppm.o
				$(CC) $(CFLAGS) test/ppm.c ppm.o -o test
ppm.o:
				$(CC) $(CFLAGS) -c src/img/ppm.h -o ppm.o
clean:
				rm -rf *.o
mrproper: clean
				rm -rf test
