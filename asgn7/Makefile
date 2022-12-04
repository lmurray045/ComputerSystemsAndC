CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
#LFLAGS = $(shell pkg-config --libs gmp) 

all: encode decode

encode: huffman.o code.o pq.o node.o stack.o io.o encode.o
	$(CC) -o $@ $^ -lm
	
decode: huffman.o code.o pq.o node.o stack.o io.o decode.o
	$(CC) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f huffman code stack pq node io *.o
	
spotless: clean
	rm -f encode decode

format:
	clang-format -i -style=file huffman.c code.c stack.c pq.c node.c io.c
