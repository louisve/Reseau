CC=gcc
CFLAGS=-Wall -Wextra -std=gnu99
LDFLAGS=-lSDL2

SRC=Client.c ../pixel.c affichage.c
OBJ=$(SRC:.c=.o)
EXEC=client

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
