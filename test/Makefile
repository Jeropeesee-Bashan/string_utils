CFLAGS = -g -Wall -Wextra -pedantic -std=c89 -I./greatest -I../

.PHONY: all clean

all: test

test: string_utils.o test.o
	${CC} ${CFLAGS} -o $@ $^

string_utils.o: ../string_utils.c
	${CC} -c ${CFLAGS} -o $@ $<

test.o: test.c

clean:
	rm -rf ./test ./test.o ./string_utils.o
