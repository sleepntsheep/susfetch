#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

void
die(const char *fmt, ...)
{
    va_list ag;
    va_start(ag, fmt);
    vfprintf(stderr, fmt, ag);
    va_end(ag);
    fputc('\n', stderr);
    exit(1);
}

void *
xmalloc(size_t size)
{
    void *a;
    if (!(a = malloc(size)))
        die("xmalloc: size = %lu", size);
    return a;
}

