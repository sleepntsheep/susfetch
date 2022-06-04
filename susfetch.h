#ifndef SUSFETCH_H

#define LENGTH(a) (sizeof (a) / sizeof (*(a)))

#define BWTE "\x1B[48;5;231m"
#define BGRY "\x1B[48;5;251m"
#define BRED "\x1B[48;5;196m"
#define BRST "\x1B[49m"
#define BYLW "\x1B[48;5;220m"
#define BPNK "\x1B[48;5;212m"
#define BBLE "\x1B[48;5;20m"
#define BGRN "\x1B[48;5;208m"
#define BBLK "\x1B[48;5;232m"

#define WIDTH 5
#define HEIGHT 6

const int amogus[HEIGHT][WIDTH] = {
	0, 1, 1, 1, 0,
	1, 1, 2, 2, 2,
	1, 1, 2, 2, 2,
	1, 1, 1, 1, 0,
	0, 1, 1, 1, 0,
	0, 1, 0, 1, 0,
};

const int smolamogus[HEIGHT][WIDTH] = {
	0, 1, 1, 1, 0,
	1, 1, 2, 2, 0,
	1, 1, 1, 1, 0,
	0, 1, 0, 1, 0,
};

static const char colorss[][2][13] = {
    {"yellow", BYLW}, {"pink", BPNK}, {"blue", BBLE}, {"green", BGRN}
};

#endif
