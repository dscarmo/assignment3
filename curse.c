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
void moveShip(int *coords, FILE *sketch, int direction){
	fprintf(sketch,"eraseSegment %d %d %d %d\n", coords[0], coords[1], coords[2], coords[3]);
	fflush(sketch);		

	switch(direction){
		case 0:		
			coords[1]+= 10;
			coords[3]+= 10;
			break;
		case 1:
			coords[0]-= 10;
			coords[2]-= 10;
			break;
		case 2:
			coords[0]+= 10;
			coords[2]+= 10;
			break;
		case 3:
			coords[1]-= 10;
			coords[3]-= 10;
			break; 
	}

	fprintf(sketch,"drawSegment %d %d %d %d\n", coords[0], coords[1], coords[2], coords[3]);
	fflush(sketch);	
}

int listenKeys(FILE *sketch, iArgs input){
	int running, c;
	//int numOfLoops = 0;
	int debugCoords[4] = {20, 20, 40, 40};
	Ship ship;
	
	init_ncurses();

	mvprintw( 5, 10, "Press any key to start." );
	refresh(); // printed output doesn't appear until we refresh
	c = getch();

	nodelay( stdscr, TRUE ); // have getch() return ERR if input isn't ready

	erase();
	mvprintw( 5, 10, "Press arrow keys, 'q' to quit." );
	refresh();

	running = 1;
	
	//TODO define drawBackground
	initializeShip (&ship);
	fprintf(sketch,"drawSegment %d %d %d %d\n", debugCoords[0], debugCoords[1], debugCoords[2], debugCoords[3]);
	fflush(sketch);
	printw("background is drawn only one time\n");	
	//drawBackground();	

	do {
		
		c = getch();
		
		//TODO define update graphics
		//updateGraphics();
		if( c == ERR ) { continue; } // keep looping until we get input
		
		erase();
		mvprintw( 5, 10, "Press arrow keys, 'q' to quit." );
		move( 6, 10 );
		switch( c ) {
			case KEY_DOWN:
				printw( "down key pressed" );
				moveShip(debugCoords, sketch, 0);					
				break;

			case KEY_LEFT:
				printw( "left key pressed" );
				moveShip(debugCoords, sketch, 1);
				break;

			case KEY_RIGHT:
				printw( "right key pressed" );
				moveShip(debugCoords, sketch, 2);				
				break;

			case KEY_UP:
				printw( "up key pressed" );
				moveShip(debugCoords, sketch, 3);				
				break;
			case ' ':
				//TODO define thrust things
				printw("thrust used!");
				break;
			case 'q':
				running = 0;
				break;

			default:
				// do nothing
				break;
		}
		refresh();
	} while( running );

	// must do this or else the terminal will be unusable
	shutdown_ncurses();

	return EXIT_SUCCESS;
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
