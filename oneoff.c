/*
 *        Project:  utils
 *       Filename:  oneoff.c
 *
 *    Description:  returns one-off to-do item when the date matches today
 *
 *        Version:  1.2
 *        Created:  2024-10-19 07:22
 *       Compiler:  gcc
 *
 *         Author:  Ian D. Brunton (idb), iandbrunton at gmail .com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct todoItem {
	char text[32];
	char date[11];
} todoItem;

int main (int argc, char *argv[]) {
	FILE *fp;
	char file[] = "/home/ian/.local/share/oneoffs";
	char *itemBuffer = NULL;
	char date[11];
	char system_call[64];
	char text[32];
	char today[11];
	int itemCount = 0;
	int i;
	size_t itemBufferSize = 0;
	ssize_t itemSize;
	time_t time_raw;
	todoItem *items;

	if (argc == 1) {
		if ((fp = fopen (file, "r")) == NULL) {
			fprintf (stderr, "Cannot open file %s\n", file);
			return EXIT_FAILURE;
		}
		else {
			itemSize = getline (&itemBuffer, &itemBufferSize, fp);

			items = (todoItem*) malloc (43);

			while (itemSize >= 0) {
				itemCount++;

				items = (todoItem*) realloc (items, itemCount*43);

				sscanf (itemBuffer, "%10s:%32[^\n]", &date, &text);
				strncpy (items[itemCount-1].date, date, 11);
				strncpy (items[itemCount-1].text, text, 32);

				itemSize = getline (&itemBuffer, &itemBufferSize, fp);
			}

			free (itemBuffer);
			itemBuffer = NULL;
			fclose (fp);
		}

		struct tm * time_struct;
		time (&time_raw);
		time_struct = localtime (&time_raw);
		strftime (today, 11, "%Y-%m-%d", time_struct);

		for (i = 0; i < itemCount; i++) {
			if ((strcmp (today, items[i].date)) == 0) {
				sprintf (system_call, "/home/ian/bin/messages \"%s\"\n", items[i].text);
				system (system_call);
				return EXIT_SUCCESS;
			}
		}
	}
	else if (argc > 1) {
		if (strncmp (argv[1], "edit\0", 5) == 0) {
			execlp ("vim", "vim", file, NULL);
			return EXIT_SUCCESS;
		}
		else {
			if ((fp = fopen (file, "a")) == NULL) {
				fprintf (stderr, "Cannot open file %s\n", file);
				return EXIT_FAILURE;
			}
			else {
				/* this is very basic, assumes correct input format
 			 	 * yyyy-mm-dd:text
 			 	 */
				fprintf (fp, "%s\n", argv[1]);
				fclose (fp);
			}
		}
	}

	return EXIT_FAILURE;
}
