CC = gcc
CFLAGS = -Wall 
S = send
L = listen
SRCS= send.c
SRCL = listen.c

all: $(L) 

$(L): $(SRCL) $(SRCS)
	$(CC) $(CFLAGS) -o $(S) $(SRCS)
	$(CC) $(CFLAGS) -o $(L) $(SRCL)


clean:
	$(RM) $(L) $(S) listenPID.txt sendPID.txt