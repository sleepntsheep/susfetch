#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <sys/file.h>
#include <pwd.h>
#include <limits.h>

#include "util.h"

#define KB 1024.0
#define GB (KB*KB)

static inline void
sec_to_format(unsigned int n, char *buf) {
    sprintf(buf, "%uh %um %us", n/3600, n%3600/60, n%60);
}

const char *
_username(void)
{
    char *s, *s2;
    s = xmalloc(LOGIN_NAME_MAX + 1);
	if (getlogin_r(s, LOGIN_NAME_MAX) != 0)
    {
        /* getlogin_r unsuccessful, get user from $USER */
        if ((s2 = getenv("USER")))
            strncpy(s, s2, LOGIN_NAME_MAX);
    }
    return s;
}

const char *
_hostname(void)
{
    char *s, *s2;
    s = xmalloc(HOST_NAME_MAX + 1);
    if (gethostname(s, HOST_NAME_MAX) == -1)
    {
        int fd;
        fd = open("/proc/sys/kernel/hostname", O_RDONLY);
        read(fd, s, HOST_NAME_MAX);
        close(fd);
        if ((s2 = strchr(s, '\n')))
            *s2 = 0;
    }
    return s;
}

const char *
_release(void)
{
    struct utsname *ver;
    ver = xmalloc(sizeof(struct utsname));
    uname(ver);
    return ver->release;
}

const char *
_shell(void)
{
    return getenv("SHELL");
}

const char *
_uptime(void)
{
    char *s;
    s = xmalloc(200);
	struct sysinfo info;
	sysinfo(&info);
	sec_to_format(info.uptime, s);
    return s;
}

const char *
_memory(void)
{
    char *s;
    struct sysinfo si;
    s = xmalloc(200);
    sysinfo(&si);
    snprintf(s, 200, "%.0f/%.0f MB", (float)(si.totalram-si.freeram)/GB, (float)si.totalram/GB);
    return s;
/*
	 mem 
	-- mem in sysinfo does not include cached mem, hence is inaccurate
	
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
	double usedmemGB = (double)usedmem / GB;*/
}


