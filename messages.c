/*
 *        Project:  utils
 *       Filename:  message_v2.c
 *
 *    Description:  
 *
 *        Version:  0.1a
 *        Created:  2024-06-03 13:02
 *       Compiler:  gcc
 *
 *         Author:  Ian D. Brunton (idb), iandbrunton at gmail .com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct messageItem {
	char text[32];
} messageItem;

int main (int argc, char *argv[]) {
	FILE *fp;
	char file[] = "/home/ian/.local/share/messages";
	char *lineBuffer = NULL;
	size_t lineBufferSize = 0;
	ssize_t lineSize;
	int lineCount = 0;
	int i;
	messageItem *lines;

	if ((fp = fopen (file, "r")) == NULL) {
	}
	else {
		lineSize = getline (&lineBuffer, &lineBufferSize, fp);

		lines = (messageItem*) malloc (32);

		while (lineSize >= 0) {
			lineCount++;

			lines = (messageItem*) realloc(lines, lineCount*32);

			/*sscanf (lineBuffer, "%s", &lines[lineCount-1]);*/
			strncpy (lines[lineCount-1].text, lineBuffer, 32);

			lineSize = getline (&lineBuffer, &lineBufferSize, fp);
		}

		free (lineBuffer);
		lineBuffer = NULL;
		fclose (fp);
	}

	if (argc > 1) {
		if (strncmp (argv[1], "clear\0", 6) == 0) {
			printf ("%s\n", "Clear!");
			/* Remove last line and write file */
			if ((fp = fopen (file, "w")) == NULL) {
			}
			else {
				i = 0;
				while (i < lineCount-1) {
					fprintf (fp, lines[i].text);
					++i;
				}

				fclose (fp);
			}
		}
		else {
			/* Add all input to end of file, with newline */
			for (i = 1; i < argc; i++) {
				...
			}
		}
	}
	else {
		/* No input: output last line of file */

		printf ("%s", lines[lineCount-1]);
	}

	return EXIT_SUCCESS;
}
