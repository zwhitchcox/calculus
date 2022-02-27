CC=gcc

.PHONY: test
test:
	$(CC) test.c -lm
	./a.out