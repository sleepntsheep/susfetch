#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <sys/file.h>
#include <pwd.h>

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
	struct sysinfo info;
    s = xmalloc(200);
	sysinfo(&info);
	sec_to_format(info.uptime, s);
    return s;
}

const char *
_memory(void)
{
    /* struct sysinfo si;
    -- sysinfo(&si);
    -- snprintf(s, 200, "%.0f/%.0f MB", (float)(si.totalram-si.freeram)/GB, (float)si.totalram/GB);
	** mem in sysinfo does not include cached mem, hence is inaccurate */
    char *s;
    uintmax_t free, total, buffer, cached;
    FILE *pmif;
    s = xmalloc(200);

    pmif = fopen("/proc/meminfo", "r");
    if (fscanf(pmif,
               "MemTotal: %ju kB\n"
               "MemFree: %ju kB\n"
               "MemAvailable: %ju kB\n"
               "Buffers: %ju kB\n"
               "Cached: %ju kB\n",
               &total, &free, &buffer, &buffer, &cached) != 5) {
        return NULL;
    }
    fclose(pmif);
    snprintf(s, 200, "%.1lf/%.1lf GB", (total - free - buffer - cached)/GB, total/GB);
    return s;
}


