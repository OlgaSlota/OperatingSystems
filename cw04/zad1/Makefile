CC = gcc
CFLAGS = -Wall 
PR = printer
SRC = printer.c


all: $(PR) run

$(PR): $(SRC) 
	$(CC) $(CFLAGS) -o $(PR) $(SRC)

clean:
	$(RM) $(PR)