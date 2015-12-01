/*
 * Assignment 3, CMPUT 201, FALL 2015
 * 
 * Student Name: Diedre Santos do Carmo
 * Student ID: 1484008
 * 
 * 
 * Timer functions, 80% from professor material
 *
 *  
*/
#include "timer.h"

// global value which our signal handler will use to communicate we're finished
static int g_finished = 0;
Ship *tship;
iArgs inp;
FILE *sket;

int startTimer(Ship *ship, FILE *sketch, iArgs input, int * c)
{
	struct sigaction handler;
	
	tship = ship;
	inp = input;
	sket = sketch;
	move(7,10);
	// handle_timeout is function to call when signal is sent
	handler.sa_handler = handle_timeout;


	sigemptyset( &handler.sa_mask );

	handler.sa_flags = 0;

	// use signal handler defined in handler to handle SIGALRM signals
	if( sigaction( SIGALRM, &handler, NULL ) < 0 ) {
		exit( EXIT_FAILURE );
	}

	// set up timer  (sends SIGLARM)
	struct itimerval timer;

	// value for time until first SIGALRM
	timer.it_value.tv_sec = 0;  // 0 in the example lander program
	timer.it_value.tv_usec = 50000; // 50000 in the example lander program
	// interval between subsequent alarms
	timer.it_interval.tv_sec = 0;  // 0 in the example lander program
	timer.it_interval.tv_usec = 50000; // 50000 in the example lander program

	// will execute repeatedly, sending SIGALRM every timer.it_interval
	// seconds/microseconds, with an inital delay of timer.it_value.
	if( setitimer( ITIMER_REAL, &timer, NULL ) < 0 ) {
		exit( EXIT_FAILURE );
	}

	// loop until we're done
	while( !g_finished ) {

		g_finished = listening(ship, sketch, input, c);

	}

	return( EXIT_SUCCESS );
}



//handler for SIGALRM.
void handle_timeout(int signal)
{
	static int called = 0;

	// check that we were called because of SIGALRM
	if( signal == SIGALRM ) {

		called++;
		//Every 0.05 update ship
		criticalZone(tship, inp, sket);

		if (!(called%20)){

			printw( "%d second(s)\n", called/20 );
		}
		if( called/20 == 60 ) {
			struct itimerval timer;

			printf("time out!\n");


			timer.it_interval.tv_sec = 0;
			timer.it_interval.tv_usec = 0;
			timer.it_value.tv_sec = 0;
			timer.it_value.tv_usec = 0;
			if( setitimer( ITIMER_REAL, &timer, NULL ) < 0 ) {
				exit( EXIT_FAILURE );
			}

			// notify the main program that we're done
			g_finished = 1;
		}
	}
}


// critical code is code that must not be interrupted.  In your asn3,
// examples will include code that updates global data structures, and
// code that erases an old ship and draws a new ship (i.e., moves the
// ship).
//
// The only way code can be interrupted in asn3 code is via our timer
// (i.e., by SIGALRM).
//
// We protect critical code by blocking the signal.
//
// The following is just an example of signal blocking; there is not
// critical code to block.
void criticalZone(Ship *ship, iArgs input, FILE *sketch)
{
	// signals we want to block (only SIGALM in our case)
	sigset_t block_mask;
	// set of previously blocked signals
	sigset_t old_mask;

	// set up set of signals to block: start with empty set, add SIGALRM
	sigemptyset( &block_mask );
	sigaddset( &block_mask, SIGALRM );
	// NOTE: more complicated code might start by calling sigprocmask to
	// get the current blocked signals and adding the new signal

	// set blocked signal set to block_mask (man 2 sigprocmask) to block SIGALRM.
	// returns previously blocked signals in old_mask.
	if( sigprocmask( SIG_BLOCK, &block_mask, &old_mask ) < 0 ) {
		exit( EXIT_FAILURE );
	}

	// CRITICAL CODE GOES HERE
	// can call other functions here, and they will not be interrupted
	// ...
	applyAccelerations(ship, input, sketch);
	//TODO check collision here
	
	// unblock signal by setting mask to old value from before we added SIGALRM
	if( sigprocmask( SIG_SETMASK, &old_mask, NULL ) < 0 ) {
		exit( EXIT_FAILURE );
	}
}
