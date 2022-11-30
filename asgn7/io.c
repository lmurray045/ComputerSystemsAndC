#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "io.h"

//I/O functions implementation

//variable declaration
uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

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

int main(void){
	uint8_t buf[100];
	uint8_t *bufpoint = &buf[0];
	int fd = open("example.txt", O_RDONLY);
	printf("bytes read: %d\n", read_bytes(fd, bufpoint, 100));
	printf("buffer contents: %s\n", buf);
	close(fd);
	int fdo = open("example2.txt", O_WRONLY | O_CREAT);
	printf("bytes written: %d\n", write_bytes(fdo, bufpoint, 100));
	close(fdo);
	return 0;
}
