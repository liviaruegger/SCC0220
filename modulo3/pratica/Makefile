objects = main.c huffman.c

all: $(objects)
	gcc $(objects) -o main -g

run:
	./main

zip: $(objects)
	zip pratica3.zip $(objects) huffman.h Makefile