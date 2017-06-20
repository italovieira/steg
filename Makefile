C=gcc
CFLAGS=-W -Wall -pedantic -ansi -std=c99
SRC=main.c
OBJS=ppm.o pixel.o

all: test
test: test/ppm.c ppm.o pixel.o
				$(CC) $(CFLAGS) test/ppm.c ppm.o pixel.o -o teste
ppm.o: src/img/ppm.c
				$(CC) $(CFLAGS) -c src/img/ppm.c -o ppm.o
pixel.o: src/img/pixel.c
				$(CC) $(CFLAGS) -c src/img/pixel.c -o pixel.o
clean:
				rm -rf *.o
mrproper: clean
				rm -rf test
