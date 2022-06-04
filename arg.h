#ifndef ARG_H
#define ARG_H

#define ARGBEGIN for (; ++argv && argv[0];) {\
                     if (argv[0][0] != '-' || !argv[0][1]) continue;\
                     switch (argv[0][1])

#define ARGEND }

#define NXARG(x) ((argv[1]) ?\
                  (*(++argv)) : ((x), abort(), NULL))

#endif /* ARG_H */
