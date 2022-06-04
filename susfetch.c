#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "susfetch.h"
#include "util.h"
#include "config.h"
#include "arg.h"

#define VERSION "0.2"

char *argv0;

void
usage()
{
    fprintf(stdout, "%s [-s] [-c yellow]\nsusfetch "VERSION" developed by sleepntsheep", argv0);
    exit(0);
}

int main(int argc, char *argv[])
{
    int ci, i, j;
    bool smol = false;
    argv0 = *argv;

    char *user, *host, *shell, *release, *uptime, *memory;
	char colors[3][12] = { BRST, BRED, BGRY };
	char colorss[][2][12] = {
		{"yellow", BYLW}, {"pink", BPNK}, {"blue", BBLE}, {"green", BGRN}
	};
	
    ARGBEGIN {
        case 'c': {
            char *nx = NXARG(usage());
            for (i = 0; i < LENGTH(colorss); i++)
                if (!strcmp(nx, colorss[i][0]))
                    strncpy(colors[1], colorss[i][1], 12);
            break;
                  }
        case 's':
            smol = true;
            break;
        default:;
            usage();
            break;
    } ARGEND

	/* print */
	printf("\n");
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
