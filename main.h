/*
 * Assignment 3, CMPUT 201, FALL 2015
 * 
 * Student Name: Diedre Santos do Carmo
 * Student ID: 1484008
 * 
 * 
 * Main things
 */

#include <stdio.h>
#include <stdlib.h>

//Sketchpad name
const char exec_name[] = "java -jar Sketchpad.jar";

typedef struct inputArgs{
	double gravity;
	double thrust;
	FILE *map;
}iArgs;

