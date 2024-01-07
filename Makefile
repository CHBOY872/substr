CC=gcc
CXX=g++

CFLAGS=-Wall -g -ansi
STATIC=

SRCMODULES=substring.c
OBJMODULES=$(SRCMODULES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(STATIC) $< -c -o $@

substring: main.c $(OBJMODULES)
	$(CC) $(CFLAGS) $(STATIC) $^ -o $@

clean:
	rm substring
	rm $(OBJMODULES)

static: CFLAGS+=-static
static: substring 
