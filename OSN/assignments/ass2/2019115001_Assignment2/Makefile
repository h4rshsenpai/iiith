CC = gcc
CFLAGS = -Iinclude -Wall -g
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: shell

shell: $(OBJ)
	$(CC) $(CFLAGS) -o shell $(OBJ)

clean:
	rm -f src/*.o shell