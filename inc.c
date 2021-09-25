/*
 *        Project:  inc
 *       Filename:  main.c
 *
 *    Description:  Increments the number stored in a file.
 *    				File name is required.
 *    				Optionally, the amount to be added.
 *    				Two arguments can be in either order.
 *
 *        Version:  0.2
 *        Created:  2021-09-17
 *       Compiler:  gcc
 *
 *         Author:  Ian D. Brunton (idb), iandbrunton at gmail .com
 *
 */

#include <stdio.h>
#include <stdlib.h>

int isNumber (char number[]) {
	int i = 0;

	/* Allow for negative numbers */
	if (number[0] == '-') {
		i = 1;
	}

	for (; number[i] != 0; i++) {
		if (number[i] <48 || number[i] >57) {
			return 1;
		}
	}
	return 0;
}

int main (int argc, char *argv[]) {
	int i;
	int n = 1;
	int num;
	char *file;
	FILE *fp;

	if (argc < 1) {
		fprintf (stderr, "No file specified.\n");
		return EXIT_FAILURE;
	}

	for (i = 0; i < argc; i++) {
		if (isNumber (argv[i]) == 0) {
			n = atoi(argv[i]);
			/* printf ("%d is a number\n", n); */
		}
		else {
			file = argv[i];
			/* printf ("%s is not a number\n", file); */
		}
	}

	if ((fp = fopen (file, "r")) == 0) {
		fprintf (stderr, "Error opening file %s.\n", file);
	}
	else {
		char line [16];
		while (fgets (line, 16, fp) != NULL) {
			sscanf (line, "%d", &num);
		}
	}
	fclose (fp);

	num += n;
	printf ("%d\n", num);

	if ((fp = fopen (file, "w")) == 0) {
		fprintf (stderr, "Error opening file %s.\n", file);
		return EXIT_FAILURE;
	}
	else {
		fprintf (fp, "%d\n", num);
	}
	fclose (fp);


	return EXIT_SUCCESS;
}

