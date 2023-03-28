CC=gcc
CFLAGS=-Wall -Wextra -std=gnu99 -DXDG_RUNTIME_DIR=/run/user/$(id -u)
LDFLAGS=-lSDL2 -lm

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
