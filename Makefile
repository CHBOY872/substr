CC=gcc
CXX=g++

CFLAGS=-Wall -g -ansi
STATIC=

substring: main.c
	$(CC) $(CFLAGS) $(STATIC) $^ -o $@

static: CFLAGS+=-static
static: substring 
