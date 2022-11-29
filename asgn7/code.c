#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "code.h"

//implementation of the code Abstract Data Type

//constructor. Initilizes a code object
Code code_init(void){
	Code c;
	(&c)->top = 10;
	for(uint64_t i =0; i < MAX_CODE_SIZE; i++){
		(&c)->bits[i] = 0;
	}
	return c;
}

//set bit: Sets the bit at the ith address
bool code_set_bit(Code *c, uint32_t i){
	if(i > c->top || i < 0){
		return false;
	}
	uint64_t byte_address = i / 8;
	uint64_t bit_address = i % 8;
	uint64_t bit_num = pow(2, (bit_address - 1));
	c->bits[byte_address] = c->bits[byte_address] | bit_num;
	return true;
}

//clear bit: clears the bit at the ith address
bool code_clr_bit(Code *c, uint32_t i){
	if(i > c->top || i < 0){
		return false;
	}
	uint64_t byte_address = i / 8;
	uint64_t bit_address = i % 8;
	uint64_t bit_num = pow(2, (bit_address - 1));
	bit_num = ~bit_num;
	c->bits[byte_address] = c->bits[byte_address] & bit_num;
	return true;
}

//get bit: returns the bit at the ith address
bool code_get_bit(Code *c, uint32_t i){
	if(i > c->top || i < 0){
		return false;
	}
	uint64_t byte_address = i / 8;
	uint64_t bit_address = i % 8;
	uint64_t bit_num = pow(2, (bit_address - 1));
	if((c->bits[byte_address] & bit_num) > 0){
		return true;
	}
	else{
		return false;
	}	
}

//prints out the bits in the given code object
void code_print(Code *c){
	for(uint64_t i = 0; i < c->top; i++){
		printf("%d", code_get_bit(c, i));
	}
	printf("\n");
}

int main(void){
	Code c = code_init();
	code_set_bit(&c, 5);
	code_set_bit(&c, 9);
	code_print(&c);
	code_clr_bit(&c, 5);
	code_print(&c);
	return 0;
}
