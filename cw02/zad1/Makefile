CC = gcc
CFLAGS = -Wall 
GEN = gen 
SORT = sort
SRCS = sort.c
SRCG = generator.c


all: $(SORT) $(GEN) plik plik1

$(SORT): $(SRCS) plik plik1
	$(CC) $(CFLAGS) -o $(SORT) $(SRCS)
	./$(SORT) plik 8192 lib
	./$(SORT) plik1 8192 sys

plik: $(SRCG)
	$(CC) $(CFLAGS) -o $(GEN) $(SRCG) 
	./$(GEN) plik1 8192 5000
	cp plik1 plik


clean:
	$(RM) $(GEN) $(SORT) plik plik1