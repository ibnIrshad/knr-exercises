#include <stdio.h>
#include <ctype.h>

/* The C Programming Language: 2nd Edition
 *
 * Exercise 5-1: As written, getint treats a + or - not followed by a digit as
 * a valid representation of zero. Fix it to push such a character back on the
 * input.
 */

#define BUFSIZE 100

int getch(void);
void ungetch(int);
int getint(int *);

char buf[BUFSIZE];
int bufp = 0;

int main() {
	int foo;
	int *bar = &foo;
	while (getint(bar) > 0) {
		printf("%d\n", foo);
	}
	return 0;
}

int getint(int *pn) {
	int c, sign;

	while (isspace(c = getch())) {
	}
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
	}
	if (!isdigit(c)) {
		ungetch(c);
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getch()) {
		*pn = 10 * *pn + (c - '0');
	}
	*pn *= sign;
	if (c != EOF) {
		ungetch(c);
	}
	return c;
}

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("ungetch: Too many characters.\n");
	} else {
		buf[bufp++] = c;
	}
}
