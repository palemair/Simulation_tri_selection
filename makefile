CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic -std=c11 -fno-common -fno-builtin
LDFLAGS = -lSDL2
EXEC= selection
TESTS= test
OBJ= obj
LIB= lib/
INC= include/

all: $(EXEC)

selection : $(OBJ)/main.o $(OBJ)/sort.o $(OBJ)/colors.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ)/main.o : src/main.c
	$(CC) -I$(INC) -o $@ -c $^ $(LDFLAGS) $(CFLAGS)

$(OBJ)/%.o: src/%.c
	$(CC) -o $@ -c $^ -I$(INC) $(LDFLAGS) $(CFLAGS)

$(OBJ)/%.o: $(LIB)%.c
	$(CC) -o $@ -c $^ -I$(INC) $(LDFLAGS) $(CFLAGS)

.PHONY : clean

clean:
	rm -rf $(OBJ)/*.o
