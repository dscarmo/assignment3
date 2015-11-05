# Assignment 3, CMPUT 201, FALL 2015 
# Student Name: Diedre Santos do Carmo
# Student ID: 1484008


CFLAGS= -Wall -std=c99 -g 

ball: ball.o
	gcc $(CFLAGS) ball.o -o ball -lncurses 

ball.o: ball.c
	gcc $(CFLAGS) -c ball.c -lncurses 	

test_curses: test_curses.o
	gcc $(CFLAGS) test_curses.o -o test_curses -lncurses 

test_curses.o: test_curses.c
	gcc $(CFLAGS) -c test_curses.c -lncurses 	

timer: timer.o
	gcc $(CFLAGS) timer.o -o timer -lncurses 

timer.o: timer.c
	gcc $(CFLAGS) -c timer.c -lncurses 	

tar:
	tar cvf submit.tar ball.c

clean:
	-rm -f *.o ball core
