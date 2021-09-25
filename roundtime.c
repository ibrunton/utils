/*
 *        Project:  roundtime
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013-6-12 15:02
 *       Compiler:  gcc
 *
 *         Author:  Ian D Brunton (ib), iandbrunton at gmail .com
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (int argc, char *argv[])
{
	char newtime [6];
	int hour, min;

	time_t time_raw_format;
	struct tm * time_struct;

	time (&time_raw_format);
	time_struct = localtime (&time_raw_format);
	strftime (newtime, 6, "%H %M", time_struct);

	sscanf (newtime, "%d %d", &hour, &min);

	switch (min % 5) {
		case 1:
			min -= 1;
			break;
		case 2:
			min -= 2;
			break;
		case 3:
			min += 2;
			break;
		case 4:
			min += 1;
			break;
	}

	if (min == 60) {
		min = 0;
		hour++;
	}

	printf ("%02d%02d", hour, min);

	return EXIT_SUCCESS;
}
