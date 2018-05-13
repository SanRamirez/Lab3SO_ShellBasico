all: cli clean

CC=gcc
CFLAGS=-I.
DEPS=parser.h ejecutador.h 
OBJ=parser.o main.o ejecutador.o 

%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

cli: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
