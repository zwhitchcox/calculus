CC=gcc

CFLAGS=-I.

.PHONY: debug
debug:
	$(CC) test.c -g -lm
	gdb ./a.out

.PHONY: clean
clean:
	rm -f *.test

.PHONY: test
%.test: clean
	$(CC) $(shell ls *.h | grep -v test) $(shell ls *.c | grep -v test) -o $@ $@.c -lm
	./$@
