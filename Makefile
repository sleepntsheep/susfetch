CC := cc
CFLAGS := -std=c99 -O2

all: susfetch

susfetch: tag.c util.c susfetch.c
	$(CC) $(CFLAGS) $^ -o $@
