CC = gcc
CFLAGS = -Wall 
F = main
SRC = main.c


all: $(F)

$(F): $(SRC) 
	$(CC) $(CFLAGS) -o $(F) $(SRC)
	./$(F) ..

clean:
	$(RM) $(F)