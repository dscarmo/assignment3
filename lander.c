/*
 * Assignment 3, CMPUT 201, FALL 2015
 * 
 * Student Name: Diedre Santos do Carmo
 * Student ID: 1484008
 * 
 * 
 * This and the .h has the game functions, such as drawing stuf and ship data
 */

#include "lander.h"

int rotationBuffer;

void initializeShip (Ship *ship){
	ship -> centerPos[0] = INIT_POS;
	ship -> centerPos[1] = INIT_POS;
	ship -> xspeed = 0;
	ship -> yspeed = 0;
	ship -> xA = 0;
	ship -> yA = 0;
	ship -> rotationAngle = 90;
	ship -> thrustOn = 0;
	
	recreateShip(ship);
}

void recreateShip (Ship *ship){
	double x = ship -> centerPos[0];
	double y = ship -> centerPos[1];
	ship -> rotationAngle = 90;
	
	(ship -> structure)[0][0] = x;
	(ship -> structure)[0][1] = x - SHIP_SIZE;
	(ship -> structure)[0][2] = x + SHIP_SIZE;
	(ship -> structure)[1][0] = y - SHIP_SIZE;
	(ship -> structure)[1][1] = y + SHIP_SIZE;
	(ship -> structure)[1][2] = y + SHIP_SIZE;
	
}

void drawShip(Ship *ship, FILE *sketch){
	//Triangle ship
	fprintf(sketch,"drawSegment %ld %ld %ld %ld\n", 
		lround(ship -> structure[0][0]), lround(ship -> structure[1][0]), lround(ship -> structure[0][1]), lround(ship -> structure[1][1]));
	fprintf(sketch,"drawSegment %ld %ld %ld %ld\n", 
		lround(ship -> structure[0][1]), lround(ship -> structure[1][1]), lround(ship -> structure[0][2]), lround(ship -> structure[1][2]));
	fprintf(sketch,"drawSegment %ld %ld %ld %ld\n", 
		lround(ship -> structure[0][2]), lround(ship -> structure[1][2]), lround(ship -> structure[0][0]), lround(ship -> structure[1][0]));
	fflush(sketch);
}

void eraseShip(Ship *ship, FILE *sketch){	
	fprintf(sketch,"eraseSegment %ld %ld %ld %ld\n", 
		lround(ship -> structure[0][0]), lround(ship -> structure[1][0]), lround(ship -> structure[0][1]), lround(ship -> structure[1][1]));
	fprintf(sketch,"eraseSegment %ld %ld %ld %ld\n", 
		lround(ship -> structure[0][1]), lround(ship -> structure[1][1]), lround(ship -> structure[0][2]), lround(ship -> structure[1][2]));
	fprintf(sketch,"eraseSegment %ld %ld %ld %ld\n", 
		lround(ship -> structure[0][2]), lround(ship -> structure[1][2]), lround(ship -> structure[0][0]), lround(ship -> structure[1][0]));
	fflush(sketch);	
}

void moveShip(Ship *ship, FILE *sketch, int direction){
	eraseShip(ship, sketch);	

	switch(direction){
		//down, left, right, up
		case DOWN:		
			ship -> centerPos[0] += 0;
			ship -> centerPos[1] += 10;
			recreateShip(ship);
			break;
		case LEFT:
			
			rotateShip(ship, -ROT_ANGLE);
			break;
		case RIGHT:

			rotateShip(ship, ROT_ANGLE);
			break;
		case UP:
			ship -> centerPos[0] -= 0;
			ship -> centerPos[1] -= 10;
			recreateShip(ship);
			break; 
	}

	drawShip(ship, sketch);	
}

void applyAccelerations(Ship *ship, iArgs input, FILE *sketch){
	eraseShip(ship, sketch);
	
	double oldX = ship -> centerPos[0];
	double oldY = ship -> centerPos[1];
	
	if (rotationBuffer != ship -> rotationAngle){
		rotationBuffer = ship -> rotationAngle;
	}
	
	double oldxV = ship -> xspeed;
	double oldyV = ship -> yspeed;
	double deltat = 0.05;
	double thrust;
	double ar = rotationBuffer * PI / 180.0;
	
	if (ship -> thrustOn){
		thrust = input.thrust;
	} else {
		thrust = 0;
	}

	ship -> xA = thrust*cos(ar);
	ship -> yA = -(input.gravity) + thrust*sin(ar);
	
	ship -> centerPos[0] = oldX + oldxV*deltat + (1/2)*(ship -> xA)*deltat*deltat;
	ship -> centerPos[1] = oldY + oldyV*deltat + (1/2)*(ship -> yA)*deltat*deltat;
	ship -> xspeed = oldxV - (ship -> xA)*deltat;
	ship -> yspeed = oldyV - (ship -> yA)*deltat;
	
	checkBoundaries(ship);
	recreateShip(ship);
	
	if (rotationBuffer != ship -> rotationAngle){
		rotateShip(ship, rotationBuffer - 90);
	}
	
	drawShip(ship, sketch);
	//
}


