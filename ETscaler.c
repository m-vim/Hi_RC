//ETscaler.c
/*This program generates "equal termperament" musical scale values. It allows the user to create 
scales with any number of notes to the octave, as opposed to the classical 12-note chromatic scale.
Converstion to-and-from raw frequency to MIDI values is offered.
Writing this program helped improve my understanding of parsing command line arguements with pointers :) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*usage: ETscaler [-m] [-i] N startval
	where: 
	-m means: interpret startval as a MIDI note
	(default: interpret frequency in hertz)
	-i means: print interval ratios as well as frequency values
	(default: print only frequency ratios) */

int main(int argc, char*argv[]) {					//passes command line arguement to main

	int notes, i;							//declare top level variables
	int ismidi = 0;
	int write_interval = 0;
	double startval, basefreq, ratio;
	double intervals[25];
	char flag;

	// check first arguement for flag options -m or -i. argc will be at least 2 
	while (argc > 1) {
		if (argv[1][0] == '-') {				//detect dash signaller for optional arguements
			flag = argv[1][1];
			if (flag == 'm')
				ismidi = 1;
			else if (flag == 'i')
				write_interval = 1;
			else {
				printf("Error: Unrecognized Option %s \n", argv[1]);
				return 1;
			}
			argc--;
			argv++;
		}
		else
			break;						//loop break indicates all optional flags, if any, have been read
	}

	if (argc < 3) {							 //display error message and reiterate usage
		printf("Error: this program takes at least 2 arguments\n");
		printf("Usage: ETscaler [-m][-i] N startval\n");
		printf("[-m] is midi; [-i] is display interval\n");
		return 1;
	}

	// We now expect argv[1] to hold N and argv[2] to hold startval
	// test for reasonableness of startval
	notes = atoi(argv[1]);
	if (notes < 1 || notes > 24) {					//program supports a maximum of 24 notes per scale
		printf("Error: N out of range. Must be between 1 and 24\n");
		return 1;
	}

	startval = atof(argv[2]);

	if (ismidi){
		if (startval > 127.0) {					//MIDI values are from 0 to 127
			printf("Error: MIDI startval must be <= 127\n");
			return 1;
		}
		if (startval < 0.0) {					//MIDI values must be positive
			printf("Error: MIDI startval must be >= 0\n");
			return 1;
		}
	}
	else {
		if (startval <= 0.0) {					//frequency must be positive
			printf("Error: frequency startval must be positive\n");
			return 1;
		}
	}

	//all parameters ready - perform math functions to calculate scale and fill array
	if (ismidi) {
	//find base frequency, if value is MIDI
		double c0, c5;													
		ratio = pow(2.0, 1.0 / 12.0);				
		c5 = 220.0 * pow(ratio, 3);
		c0 = c5 * pow(0.5, 4);
		basefreq = c0 * pow(ratio, startval);
	}
	else {
		basefreq = startval;
	}
  
	//calculate ratio from notes, and fill the array
	ratio = pow(2.0, 1.0 / notes);
	for (i = 0; i <= notes; i++) {
		intervals[i] = basefreq;
		basefreq *= ratio;
	}
  
	//finally, read array and write to screen
	for (i = 0; i <= notes; i++) {
		if (write_interval)
			printf("%d:\t%f\t%f\n", i, pow(ratio,i), intervals[i]);
		else
			printf("%d:\t%f\n", i, intervals[i]);
	}

	return 0;
}
