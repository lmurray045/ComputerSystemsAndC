CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp) 

all: keygen encrypt decrypt

keygen: keygen.o rsa.o randstate.o numtheory.o
	$(CC) -o $@ $^ $(LFLAGS) -lm -Ofast

encrypt: encrypt.o rsa.o randstate.o numtheory.o
	$(CC) -o $@ $^ $(LFLAGS) -lm -Ofast

decrypt: decrypt.o rsa.o randstate.o numtheory.o
	$(CC) -o $@ $^ $(LFLAGS) -lm -Ofast

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f keygen encrypt decrypt *.o

cleankeys:
	rm -f *.{pub,priv}

format:
	clang-format -i -style=file *.[ch]
