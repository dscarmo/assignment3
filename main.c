/*
 * Assignment 3, CMPUT 201, FALL 2015
 * 
 * Student Name: Diedre Santos do Carmo
 * Student ID: 1484008
 * 
 * 
 * Has main function of the program, curse and sketchpad stuff
 */

//#define _XOPEN_SOURCE
#include "main.h"



int main(int argc, char * argv[])
{
	iArgs input;
	FILE *sketch;
	int checkInput;
	
	if (argc != 7){
		printf("Incorrect number of arguments.\nExample: \"./main -g 9.8 -t -20 -f landscape.txt\"\n");
		exit(EXIT_FAILURE);
	}
	
	//Read input and fill gravity, thrust, map
	input.gravity = atof(argv[2]);
	input.thrust = atof(argv[4]);
	input.map = fopen(argv[6], "r");
	
	for (checkInput = 0; checkInput < 7; checkInput++){
		if (argv[checkInput] == NULL){
			printf("Error reading input arguments, exiting.\n");
			exit(EXIT_FAILURE);
		}
	}
	
	//Debug
	printf("gravity: %f thrust: %f\n", input.gravity, input.thrust);
	sleep(1);
	//
			
	
	//Open pipe to sketchpad and start program
  	sketch = popen(exec_name, "w");
  	if (sketch == NULL){
    		fprintf(stderr, "Could not open pipe %s\n", exec_name);
   		exit(EXIT_FAILURE);
 	}
	else{
		startCurse(sketch, input);
		fclose(input.map);
		pclose(sketch);
		exit(EXIT_SUCCESS);
	}		
}

