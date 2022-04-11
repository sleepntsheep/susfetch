#ifndef SUSFETCH_H

#define BWTE "\x1B[48;5;231m"
#define BGRY "\x1B[48;5;251m"
#define BRED "\x1B[48;5;196m"
#define BRST "\x1B[49m"
#define BYLW "\x1B[48;5;220m"
#define BPNK "\x1B[48;5;212m"
#define BBLE "\x1B[48;5;20m"
#define BGRN "\x1B[48;5;208m"
#define BBLK "\x1B[48;5;232m"

const char amogus[6][5] = {
	{0, 1, 1, 1, 0},
	{1, 1, 2, 2, 2},
	{1, 1, 2, 2, 2},
	{1, 1, 1, 1, 0},
	{0, 1, 1, 1, 0},
	{0, 1, 0, 1, 0},
};

const char smolamogus[6][5] = {
	{0, 1, 1, 1, 0},
	{1, 1, 2, 2, 0},
	{1, 1, 1, 1, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
};

void sec_to_format(unsigned int sec, char *buf);

#endif
