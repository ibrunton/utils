/*
 *        Project:  temperature-convert
 *       Filename:  c2f.c
 *
 *    Description:  Convert given temperature from Celcius to Fahrenheit.
 *
 *        Version:  0.1a
 *        Created:  2016-12-17 08:46
 *       Compiler:  gcc
 *
 *         Author:  Ian D. Brunton (idb), iandbrunton at gmail .com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#define FACTOR (9.0/5.0)

int
main (int argc, char *argv[])
{
	float input, output;

	sscanf (argv[1], "%f", &input);
	output = (input * FACTOR) + 32;
	printf ("%.1f\n", output);

	return EXIT_SUCCESS;
}
