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

#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3

#define ROT_ANGLE 10
#define SHIP_SIZE 10
#define INIT_POS 50
#define PI 3.14159265358979323846

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct inputArgs{
	double gravity;
	double thrust;
	FILE *map;
}iArgs;

typedef struct shipData{
	int centerPos[2];	
	int speed;
	double structure[2][3];
	int rotationAngle; 
}Ship;


void initializeShip (Ship *ship);	
void moveShip(Ship *ship, FILE *sketch, int direction);
void drawShip(Ship *ship, FILE *sketch);
void eraseShip(Ship *ship, FILE *sketch);
void recreateShip (Ship *ship);
void rotateShip(Ship *ship, int direction);
void drawLand(FILE* map, FILE *sketch);

#endif
