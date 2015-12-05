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

//Setups curse stuff and starts timer (in timer.c)
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
	input.mapStructure = drawLand(input.map, sketch);	
	
	startTimer(&ship, sketch, input, &c);	

	// must do this or else the terminal will be unusable
	shutdown_ncurses();

	return EXIT_SUCCESS;
}

//Listen for keyboard strokes (called from timer.c)
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
										
					break;

				case KEY_LEFT:
					if (ship -> collision){
						if (ship -> collision == 1)
							printw("You crashed, you cant move!");
						else if (ship -> collision == 2)
							printw("You landed, you cant move!");
					}					
					else 
						moveShip(ship, sketch, LEFT);
					break;

				case KEY_RIGHT:
					if (ship -> collision){
						if (ship -> collision == 1)
							printw("You crashed, you cant move!");
						else if (ship -> collision == 2)
							printw("You landed, you cant move!");
					}					
					else 
						moveShip(ship, sketch, RIGHT);				
					break;

				case KEY_UP:
									
					break;
				case ' ':
					if (ship -> collision){
						if (ship -> collision == 1)
							printw("You crashed, you cant move!");
						else if (ship -> collision == 2)
							printw("You landed, you cant move!");
					}					
					else{ 
						if (ship -> thrustOn){
							;	
						} else {
							ship -> thrustOn = 1;
						}
						printw("thrust used!");					 
					}
					
					break;
				case 'Q':
				case 'q':
					printw("Closing...");
					sleep(1);
					status = 1;
					break;

				default:
					// do nothing
					break;
			}
		}
		refresh();
		return status;
}

//Init curses copied from A3 files.
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
