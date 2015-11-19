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

void initializeShip (Ship *ship){
	ship -> centerPos[0] = 20;
	ship -> centerPos[1] = 20;
	ship -> structure[0] = malloc(4*sizeof(int));
	ship -> structure[1] = malloc(4*sizeof(int));
	ship -> speed = 0;
}
