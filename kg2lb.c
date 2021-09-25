/*
 *        Project:  weight-convert
 *       Filename:  kg2lb.c
 *
 *    Description:  Convert kilograms to pounds
 *
 *        Version:  0.1a
 *        Created:  2018-01-21 06:57
 *       Compiler:  gcc
 *
 *         Author:  Ian D. Brunton (idb), iandbrunton at gmail .com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#define FACTOR 2.204

int
main (int argc, char *argv[])
{
	float input, output;
	int i;

	for (i = 1; i < argc; i++) {
		sscanf (argv[i], "%f\n", &input);
		output = input * FACTOR;
		printf ("%.1f\n", output);
	}
	return EXIT_SUCCESS;
}
