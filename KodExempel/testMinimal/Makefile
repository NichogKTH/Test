# A simple Makefile for compiling small SDL projects

run: main.o spaceman.o Alien.o world.o
	gcc -o theGame main.o spaceman.o Alien.o world.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
main.o: main.c
	gcc -c main.c
spaceman.o: spaceman.c
	gcc -c spaceman.c
world.o: world.c
	gcc -c world.c
Alien.o: Alien.c
	gcc -c Alien.c