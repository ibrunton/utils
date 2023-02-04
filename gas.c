/*
 *        Project:  gas
 *       Filename:  main.c
 *
 *    Description:  Keeps track of gas purchases.
 *
 *        Version:  0.3
 *        Created:  2015-07-08 13:25
 *        Updated:	2023-02-02
 *       Compiler:  gcc
 *
 *         Author:  Ian D. Brunton (idb), iandbrunton at gmail .com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define VERSION "0.1b"
#define APPNAME "gas"

void
print_version ()
{
	printf ("%s %s\n", APPNAME, VERSION);
}

void
print_usage ()
{
	printf ("%s -l LITRES -k ODOMETER READING -r RATE PER LITRE -p TOTAL PAID -d DISTANCE TO EMPTY [-e PETRO POINTS]\n", APPNAME);
}

int
main (int argc, char *argv[])
{
	int i, kms, dte, card, points = 0;
	float litres, rate, payment;
	char date[11];
	char cardcall[16];
	time_t time_raw;
	FILE *fp;

	char *file = "/home/ian/Dropbox/docs/gas";

	if (argc < 2) {
		print_usage ();
		return EXIT_FAILURE;
	}

	for (i = 1; i < argc; ++i) {
		switch (argv[i][1]) {
			case 'h':
				print_usage ();
				return EXIT_FAILURE;
				break;
			case 'v':
				print_version ();
				return EXIT_SUCCESS;
				break;
			case 'l':
				sscanf (argv[++i], "%f", &litres);
				break;
			case 'k':
				sscanf (argv[++i], "%d", &kms);
				break;
			case 'r':
				sscanf (argv[++i], "%f", &rate);
				break;
			case 'p':
				sscanf (argv[++i], "%f", &payment);
				break;
			case 'd':
				sscanf (argv[++i], "%d", &dte);
				break;
			case 'c':
				card = 1;
				break;
			default:
				print_usage ();
				return EXIT_FAILURE;
				break;
		}
	}

	struct tm * time_struct;
	time (&time_raw);
	time_struct = localtime (&time_raw);
	strftime (date, 11, "%Y-%m-%d", time_struct);

	if ((fp = fopen (file, "a")) == 0) {
		perror ("Error opening file");
		return EXIT_FAILURE;
	}
	else {
		fprintf (fp, "%s\t%d\t%.3f\t@ %.3f\t\t$ %.2f\t%d\t%d\n", date, kms, litres, rate, payment, points, dte);
	}
	fclose (fp);

	if (card == 1) {
		sprintf (cardcall, "ccard %f\n", payment);
		system (cardcall);
	}

	return EXIT_SUCCESS;
}
