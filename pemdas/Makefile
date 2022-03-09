CC=gcc

CFLAGS=-I.

.PHONY: debug
debug:
	$(CC) test.c -g -lm
	gdb ./a.out

.PHONY: test
%.test: $(OBJ)
	$(CC) $(shell ls *.h | grep -v test) $(shell ls *.c | grep -v test) -o $@ $@.c
	./$@
