FLAGS= -Wall -g
CC=gcc

all:stringProg

stringProg:f.o
	$(CC) $(FLAGS) -o stringProg f.o -lm

f.o:f.c
	$(CC) $(FLAGS) -c f.c -lm


PHONY: all clean 
clean:
	rm -f *.a *.o