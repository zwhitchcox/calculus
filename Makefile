CC=gcc

CFLAGS=-I.

SHELL=/bin/bash
# .SHELLFLAGS="-O extglob -c"

.PHONY: debug
debug:
	$(CC) test.c -g -lm
	gdb ./a.out

.PHONY: clean
clean:
	rm -fr build

.PHONY: test
term.test: clean
	mkdir -p build
	@echo $(shell 'ls src/{term,common,term}.{c,h}'')
	$(CC) -o build/$@ $(shell ls src/{term,common,term}.{c,h}) src/$@.c -lm
	./build/$@

.PHONY: test
%.test: clean
	mkdir -p build
	$(CC) $(shell ls src/*.h | grep -v test) $(shell ls src/*.c | grep -v test) -o build/$@ src/$@.c -lm
	./build/$@


.PHONY: test
pemdas.debug: clean
	mkdir -p build
	$(CC) $(shell ls src/*.h | grep -v test) $(shell ls src/*.c | grep -v test) -o ./build/pemdas.debug ./src/pemdas.test.c -lm
	gdb -ex run ./build/pemdas.debug