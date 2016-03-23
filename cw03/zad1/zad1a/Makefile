CC = gcc
CFLAGS = -Wall 
F = fork
SRC = forks.c


all: $(F)

$(F): $(SRC) 
	$(CC) $(CFLAGS) -o $(F) $(SRC)
	./$(F) 

clean:
	$(RM) $(F)