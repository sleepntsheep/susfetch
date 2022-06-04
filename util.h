#ifndef UTIL_H
#define UTIL_H

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

void
die(const char *fmt, ...);

void *
xmalloc(size_t size);

#endif
