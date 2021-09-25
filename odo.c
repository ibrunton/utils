/*
 *        Project:  odo
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015-06-26 20:20
 *       Compiler:  gcc -o odo main.c
 *
 *         Author:  Ian D. Brunton (idb), iandbrunton at gmail .com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

int
main (int argc, char *argv[])
{
	char date[11];
	int kms;
	FILE *fp;
	time_t time_raw;

	char *file = "/home/ian/Dropbox/docs/odometer";

	if (argc > 1) {
		kms = atof (argv[1]);

		struct tm * time_struct;
		time (&time_raw);
		time_struct = localtime (&time_raw);
		strftime (date, 11, "%Y-%m-%d", time_struct);

		if ((fp = fopen (file, "a")) == 0) {
			perror ("Error opening file");
			return EXIT_FAILURE;
		}
		else {
			fprintf (fp, "%s\t%d\n", date, kms);
		}
		fclose (fp);
	}
	else { /* print odo */
		if ((fp = fopen (file, "r")) == 0) {
			perror ("Error opening file");
			return EXIT_FAILURE;
		}
		else {
			char line[128];
			while (fgets (line, 128, fp) != NULL) {
				sscanf (line, "%*d-%*d-%*d\t%d", &kms);
			}
		}
		fclose (fp);
		printf ("%d\n", kms);

	}

	return EXIT_SUCCESS;
}
