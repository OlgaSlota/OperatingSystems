GEN =../zad1/generator.c
RYGLE =rygle.c

file: $(RYGLE) $(GEN)
	gcc -Wall -o lock $(RYGLE)
	gcc -Wall -o gen $(GEN)
	./gen file 4 10
	chmod g+s,g-x file
	sudo mount -oremount,mand /

run: lock file
	./lock file

clean:
	$(RM) lock gen file