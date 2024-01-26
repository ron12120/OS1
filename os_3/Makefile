CC = gcc
FLAGS = -Wall -g
TARGETS = libencriptor.so encode decode

.PHONY: all clean

all: $(TARGETS)

libencriptor.so: encriptor.c encriptor.h
	$(CC) $(FLAGS) -fPIC -c $^
	$(CC) -shared -o $@ encriptor.o
	
encode: encode.c
	$(CC) $(FLAGS) -c $^
	$(CC) -o $@ encode.o

decode: decode.c
	$(CC) $(FLAGS) -c $^
	$(CC) -o $@ decode.o

	
clean:
	rm -rf *.o *.h.*gch $(TARGETS)