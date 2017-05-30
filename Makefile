# Compiler variable
CC = g++

CFLAGS = -c -Wall

all: chip8

chip8: chip8.o main.o
	$(CC) main.o chip8.o -o chip8

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

chip8.o: chip8.cpp
	$(CC) $(CFLAGS) chip8.cpp

clean:
	rm -rf *o chip8