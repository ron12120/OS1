CC = gcc
CFLAGS = -Wall 

.PHONY: all clean

all: myzip myunzip 

myzip: myzip.c
	$(CC) $(CFLAGS) -o myzip myzip.c

myunzip: myunzip.c
	$(CC) $(CFLAGS) -o myunzip myunzip.c

clean:
	rm -f myzip myunzip res.tar.gz.gpg 
