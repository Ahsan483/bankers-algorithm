CC = gcc
CFLAGS = -Wall -Wextra -O2 -g

all: bankers

bankers: bankers.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f bankers
