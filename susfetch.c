#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "susfetch.h"
#include "util.h"
#include "config.h"
#include "arg.h"

#define VERSION "0.2"

char *argv0;

void
usage()
{
    fprintf(stdout, "%s [-s | --small] [-c yellow || --color yellow]\nsusfetch "VERSION" developed by sleepntsheep", argv0);
    exit(0);
}

int
main(int argc, char *argv[])
{
    int ci, i, j, smol = 0;
	char colors[3][13] = { BRST, BRED, BGRY };

    argv0 = *argv;

    ARGBEGIN {
        ARGCMP("-c", "--color") {
            char *nx = NXARG(usage());
            for (i = 0; i < LENGTH(colorss); i++)
                if (!strcmp(nx, colorss[i][0]))
                    strcpy(colors[1], colorss[i][1]);
            continue;
        }
        ARGCMP("-s", "--small") {
            smol = 1;
            continue;
        }
        usage();
    } ARGEND

	/* print */
    fputc('\n', stdout);
	for (i = 0; i < MAX(HEIGHT, LENGTH(fetch)); i++) {
        fputs("  ", stdout);
		for (j = 0; j < WIDTH; j++)
            if (i >= HEIGHT)
                fputs("  ", stdout);
            else if ((ci = smol ? smolamogus[i][j] : amogus[i][j]) >= 0)
				fprintf(stdout, "%s  ", colors[ci]);
        fprintf(stdout, "%s   %8s: %s\n", BRST, fetch[i].name, fetch[i].fnc());
	}
    fputc('\n', stdout);

	return 0;
}
