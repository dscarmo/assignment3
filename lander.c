/*
 * Assignment 3, CMPUT 201, FALL 2015
 * 
 * Student Name: Diedre Santos do Carmo
 * Student ID: 1484008
 * 
 * 
 * This and the .h has the game functions, such as drawing stuf and ship data
 */

#define ROT_ANGLE 10
#define SHIP_SIZE 5
#define INIT_POS 20
#define PI 3.1415

#include "lander.h"

void initializeShip (Ship *ship){
	ship -> centerPos[0] = INIT_POS;
	ship -> centerPos[1] = INIT_POS;
	ship -> speed = 0;
	
	recreateShip(ship);
}

void recreateShip (Ship *ship){
	int x = ship -> centerPos[0];
	int y = ship -> centerPos[1];

	
	(ship -> structure)[0][0] = x;
	(ship -> structure)[0][1] = x - SHIP_SIZE;
	(ship -> structure)[0][2] = x + SHIP_SIZE;
	(ship -> structure)[1][0] = y - 2*SHIP_SIZE;
	(ship -> structure)[1][1] = y + SHIP_SIZE;
	(ship -> structure)[1][2] = y + SHIP_SIZE;
	
}

void drawShip(Ship *ship, FILE *sketch){
	//Triangle ship
	recreateShip(ship);
	fprintf(sketch,"drawSegment %d %d %d %d\n", ship -> structure[0][0], ship -> structure[1][0], ship -> structure[0][1], ship -> structure[1][1]);
	fprintf(sketch,"drawSegment %d %d %d %d\n", ship -> structure[0][1], ship -> structure[1][1], ship -> structure[0][2], ship -> structure[1][2]);
	fprintf(sketch,"drawSegment %d %d %d %d\n", ship -> structure[0][2], ship -> structure[1][2], ship -> structure[0][0], ship -> structure[1][0]);
	fflush(sketch);
}

void eraseShip(Ship *ship, FILE *sketch){	
	fprintf(sketch,
		"eraseSegment %d %d %d %d\n", ship -> structure[0][0], ship -> structure[1][0], ship -> structure[0][1], ship -> structure[1][1]);
	fprintf(sketch,
		"eraseSegment %d %d %d %d\n", ship -> structure[0][1], ship -> structure[1][1], ship -> structure[0][2], ship -> structure[1][2]);
	fprintf(sketch,
		"eraseSegment %d %d %d %d\n", ship -> structure[0][2], ship -> structure[1][2], ship -> structure[0][0], ship -> structure[1][0]);
	fflush(sketch);	
}

void moveShip(Ship *ship, FILE *sketch, int direction){
	eraseShip(ship, sketch);	

	switch(direction){
		//down, left, right, up
		case 0:		
			ship -> centerPos[0] += 0;
			ship -> centerPos[1] += 10;
			break;
		case 1:
			//ship -> centerPos[0] -= 10;
			//ship -> centerPos[1] -= 0;
			rotateShip(ship, 0);
			break;
		case 2:
			//ship -> centerPos[0] += 10;
			//ship -> centerPos[1] += 0;
			rotateShip(ship, 1);
			break;
		case 3:
			ship -> centerPos[0] -= 0;
			ship -> centerPos[1] -= 10;
			break; 
	}

	drawShip(ship, sketch);	
}

void rotateShip(Ship *ship, int direction){
	int i = 0;
	double ar;
	if (direction == 1) 
		ar = ROT_ANGLE * PI / 180.0;
	else 
	 	ar = -ROT_ANGLE * PI / 180.0;
	double rotated_x, rotated_y;
	double x, y;

	for (i = 0; i < 3; i++)
	{
		x = ship -> structure[0][i];
		y = ship -> structure[1][i];
		rotated_x = x*cos(ar) - y*sin(ar);
		rotated_y = x*sin(ar) + y*cos(ar);		
		ship -> structure[0][i] = rotated_x;
		ship -> structure[1][i] = rotated_y;
	}
	//TODO REDEFINE 
}

