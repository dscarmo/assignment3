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
#include "intersec.h"


typedef struct tmapStructure{
	double x[100];
	double y[100];
	int n;
}MapStructure;

typedef struct inputArgs{
	double gravity;
	double thrust;
	FILE *map;
	MapStructure *mapStructure;
}iArgs;


typedef struct shipData{
	double centerPos[2];	
	double xspeed, yspeed;
	double xA, yA;
	double structure[2][3];
	int rotationAngle;
	int thrustOn;
	int collision; 
}Ship;


void initializeShip (Ship *ship);	
void moveShip(Ship *ship, FILE *sketch, int direction);
void drawShip(Ship *ship, FILE *sketch);
void eraseShip(Ship *ship, FILE *sketch);
void recreateShip (Ship *ship);
int checkCollision(Ship *ship, iArgs input);
void applyAccelerations(Ship *ship, iArgs input, FILE *sketch);
void rotateShip(Ship *ship, int angle);
void checkBoundaries(Ship *ship);
int freeAndQuit(double *mapx, double *mapy, int returnValue);
MapStructure *drawLand(FILE* map, FILE *sketch);
void explode(Ship *ship, FILE *sketch);
#endif
