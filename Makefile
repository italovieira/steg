C=gcc
CFLAGS=-W -Wall -pedantic -ansi -std=c99
SRC=main.c
OBJS=ppm.o pixel.o

all: main
main: src/main.c $(OBJS)
				$(CC) $(CFLAGS) src/main.c $(OBJS) -o steg
test: test/ppm.c $(OBJS)
				$(CC) $(CFLAGS) test/ppm.c $(OBJS) -o test/test
ppm.o: src/img/ppm.c
				$(CC) $(CFLAGS) -c src/img/ppm.c -o ppm.o
pixel.o: src/img/pixel.c
				$(CC) $(CFLAGS) -c src/img/pixel.c -o pixel.o
clean:
				rm -rf *.o
mrproper: clean
				rm -rf test
