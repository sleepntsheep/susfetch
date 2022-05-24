#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <limits.h>
#include "susfetch.h"

#define KB 1024.0
#define GB (KB*KB)

int main(int argc, char *argv[]) {
	bool smol = false;
	char colors[3][12] = { BRST, BRED, BGRY };
	char colorss[][2][12] = {
		{"yellow", BYLW}, {"pink", BPNK}, {"blue", BBLE}, {"green", BGRN}
	};
	
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--color") == 0 && argc > i+1) {
			for (int j = 0; j < LENGTH(colorss); j++) {
				if (strcmp(argv[i+1], colorss[j][0]) == 0) {
					strncpy(colors[1], colorss[j][1], 12);
					break;
				}
			}
		} else if (strcmp(argv[i], "--smol") == 0) {
			smol = true;
		}
	}

	/* hostname */
	char hostname[HOST_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);

	/* username */
	char username[LOGIN_NAME_MAX] = "";
	if (getlogin_r(username, LOGIN_NAME_MAX) != 0) {
		strncpy(username, getenv("USER"), LOGIN_NAME_MAX);
	}

	/* nix name */
	struct utsname ver;
	uname(&ver);

	/* shellname */
	char *shellname;
	shellname = getenv("SHELL");
	if (shellname == NULL) {
		shellname = "";
	}

	/* uptime */
	struct sysinfo info;
	sysinfo(&info);
	char uptime[200] = "";
	sec_to_format(info.uptime, uptime);

	/* mem 
	-- mem in sysinfo does not include cached mem, hence is inaccurate
	*/
	unsigned int totalmem, freemem, cachedmem, buffermem;
	FILE *fp = fopen("/proc/meminfo", "r");
	char memtype[50];
	unsigned int mem;
	while (fscanf(fp, "%s %u kB%*[^\n]", memtype, &mem) != EOF) {
		if (strncmp(memtype, "MemTotal", 8) == 0)
			totalmem = mem;
		else if (strncmp(memtype, "MemFree", 7) == 0)
			freemem = mem;
		else if (strncmp(memtype, "Cached", 6) == 0)
			cachedmem = mem;
		else if (strncmp(memtype, "Buffers", 7) == 0)
			buffermem = mem;
	}
	unsigned int usedmem = totalmem-freemem-cachedmem-buffermem;

    fclose(fp);

	double totalmemGB = (double)totalmem / GB;
	double usedmemGB = (double)usedmem / GB;

	/* format */
	#define LEN 300

	char fname[6][40] = {"usr", "hst", "ker", "mem", "shl", "upt"};
	char fetch[6][LEN];
	strncpy(fetch[0], username, LEN);
	strncpy(fetch[1], hostname, LEN);
	strncpy(fetch[2], ver.release, LEN);
	strncpy(fetch[4], shellname, LEN);
	strncpy(fetch[5], uptime, LEN);
	snprintf(fetch[3], LEN, "%.1lf/%.1lf GB", usedmemGB, totalmemGB);

	/* print */
	printf("\n");
	for (int i = 0; i < 6; i++) {
		printf("  ");
		for (int j = 0; j < 5; j++) {
			int ci = (smol) ? smolamogus[i][j] : amogus[i][j];
			if (ci >= 0) {
				printf("%s", colors[ci]);
				printf("  ");
			}
		}
		printf("%s   %8s: %s\n", BRST, fname[i], fetch[i]);
	}
	printf("\n");

	return 0;
}

void sec_to_format(unsigned int n, char *buf) {
	unsigned int hms[] = {n / 3600, n % 3600 / 60, n % 60};
	char chms[] = "hms";
	for (int i = 0; i < 3; i++) {
		if (hms[i] >= 0) {
			char t[10];
			snprintf(t, 10, "%d%c ", hms[i], chms[i]);
			strncat(buf, t, 10);
		}
	}
}
