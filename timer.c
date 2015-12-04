/*
 * Assignment 3, CMPUT 201, FALL 2015
 * 
 * Student Name: Diedre Santos do Carmo
 * Student ID: 1484008
 * 
 * 
 * Timer functions, partly from professor material (A3Files)
 *
 *  
*/
#include "timer.h"

// global value which our signal handler will use to communicate we're finished
static int g_finished = 0;

//Global pointers for signal handler to access
Ship *tship;
iArgs inp;
FILE *sket;
int thrustTimer = 0;

//Setups timer configurations and listens for keyboard in signals intervals
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



//handler for SIGALRM
void handle_timeout(int signal)
{
	static int called = 0;

	// check that we were called because of SIGALRM
	if( signal == SIGALRM ) {

		called++;

		//Every 0.05 update ship
		criticalZone(tship, inp, sket);

		if (!(called%20)){
			if (tship -> thrustOn){
				thrustTimer++;
				if (thrustTimer == 2){
					tship -> thrustOn = 0;
					thrustTimer = 0;				
				}			
			}
			
			printw( "%d second(s)\n", called/20 );
		}
		
		if( tship -> collision ) {
			struct itimerval timer;

			printw("You exploded!!! Press q to quit.\n");


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



//Critical zone code, partly from A3Files
void criticalZone(Ship *ship, iArgs input, FILE *sketch)
{
	sigset_t block_mask;
	sigset_t old_mask;
	sigemptyset( &block_mask );
	sigaddset( &block_mask, SIGALRM );

	// blocks signal
	if( sigprocmask( SIG_BLOCK, &block_mask, &old_mask ) < 0 ) {
		exit( EXIT_FAILURE );
	}

	// CRITICAL CODE GOES
	applyAccelerations(ship, input, sketch);
	if (checkCollision(ship, input)){ 
		if (ship -> yspeed > 30){ 
				
			explode(tship, sket);
		}
		else printw("You landed!");
		ship -> collision = 1;	
	}
	//

	// unblock signal by setting mask to old value from before we added SIGALRM
	if( sigprocmask( SIG_SETMASK, &old_mask, NULL ) < 0 ) {
		exit( EXIT_FAILURE );
	}
}
