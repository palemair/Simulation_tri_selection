CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic -std=c11 -fno-common -fno-builtin
LDFLAGS = -lSDL2 -lSDL2_ttf
EXEC= selection
TESTS= tests/
OBJ= obj/
SRC= src/
INC= include/

all: $(EXEC)

selection : $(OBJ)main.o $(OBJ)colors.o $(OBJ)tstack.o $(OBJ)xalloc.o $(OBJ)drawing.o $(OBJ)init_0.o

	$(CC) -o $@ $^ $(LDFLAGS)

graph_test : $(TESTS)graphics.o $(OBJ)colors.o $(OBJ)tstack.o $(OBJ)xalloc.o $(OBJ)drawing.o $(OBJ)init_0.o 

	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ)main.o : main.c
	$(CC) -I$(INC) -o $@ -c $^ $(LDFLAGS) $(CFLAGS)

$(OBJ)%.o: $(SRC)%.c
	$(CC) -o $@ -c $^ -I$(INC) $(LDFLAGS) $(CFLAGS)

$(TESTS)graphics.o: $(TESTS)graphics.c
	$(CC) -o $@ -c $^ -I$(INC) $(LDFLAGS) $(CFLAGS)

.PHONY : clean

clean:
	rm -rf $(OBJ)*.o
