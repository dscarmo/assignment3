/*
 * Assignment 3, CMPUT 201, FALL 2015
 * 
 * Student Name: Diedre Santos do Carmo
 * Student ID: 1484008
 * 
 * 
 * This handles input
 */


#include "curse.h"
//Debug move

int startCurse(FILE *sketch, iArgs input){
	int c;

	Ship ship;
	
	init_ncurses();

	mvprintw( 5, 10, "Press any key to start." );
	refresh(); // printed output doesn't appear until we refresh
	c = getch();

	nodelay( stdscr, TRUE ); // have getch() return ERR if input isn't ready

	erase();
	mvprintw( 5, 10, "Press arrow keys, 'q' to quit." );
	refresh();
	
	initializeShip (&ship);
	drawShip(&ship, sketch);	
	drawLand(input.map, sketch);	

	
	startTimer(&ship, sketch, input, &c);	

	// must do this or else the terminal will be unusable
	shutdown_ncurses();

	return EXIT_SUCCESS;
}

int listening(Ship *ship, FILE *sketch, iArgs input, int * c){
		int status = 0;
		*c = getch();
		if( *c == ERR ) 
		{  
		} 
		else {
			erase();
			mvprintw( 5, 10, "Press arrow keys, 'q' to quit." );
			move( 6, 10 );
			switch( *c ) {
				case KEY_DOWN:
					printw( "down key pressed" );
					moveShip(ship, sketch, DOWN);					
					break;

				case KEY_LEFT:
					printw( "left key pressed" );
					moveShip(ship, sketch, LEFT);
					break;

				case KEY_RIGHT:
					printw( "right key pressed" );
					moveShip(ship, sketch, RIGHT);				
					break;

				case KEY_UP:
					printw( "up key pressed" );
					moveShip(ship, sketch, UP);				
					break;
				case ' ':
					if (ship -> thrustOn){
						ship -> thrustOn = 0;	
					} else {
						ship -> thrustOn = 1;
					}
					 
					printw("thrust used!");
					break;
				case 'Q':
				case 'q':
					sleep(1);
					fprintf(sketch, "end");
					status = 1;
					//*running = 0;
					break;
					
				case 'r':
					initializeShip(ship);
					break;

				default:
					// do nothing
					break;
			}
		}
		refresh();
		return status;
}

void init_ncurses()
{
	int r;

	// start up the ncurses environment
	initscr(); // nothing to check, initscr exits on error

	// don't wait for enter for keyboard input
	r = cbreak(); assert( r != ERR );

	// don't echo keypresses to screen
	r = noecho(); assert( r != ERR );

	r = nonl(); assert( r != ERR );

	// turn cursor off
	r = curs_set( 0 ); assert( r != ERR );

	// don't worry about cursor position
	r = leaveok( stdscr, TRUE ); assert( r != ERR );

	// slower handling of ^C but saner output
	r = intrflush( stdscr, FALSE ); assert( r != ERR );

	// translate movement espace codes into single keys
	r = keypad( stdscr, TRUE ); assert( r != ERR );
}

void shutdown_ncurses()
{
	endwin();
}
