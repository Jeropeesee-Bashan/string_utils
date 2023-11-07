CFLAGS = -g -Wall -Wextra -pedantic -std=c89

.PHONY: default all clean help
.SILENT: help
default: help

all: test
help:
	echo "Available targets:"
	echo "all: build test (same as target \"test\")."
	echo "test: build test."
	echo "clean: remove all build files."
	echo "help: display this message."

test: test.o string_utils.o
	${CC} ${CFLAGS} -o $@ $^
test.o: test.c
string_utils.o: ../string_utils.c
	${CC} -c ${CFLAGS} -o $@ $<

clean:
	rm -rf test test.o string_utils.o
