CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic -std=c11 -fno-common -fno-builtin
LDFLAGS = -lSDL2
EXEC= selection
TESTS= test

all: $(EXEC)

test : test-01.o sort.o
	$(CC) -o $@ $^

test-01.o : tests/test-01.c
	$(CC) -o $@ -c $<

sort.o : src/sort.c
	$(CC) -c $< -c $<

colors.o : src/colors.c
	$(CC) -c $< -c $<

selection : main.o sort.o colors.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: src/%.c
	$(CC) -c $^ $(CFLAGS)

.PHONY : clean

clean:
	rm -rf *.o
	rm -rf $(TESTS)
