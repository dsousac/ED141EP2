CC = gcc
CFLAGS = -c -Wall -pedantic -O2
CFLAGSDB = -c -Wall -pedantic -ggdb

all: ep2 ep2db

ep2: ep2.o 
	$(CC) ep2.o -o ep2

ep2db: ep2db.o
	$(CC) ep2db.o -o ep2db

ep2.o: ep2.c
	$(CC) $(CFLAGS) ep2.c

ep2db.o: ep2.c
	$(CC) $(CFLAGSDB) ep2.c -o ep2db.o

clean:
	rm -f *o ep2 ep2db
