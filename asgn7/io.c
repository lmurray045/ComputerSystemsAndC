#include "io.h"
#include "code.h"
#include "defines.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// I/O functions implementation

// variable declaration
uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

static uint8_t bitvec[BLOCK];
static uint64_t index = 0;
static uint64_t bvsize = 0;

static uint8_t wtbitvec[1];
static uint64_t wtdex = 0;
// static uint64_t wtsize = 0;

// read bytes: function for reading bytes from a file
int read_bytes(int infile, uint8_t *buf, int nbytes) {
  int counter = 0;
  while (read(infile, (buf + counter), 1) != 0) {
    counter += 1;
    if (counter == nbytes) {
      break;
    }
  }
  bytes_read += counter;
  return counter;
}

// write bytes: function for writing bytes to a file
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
  int counter = 0;
  while (write(outfile, (buf + counter), 1) != 0) {
    counter += 1;
    if (counter == nbytes) {
      break;
    }
  }
  bytes_written += counter;
  return counter;
}

// read bit: reads a single bit from the file;
bool read_bit(int infile, uint8_t *bit) {
  if (index == 0) {
    bvsize = read_bytes(infile, &bitvec[0], BLOCK);
  }
  if (index == ((bvsize * 8))) {
    if (bvsize != (BLOCK)) {
      return false;
    }
    bvsize = read_bytes(infile, &bitvec[0], BLOCK);
    if (bvsize == 0) {
      return false;
    }
  }
  if (index == (BLOCK * 8)) {
    index = 0;
  }
  uint64_t byte_address = index / 8;
  uint64_t bit_address = index % 8;
  // bit_address = 7 - bit_address;
  uint64_t bit_num = pow(2, bit_address);
  if ((bitvec[byte_address] & bit_num) > 0) {
    *bit = 1;
  } else {
    *bit = 0;
  }
  // printf("index: %lu\n", index);
  // printf("bvsize: %lu\n", bvsize);
  index += 1;
  return true;
}

// repeatedly write codes into the buffer. When its full, send it to outfile.
void write_code(int outfile, Code *c) {
  uint8_t bit;
  for (uint64_t counter = 0; counter < c->top; counter++) {
    if (code_get_bit(c, counter) == true) {
      bit = 1;
    } else {
      bit = 0;
    }
    uint64_t byte_address = wtdex / 8;
    uint64_t bit_address = wtdex % 8;
    uint64_t bit_num = pow(2, bit_address);
    if (bit == 1) {
      wtbitvec[byte_address] = wtbitvec[byte_address] | bit_num;
    } else {
      bit_num = ~bit_num;
      wtbitvec[byte_address] = wtbitvec[byte_address] & bit_num;
    }
    wtdex++;
    if (wtdex == (1 * 8)) {
      write_bytes(outfile, &wtbitvec[0], 1);
      for (uint64_t i = 0; i < 1; i++) {
        wtbitvec[i] = 0;
      }
      wtdex = 0;
    }
  }
  return;
}

// flush bits. Basically, send all the bits in the array that didnt make fill
// the buffer and get sent by write_codes()
void flush_codes(int outfile) {
  uint64_t byte_address = wtdex / 8;
  for (uint64_t i = 0; i <= byte_address; i++) {
    write_bytes(outfile, &wtbitvec[byte_address], 1);
  }
  return;
}
/*
int main(void){
        uint8_t buf[100];
        uint8_t *bufpoint = &buf[0];
        printf("\n");
        printf("%d\n", counter);
        //printf("bytes read: %d\n", read_bytes(fd, bufpoint, 100));
        //printf("buffer contents: %s\n", buf);
        close(fd);

        Code c1 = code_init();
        code_push_bit(&c1, 1);
        code_push_bit(&c1, 0);
        code_push_bit(&c1, 1);
        code_push_bit(&c1, 1);
        code_push_bit(&c1, 0);
        code_push_bit(&c1, 1);
        Code c2 = code_init();
        code_push_bit(&c2, 1);
        code_push_bit(&c2, 0);
        code_push_bit(&c2, 0);
        code_push_bit(&c2, 1);
        code_push_bit(&c2, 0);
        code_push_bit(&c2, 1);
        Code c3 = code_init();
        code_push_bit(&c3, 0);
        code_push_bit(&c3, 1);
        code_push_bit(&c3, 1);
        code_push_bit(&c3, 0);
        code_push_bit(&c3, 1);
        code_push_bit(&c3, 1);
        int fdo = open("example2.txt", O_WRONLY | O_CREAT);
        write_code(fdo, &c1);
        write_code(fdo, &c2);
        write_code(fdo, &c3);
        flush_codes(fdo);
        close(fdo);
        uint8_t bit;
        int fd = open("example2.txt", O_RDONLY);
        printf("example2.txt in binary: ");
        int counter;
        for(counter = 1; counter != 500 && read_bit(fd, &bit) == true;
counter++){ printf("%d", bit); if(counter % 8 == 0 && counter != 0){ printf("
");
                }
        }
        printf("\n");
        return 0;
}
*/
