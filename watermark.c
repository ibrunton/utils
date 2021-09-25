/*
 *       Filename:  main.c
 *
 *    Description:  to keep track of water consumption
 *
 *        Version:  2.0
 *        Created:  2011-10-03 13:11
 *       Compiler:  gcc
 *
 *         Author:  Ian D Brunton (ib), iandbrunton@gmail.com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

void print_version ();

int
main (int argc, char *argv[])
{
	int echo = 0;
	int i;
	float litres = 0;
	float transaction = 0;
	char date_str [9];
	char file_date [9];
	char *l_str;

	time_t time_raw_format;
	struct tm * time_struct;
	time (&time_raw_format);
	time_struct = localtime (&time_raw_format);
	strftime (date_str, 9, "%Y%m%d", time_struct);

	char *home = getenv ("HOME");
	char *file = "/.local/share/wm";
	size_t len1 = strlen (home);
	size_t len2 = strlen (file);
	char *wm_file = malloc (len1 + len2 + 2);
	memcpy (wm_file, home, len1);
	memcpy (wm_file + len1, file, len2 + 1);

	FILE *frc;
	if ((frc = fopen (wm_file, "r")) == 0) {
		perror ("Error opening watermark file");
		return EXIT_FAILURE;
	} else {
		char line [80];
		while (fgets (line, 80, frc) != NULL) {
			sscanf (line, "%s %f", &file_date, &litres);
		}
	}
	fclose (frc);

	if (strcmp (date_str, file_date) != 0) {
		litres = 0;
	}

	if (argc > 1) {
		if (strcmp (argv[1], "-v") == 0)
			print_version ();
		else {
			for (i = 1; i < argc; i++) {
				if (strcmp (argv[i], "-e") == 0)
					echo = 1;
				else {
					transaction = strtof (argv[i], NULL);
					litres += transaction;
				}
			}
		}

		if (transaction != 0) {
			if ((frc = fopen (wm_file, "w")) == 0) {
				perror ("Error opening watermark file for writing");
				return EXIT_FAILURE;
			} else {
				fprintf (frc, "%s %.2f\n", date_str, litres);
			}
			fclose (frc);
		}
	}
	else {
		echo = 1;
	}

	if (echo == 1) {
		if (litres > 1 || litres == 0)
			l_str = "litres";
		else
			l_str = "litre";

		printf ("You have drunk %.2f %s of water today.\n", litres, l_str);
	}

	free (wm_file);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void
print_version ()
{
	printf ("%s %s\n", APPNAME, VERSION);
	exit (0);
}