int checkCollision(Ship *ship, iArgs input){
	//Compare every line from ship structure with file input
	double shipx[3];
	double shipy[3];
	MapStructure *mapStructure = input.mapStructure;
	int n = mapStructure -> n;
	double *mapx = malloc(n*sizeof(double));
	double *mapy = malloc(n*sizeof(double));
	double dumpResultx = 0;
	double dumpResulty = 0;
	
	int i = 0;
	
	for (i = 0; i < 3; i++){
		shipx[i] = ship -> structure[0][i];
		shipy[i] = ship -> structure[1][i];
		printf("ship points: %lf %lf\n", shipx[i], shipy[i]);
	}
	
	for (i = 0; i < n; i++){
		mapx[i] = (mapStructure -> x)[i];
		mapy[i] = (mapStructure -> y)[i];
		printf("map points: %lf %lf\n", mapx[i], mapy[i]);
	}
	
	//Check collision for all possible lines
	for (i = 0; i < n - 1; i++){
		//line 1
		if (lineSegmentIntersection(shipx[0], shipy[0], shipx[1], shipy[1], 
						 	 mapx[i], mapy[i], mapx[i+1], mapy[i+1], 
						     &dumpResultx, &dumpResulty)) return freeAndQuit(mapx, mapy, 1, dumpResultx, dumpResulty);
		
		//line 2
		else if (lineSegmentIntersection(shipx[1], shipy[1], shipx[2], shipy[2], 
						 		  mapx[i], mapy[i], mapx[i+1], mapy[i+1], 
						 		  &dumpResultx, &dumpResulty)) return freeAndQuit(mapx, mapy, 1, dumpResultx, dumpResulty);
		
		//line 3
		else if (lineSegmentIntersection(shipx[2], shipy[2], shipx[0], shipy[0], 
						 		  mapx[i], mapy[i], mapx[i+1], mapy[i+1], 
						 		  &dumpResultx, &dumpResulty)) return freeAndQuit(mapx, mapy, 1, dumpResultx, dumpResulty);
		
	}
	return freeAndQuit(mapx, mapy, 0, dumpResultx, dumpResulty);
}

int freeAndQuit(double *mapx, double *mapy, int returnValue, double resultx, double resulty){
	if (returnValue) printf("Collision detected in %lf %lf\n", resultx, resulty);
	free(mapx);
	free(mapy);
	return returnValue;
}

void checkBoundaries(Ship *ship){
	int x = ship -> centerPos[0];
	int y = ship -> centerPos[1];
	
	if (x <= 0) 
		x = 10;
	if (y <= 0) 
		y = 10;
	if (x >= 640)
		x = 630;
	if (y >= 480)
		y = 470;
		
	ship -> centerPos[0] = x;
	ship -> centerPos[1] = y;
		
}

void rotateShip(Ship *ship, int angle){
	//Translate to center rotate then translate back
	int i = 0;
	ship -> rotationAngle += angle;
	for (i = 0; i < 3; i++)
	{
		ship -> structure[0][i] = ship -> structure[0][i] - ship -> centerPos[0];
		ship -> structure[1][i] = ship -> structure[1][i] - ship -> centerPos[1];
	}
	
	double ar;
	//if (direction == 1) 
		ar = angle * PI / 180.0;
	//else 
	// 	ar = -angle * PI / 180.0;
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
	
	//Go back
	for (i = 0; i < 3; i++)
	{
		ship -> structure[0][i] = ship -> structure[0][i] + ship -> centerPos[0];
		ship -> structure[1][i] = ship -> structure[1][i] + ship -> centerPos[1];
	}
}

MapStructure *drawLand(FILE* map, FILE *sketch){
	char line[255];
	double x[100];
	double y[100];
	MapStructure *mapStructure = malloc(sizeof(MapStructure));
	int n = 0;
	int i = 0;
	
	for (i = 0; i < 100; i++){
		x[i] = 0;
		y[i] = 0;
	}
	
	//First storage land
	i = 0;
	fgets(line, sizeof(line), map);
	sscanf(line, "%lf %lf", &x[i], &y[i]);
	n++;		
	while(!feof(map)){
		i++;
		fgets(line, sizeof(line), map);
		sscanf(line, "%lf %lf", &x[i], &y[i]);
		n++;
	}
	
	//Copy to structure
	mapStructure -> n = n;
	for (i = 0; i < n; i++){
		(mapStructure -> x)[i] = x[i];
		(mapStructure -> y)[i] = y[i];
	}
	
	
	for (i = 0; i < n - 1; i++){
		fprintf(sketch, "drawSegment %ld %ld %ld %ld\n", lround(x[i]), lround(y[i]), lround(x[i+1]), lround(y[i+1]));
	}
	
	fflush(sketch);
	
	return mapStructure;
}



