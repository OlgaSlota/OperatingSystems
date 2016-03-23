CC = gcc
CFLAGS = -Wall 
F = clonefork
SRC = clonefork.c


all: $(F)

$(F): $(SRC) 
	$(CC) $(CFLAGS) -o $(F) $(SRC)
	./$(F) 

clean:
	$(RM) $(F)