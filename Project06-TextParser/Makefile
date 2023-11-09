CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
#LFLAGS = $(shell pkg-config --libs gmp) 

all: banhammer

banhammer: bf.o bv.o ht.o banhammer.o node.o ll.o parser.o city.o
	$(CC) -o $@ $^ -lm -Ofast

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f bf bv ht banhammer node ll parser city *.o
	
spotless: clean
	rm -f banhammer

format:
	clang-format -i -style=file bf.c bv.c ht.c banhammer.c node.c ll.c parser.c
