CC = gcc
CFLAGS = -Wall 
F = clonevfork
SRC = clonevfork.c


all: $(F)

$(F): $(SRC) 
	$(CC) $(CFLAGS) -o $(F) $(SRC)
	./$(F) 

clean:
	$(RM) $(F)