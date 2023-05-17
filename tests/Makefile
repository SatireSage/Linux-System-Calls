CC=gcc
CFLAGS=-std=c99 -D _GNU_SOURCE -static

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%)

all: $(OBJS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

send:
	scp -P 9347 $(OBJS) ubuntu@localhost:

clean:
	rm -f $(OBJS)
