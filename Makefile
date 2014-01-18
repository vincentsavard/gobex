CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99

all: obj/gobex.o obj/extract.o obj/file.o
	$(CC) $(CFLAGS) obj/gobex.o obj/extract.o obj/file.o -o bin/gobex

obj/gobex.o: src/gobex.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/extract.o: src/extract.c src/extract.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/file.o: src/file.c src/file.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj/* bin/*
