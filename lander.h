/*
 * Assignment 3, CMPUT 201, FALL 2015
 * 
 * Student Name: Diedre Santos do Carmo
 * Student ID: 1484008
 * 
 * 
 * This and the .h has the game functions, such as drawing stuf and ship data
 */

#ifndef _LANDER_H_
#define _LANDER_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct inputArgs{
	double gravity;
	double thrust;
	FILE *map;
}iArgs;

typedef struct shipData{
	int centerPos[2];	
	int speed;
	int *structure[2];
}Ship;


void initializeShip (Ship *ship);	

#endif
