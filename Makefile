CC=gcc

.PHONY: test
test:
	$(CC) test.c -lm
	./a.out

.PHONY: debug
debug:
	$(CC) test.c -g -lm
	gdb ./a.out