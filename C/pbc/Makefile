CC=gcc -ggdb
objects = dcp-abe.o testing.o

dcp-abe : $(objects)
	$(CC) -o dcp-abe -lgmp -lpbc $(objects)

dcp-abe.o : dcp-abe.h
testing.o : dcpabe.h

.PHONY: clean run
clean : 
	rm -f dcp-abe $(objects)

run: dcp-abe
	./dcp-abe