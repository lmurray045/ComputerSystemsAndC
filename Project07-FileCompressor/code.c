#include "code.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// implementation of the code Abstract Data Type

// constructor. Initilizes a code object
Code code_init(void) {
  Code c;
  (&c)->top = 0;
  for (uint64_t i = 0; i < MAX_CODE_SIZE; i++) {
    (&c)->bits[i] = 0;
  }
  return c;
}

// set bit: Sets the bit at the ith address
bool code_set_bit(Code *c, uint32_t i) {
  if (i > c->top || i < 0) {
    return false;
  }
  uint64_t byte_address = (i) / 8;
  uint64_t bit_address = i % 8;
  uint64_t bit_num = pow(2, (bit_address));
  // printf("i: %u, bitnum: %lu, byte: %lu, bit: %lu\n", i, bit_num,
  // byte_address, bit_address);
  c->bits[byte_address] = c->bits[byte_address] | bit_num;
  return true;
}

// clear bit: clears the bit at the ith address
bool code_clr_bit(Code *c, uint32_t i) {
  if (i > c->top || i < 0) {
    return false;
  }
  uint64_t byte_address = (i) / 8;
  uint64_t bit_address = i % 8;
  uint64_t bit_num = pow(2, (bit_address));
  bit_num = ~bit_num;
  c->bits[byte_address] = c->bits[byte_address] & bit_num;
  return true;
}

// code empty: returns true if code is empty
bool code_empty(Code *c) {
  if (c->top == 0) {
    return true;
  }
  return false;
}

// code full: returns true if code is full
bool code_full(Code *c) {
  if (c->top == (MAX_CODE_SIZE * 8)) {
    return true;
  }
  return false;
}

// get bit: returns the bit at the ith address
bool code_get_bit(Code *c, uint32_t i) {
  if (i > c->top || i < 0) {
    return false;
  }
  uint64_t byte_address = (i) / 8;
  uint64_t bit_address = i % 8;
  uint64_t bit_num = pow(2, (bit_address));
  if ((c->bits[byte_address] & bit_num) > 0) {
    return true;
  } else {
    return false;
  }
}

// push bit: adds a bit to the stack
bool code_push_bit(Code *c, uint8_t bit) {
  if (code_full(c) == true) {
    return false;
  }
  if (bit == 0) {
    code_clr_bit(c, c->top);
  } else {
    code_set_bit(c, c->top);
  }
  c->top += 1;
  return true;
}

// pop bit: removes a bit from the stack
bool code_pop_bit(Code *c, uint8_t *bit) {
  if (code_empty(c) == true) {
    return false;
  }
  if (code_get_bit(c, c->top) == true) {
    *bit = 1;
  } else {
    *bit = 0;
  }
  code_clr_bit(c, c->top);
  c->top -= 1;
  return true;
}

// prints out the bits in the given code object
void code_print(Code *c) {
  for (uint64_t i = 0; i < c->top; i++) {
    printf("%d", code_get_bit(c, i));
  }
  // if(c->top != 0){
  printf("\n");
  //}
}
/*
int main(void){
        Code c = code_init();
        assert(code_push_bit(&c, 1));
        assert(code_push_bit(&c, 0));
        code_push_bit(&c, 1);
        code_push_bit(&c, 0);
        code_push_bit(&c, 1);
        code_push_bit(&c, 1);
        code_print(&c);
        uint8_t bitstore = 2;
        code_pop_bit(&c, &bitstore);
        printf("popped bit: %d\n", bitstore);
        code_print(&c);
        code_pop_bit(&c, &bitstore);
        printf("popped bit: %d\n", bitstore);
        code_print(&c);
        return 0;
}
*/
