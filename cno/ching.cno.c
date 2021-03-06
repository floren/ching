/*
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Guy Harris.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char copyright[] =
"@(#) Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "@(#)ching.cno.c	8.1 (Berkeley) 05/31/93";
#endif /* not lint */

/*
 * cno - Read a question, cast a change, and output the line values to the
 * standard output for processing by "phx".
 */
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "ching.h"

long	now;		/* current time */

unsigned seed;		/* seed for random number generator */
unsigned getrand();

char	*change();
char	string[6+1];	/* where the actual change string is put */

int	table[2][2][2] = {
	{ { OYIN,  YYANG,}, { YYANG, YYIN,} },
	{ { YYANG, YYIN,},  { YYIN,  OYANG,} },
};

/*
 * Hash the question by adding all the characters together.
 */
int
getquest()
{
	int result;
	register int c;

	result = 0;
	while ((c = getchar()) != EOF)
		result += c;
	return(result);
}

/*
 * Get a random number.
 */
unsigned
getrand()
{
	return(seed = (seed*13077) + 6925);
}

/*
 * Get a number more random than what getrand() gives.
 */
unsigned getrnum()
{
	return((getrand())>>(getrand()%17));
}

/*
 * Get a set of six lines making up a change.
 */
char *
change()
{
	register int i;

	for (i = 0; i < 6; i++)
		string[i] = table[getrnum()&01][getrnum()&01][getrnum()&01] + '0';
	string[i] = '\0';
	return(string);
}

int main()
{
	FILE *logf;

	time(&now);
	seed = (int)now + getquest() + getgid() + getuid() + getpid();	/* randomize */
	printf("%s\n", change());
	return(0);
}

