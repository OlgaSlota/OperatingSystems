CC = gcc
CFLAGS = -Wall 
F = vfork
SRC = vforks.c


all: $(F)

$(F): $(SRC) 
	$(CC) $(CFLAGS) -o $(F) $(SRC)
	./$(F) 

clean:
	$(RM) $(F)