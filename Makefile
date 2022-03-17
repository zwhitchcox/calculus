CC=gcc

CFLAGS=-I.

.PHONY: debug
debug:
	$(CC) test.c -g -lm
	gdb ./a.out

.PHONY: clean
clean:
	rm -fr build

.PHONY: test
%.test: clean
	mkdir -p build
	$(CC) $(shell ls src/*.h | grep -v test) $(shell ls src/*.c | grep -v test) -o build/$@ src/$@.c -lm
	./build/$@

.PHONY: test
pedmas.debug: clean
	mkdir -p build
	$(CC) $(shell ls src/*.h | grep -v test) $(shell ls src/*.c | grep -v test) -o ./build/pedmas.debug ./src/pedmas.test.c -lm
	gdb -ex run ./build/pedmas.debug