# Assignment 3, CMPUT 201, FALL 2015 
# Student Name: Diedre Santos do Carmo
# Student ID: 1484008
# Makefile

CFLAGS= -Wall -g

main: main.o curse.o lander.o timer.o intersec.o
	gcc $(CFLAGS) main.o curse.o lander.o timer.o intersec.o -o main -lncurses -lm

main.o: main.c
	gcc $(CFLAGS) -c main.c	

curse.o: curse.c
	gcc $(CFLAGS) -c curse.c -lncurses 	

lander.o: lander.c
	gcc $(CFLAGS) -c lander.c -lm	

timer.o: timer.c
	gcc $(CFLAGS) -c timer.c -lncurses

intersec.o: intersec.c
	gcc $(CFLAGS) -c intersec.c -lm 

tar:
	tar cvf submit.tar main.c main.h Makefile

clean:
	-rm -f *.o main core
