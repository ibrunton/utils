/*
 *        Project:  utils
 *       Filename:  bvgas.c
 *
 *    Description:  Calculate cost of driving to crossfit gym
 *    				based on per-litre cost of last gas purchase
 *
 *        Version:  0.1a
 *        Created:  2024-08-31 18:54
 *       Compiler:  gcc
 *
 *         Author:  Ian D. Brunton (idb), iandbrunton at gmail .com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main (int argc, char *argv[]) {
	/* distance */
	float km_in = 85;
	float km_out = 80;
	/* litres of gas per 100km */
	float lkm_in;
	float lkm_out;
	/* most recent cost per litre of gas */
	float rate;

	/* outputs */
	float price_in;
	float price_out;
	float total;

	FILE *fp;
	char *file = "/home/ian/Dropbox/docs/lastgasprice";
	char system_call[32];

	/* get rates of trips */
	if (argc > 1) {
		/* assumes 85km out and 80km in */
		sscanf (argv[1], "%f", &lkm_in);
		sscanf (argv[2], "%f", &lkm_out);
	}
	else {
		printf ("Distance in: ");
		scanf ("%f", &km_in);
		printf ("Distance out: ");
		scanf ("%f", &km_out);
		printf ("L/100km in: ");
		scanf ("%f", &lkm_in);
		printf ("L/100km out: ");
		scanf ("%f", &lkm_out);
	}

	/* get gas price from file */
	if ((fp = fopen (file, "r")) == 0) {
		perror ("Error opening file");
		return EXIT_FAILURE;
	}
	else {
		char line[16];
		while (fgets (line, 16, fp) != NULL) {
			sscanf (line, "%f", &rate);
		}
	}
	fclose (fp);

	/* calculations */
	price_in = (km_in/100) * lkm_in * rate;
	price_out = (km_out/100) * lkm_out * rate;
	total = price_in + price_out;

	sprintf (system_call,
			"llg -Tt Gas: 85km @ %.1f = %.2f + 80km @ %.1f = %.2f = %.2f",
			lkm_in, price_in, lkm_out, price_out, total);
	system (system_call);

	return EXIT_SUCCESS;
}
