#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "io.h"
#include "defines.h"
#include <math.h>

//I/O functions implementation

//variable declaration
uint64_t bytes_read = 0;
uint64_t bytes_written = 0;
static uint8_t bitvec[BLOCK];
static uint64_t index = 0;
static uint64_t bvsize = 0;

//read bytes: function for reading bytes from a file
int read_bytes(int infile, uint8_t *buf, int nbytes){
	int counter = 0;
	while(read(infile, (buf + counter), 1) != 0){
		counter += 1;
		if(counter == nbytes){
			break;
		}
	}
	bytes_read += counter;
	return counter;
}

//write bytes: function for writing bytes to a file
int write_bytes(int outfile, uint8_t *buf, int nbytes){
	int counter = 0;
	while(*(buf+counter) != 0 && write(outfile, (buf + counter), 1) != 0){
		counter += 1;
		if(counter == nbytes){
			break;
		}
	}
	bytes_written += counter;
	return counter;
}

//read bit: reads a single bit from the file;
bool read_bit(int infile, uint8_t *bit){
	if(index == 0){
		bvsize = read_bytes(infile, &bitvec[0], BLOCK);
	}
	if(index == ((bvsize * 8))){
		if(bvsize != (BLOCK)){
			return false;
		}
		bvsize = read_bytes(infile, &bitvec[0], BLOCK);
		if(bvsize == 0){
			return false;
		}
	}
	if(index == (BLOCK * 8)){
		index = 0;
	}
	uint64_t byte_address = index / 8;
	uint64_t bit_address = index % 8;
	bit_address = 7 - bit_address;
	uint64_t bit_num = pow(2, bit_address);
	if((bitvec[byte_address] & bit_num) > 0){
		*bit = 1;
	}
	else{
		*bit = 0;
	}
	//printf("index: %lu\n", index);
	//printf("bvsize: %lu\n", bvsize);
	index += 1;
	return true;
}

int main(void){
	uint8_t buf[100];
	uint8_t *bufpoint = &buf[0];
	uint8_t bit;
	int fd = open("example.txt", O_RDONLY);
	printf("example.txt in binary: ");
	int counter;
	for(counter = 1; counter != 500 && read_bit(fd, &bit) == true; counter++){
		printf("%d", bit);
		if(counter % 8 == 0 && counter != 0){
			printf(" ");
		}
	}
	printf("\n");
	printf("%d\n", counter);
	//printf("bytes read: %d\n", read_bytes(fd, bufpoint, 100));
	//printf("buffer contents: %s\n", buf);
	close(fd);
	int fdo = open("example2.txt", O_WRONLY | O_CREAT);
	printf("bytes written: %d\n", write_bytes(fdo, bufpoint, 100));
	close(fdo);
	return 0;
}
