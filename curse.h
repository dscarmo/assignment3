
/*
 * Assignment 3, CMPUT 201, FALL 2015
 * 
 * Student Name: Diedre Santos do Carmo
 * Student ID: 1484008
 * 
 * 
 * This handles input
 */

#ifndef _CURSE_H_
#define _CURSE_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ncurses.h>
#include "lander.h"
#include "timer.h"

int startCurse(FILE *sketch, iArgs input);
void init_ncurses();
void shutdown_ncurses();
int listening(Ship *ship, FILE *sketch, iArgs input, int * c);

#endif
