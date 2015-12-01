/*
 * Assignment 3, CMPUT 201, FALL 2015
 * 
 * Student Name: Diedre Santos do Carmo
 * Student ID: 1484008
 * 
 * 
 * Timer functions declarations
 */
#ifndef TIMER_H_
#define TIMER_H

#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> // for signal handling
#include <sys/time.h> // for the timer
#include "curse.h"
#include "intersec.h"

// our signal handler function which will be called whenever the timer expires

void handle_timeout( int signal );
int startTimer(Ship *ship, FILE *sketch, iArgs input, int * c);
void handle_timeout(int signal);
void criticalZone(Ship *ship, iArgs input, FILE *sketch);


#endif
