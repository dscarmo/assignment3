/*
 * Assignment 3, CMPUT 201, FALL 2015
 * 
 * Student Name: Diedre Santos do Carmo
 * Student ID: 1484008
 * 
 * 
 * Has main function of the program, curse and sketchpad stuff
 */
#include "main.h"

//Pipe things
const char exec_name[] = "java -jar Sketchpad.jar";

int main(int argc, char * argv[])
{
	FILE *input;
	FILE *executable;
	
	//Start message
	startUp(argv[0]);
		
	//TODO handle gravity, trust and map inputs
	if (argv[1] != NULL)
	{
		printf("Input file: %s\n", argv[1]);
		input = fopen(argv[1], "r");
		
		if(input == NULL)
		{
			printf( "Error opening file %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}
				
	} else {
		printf("No Input file, exiting program.\n");
		exit(EXIT_FAILURE);
	}
	
	//Open pipe to sketchpad
  	executable = popen(exec_name, "w");
  	if (executable == NULL){
    		fprintf(stderr, "Could not open pipe %s\n", exec_name);
   		exit(EXIT_FAILURE);
 	}
	else{
		//Call main code
		//execute(input, executable);	
		
		fclose(input);
		pclose(executable);
		exit(EXIT_SUCCESS);
	}
	
}
