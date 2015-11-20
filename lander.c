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
#define SHIP_SIZE 10
#define INIT_POS 50
#define PI 3.14159265358979323846

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
	(ship -> structure)[1][0] = y - SHIP_SIZE;
	(ship -> structure)[1][1] = y + SHIP_SIZE;
	(ship -> structure)[1][2] = y + SHIP_SIZE;
	
}

void adjust(Ship *ship, int i){
	//Stupid zeroing
	(ship -> structure)[0][0] = (ship -> structure)[0][0];
	(ship -> structure)[0][1] = (ship -> structure)[0][1] - i;
	(ship -> structure)[0][2] = (ship -> structure)[0][2] + i;
	(ship -> structure)[1][0] = (ship -> structure)[1][0] - i;
	(ship -> structure)[1][1] = (ship -> structure)[1][1] + i;
	(ship -> structure)[1][2] = (ship -> structure)[1][2] + i;
}

void drawShip(Ship *ship, FILE *sketch){
	//Triangle ship
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
			recreateShip(ship);
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
			recreateShip(ship);
			break; 
	}

	drawShip(ship, sketch);	
}


void rotateShip(Ship *ship, int direction){
	//TODO WHY IS IT SHRINKING?
	//Translate to center rotate then translate back
	int i = 0;
	
	for (i = 0; i < 3; i++)
	{
		ship -> structure[0][i] = ship -> structure[0][i] - ship -> centerPos[0];
		ship -> structure[1][i] = ship -> structure[1][i] - ship -> centerPos[1];
	}
	
	double ar;
	if (direction == 1) 
		ar = ROT_ANGLE * PI / 180.0;
	else 
	 	ar = -ROT_ANGLE * PI / 180.0;
	double rotated_x, rotated_y;
	double x, y;

	for (i = 0; i < 3; i++)
	{
		x = (double)ship -> structure[0][i];
		y = (double)ship -> structure[1][i];
		rotated_x = x*cos(ar) - y*sin(ar);
		rotated_y = x*sin(ar) + y*cos(ar);		
		ship -> structure[0][i] = (int)rotated_x;
		ship -> structure[1][i] = (int)rotated_y;
	}
	
	//Go back
	for (i = 0; i < 3; i++)
	{
		ship -> structure[0][i] = ship -> structure[0][i] + ship -> centerPos[0];
		ship -> structure[1][i] = ship -> structure[1][i] + ship -> centerPos[1];
	}
}

void drawLand(FILE* map, FILE *sketch){
	char line[255];
	int x1, y1;
	int x2, y2;
	
	//First line	
	fgets(line, sizeof(line), map);
	sscanf(line, "%d %d", &x1, &y1);
			
	while(!feof(map)){
		fgets(line, sizeof(line), map);
		
		sscanf(line, "%d %d", &x2, &y2);
		
		fprintf(sketch, "drawSegment %d %d %d %d\n", x1, y1, x2, y2);
		
		x1 = x2;
		y1 = y2;
	
	}
	fflush(sketch);
}



