#include <stdio.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 1-16: Revise the main routine of the longest-line program so it
 * will correctly print the length of arbitrarily long input lines, and as
 * much as possible of the text.
 *
 * Answer: The key to arbitrary limits is buffering. Using a buffer allows you
 * to tackle a problem in chunks of memory instead of all at once. It's
 * slightly more complicated, but adds usefulness to a program.
 *
 * This solution follows the spec exactly, by only modifying main(), unlike many
 * other solutions on the internet.
 *
 * Assumptions:
 * 1. "arbitrarily long" is interpreted to mean upto the maximum size of an
 * integer on the given architechture, e.g. 2^32 unsigned on a 32-bit machine.
 * Indeed a string of that size would be larger than 4 gigabytes. It is possible
 * to deal with numbers larger than that, but it involves a great deal of work
 * abstracting away the concept of an integer, similar to dynamically sized
 * arrays.
 *
 * 2. EOF signal (Ctrl-D) must be given on an empty line
 */

/* demonstrate that we can handle lines much greater than this number*/
#define BUFFSIZE 5

int getlinelen(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
main() {
	/* len of current line, max len seen so far, templen of buffer */
	int len, max, templen;
	char buffer[BUFFSIZE];
	max = len = 0;
	while ((templen = getlinelen(buffer, BUFFSIZE)) > 0) {
		len += templen;
		if (buffer[templen - 1] == '\n') {
			if (len > max) {
				max = len;
			}
			len = 0;
		}
	}
	/* The length returned includes the '\n' character. */
	printf("\nLen of longest line: %d\n", max);
	return 0;
}

/* getlinelen: read a line into s, return length */
int getlinelen(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}


/* copy: copy 'from' into 'to'; assume 'to' is big enough */
void copy(char to[], char from[]) {
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0') {
		++i;
	}
}
