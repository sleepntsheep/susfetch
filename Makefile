CC := cc
CFLAGS := -std=c99 -O2
DEST := /usr/local/bin

all: susfetch

install: susfetch
	sudo install -m755 $< $(DEST)

susfetch: tag.c util.c susfetch.c
	$(CC) $(CFLAGS) $^ -o $@
