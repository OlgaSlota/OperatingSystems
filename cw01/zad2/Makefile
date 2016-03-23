CC = gcc
CFLAGS = -Wall -fPIC
LIBSTAT = liblist.a 
LIBSRC = liblist.c
LIBOBJ = liblist.o
STAT = static
LIBDYN = liblist.so
DYN = dynamic
SHARED = shared


all:  $(STAT) $(DYN) $(SHARED)

$(STAT): $(LIBSRC)
	$(CC) -Wall -c $(LIBSRC) -o $(LIBOBJ)
	$(AR) ruv $(LIBSTAT)  $(LIBOBJ)
	ranlib $(LIBSTAT)
	$(CC) -Wall -o $(STAT) main.c -L. -llist

$(SHARED):  $(LIBSRC)
	$(CC) $(CFLAGS) -c $(LIBSRC)
	$(CC) $(CFLAGS) -shared -o $(LIBDYN) $(LIBOBJ)
	$(CC) -L. -o $(SHARED) main.c -llist

$(DYN):  main_dyn.c  
	$(MAKE) $(SHARED)
	$(CC) -Wall -o $(DYN) main_dyn.c -ldl
	
run_dynamic:
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
	./dynamic

run_static:
	./static

run_shared:
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
	./shared


clean:
	$(RM) $(LIBSTAT) $(LIBDYN) $(LIBOBJ) $(STAT) $(DYN) $(SHARED)