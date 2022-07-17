#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

#include "susfetch.h"
#include "util.h"
#include "config.h"

#define VERSION "0.2.1"

char *argv0;

void
usage()
{
    fprintf(stdout, "%s [-h] [-v] [-s] [-c yellow]\nsusfetch "VERSION" developed by sleepntsheep", argv0);
    exit(EXIT_SUCCESS);
}

int
main(int argc, char *argv[])
{
    int ci, i, j, opt;
    bool smol = false;
    char colors[3][13] = { BRST, BRED, BGRY };

    argv0 = *argv;

    while((opt = getopt(argc, argv, "hvsc:")) != -1) {
        switch (opt) {
            case 'h':
            case 'v':
                usage();
                break;
            case 'c':
                for (i = 0; i < LENGTH(colorss); i++)
                    if (!strcmp(optarg, colorss[i][0]))
                        strcpy(colors[1], colorss[i][1]);
                break;
            case 's':
                smol = true;
                break;
            default:
                break;
        }
    }

    /* print */
    fputc('\n', stdout);
    for (i = 0; i < MAX(HEIGHT, LENGTH(fetch)); i++) {
        fputs("  ", stdout);
        for (j = 0; j < WIDTH; j++)
            if (i >= HEIGHT)
                fputs("  ", stdout);
            else if ((ci = (smol ? smolamogus[i][j] : amogus[i][j])) >= 0)
                fprintf(stdout, "%s  ", colors[ci]);
        fprintf(stdout, "%s   %8s: %s\n", BRST, fetch[i].name, fetch[i].fnc());
    }
    fputc('\n', stdout);

    return 0;
}

