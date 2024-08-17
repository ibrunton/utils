/*
 *        Project:  utils
 *       Filename:  sr.c
 *
 *    Description:  Daily sleep rating
 *
 *        Version:  2.0
 *        Created:  2024-08-14 14:25
 *       Compiler:  gcc
 *
 *         Author:  Ian D. Brunton (idb), iandbrunton at gmail .com
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int main (int argc, char *argv[]) {
	char system_call[32];
	int rating;

	if (argc > 1) {
		sscanf (argv[1], "%d", &rating);
	}
	else {
		printf ("Sleep rating: ");
		scanf ("%d", &rating);

		/*
		fprintf (stderr, "No integer supplied\n");
		return EXIT_FAILURE;
		*/
	}

	if (rating > MAX) {
		rating = MAX;
	}

	sprintf (system_call, "llg -t Sleep: %d\n", rating);

	system (system_call);
	return EXIT_SUCCESS;
}
