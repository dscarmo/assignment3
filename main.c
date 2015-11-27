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
	
	//Read input and fill gravity, thrust, map
	if (argv[1] != NULL)
	{
		input.map = fopen(argv[1], "r");
		
		if(input.map == NULL)
		{
			printf( "Error opening file %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}
				
	} else {
		printf("No Input file, exiting program.\n");
		exit(EXIT_FAILURE);
	}
	
	//Open pipe to sketchpad
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

