#include <stdlib.h>
#include <stdio.h>
#include "bv.h"
#include <math.h>

//bit vector definition
struct BitVector {
	uint32_t length;
	uint64_t *vector;
};

BitVector *bv_create(uint32_t length)
{
	uint64_t array_bytes = (length / 64) + 1;
	BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
	bv->vector = (uint64_t *)calloc(array_bytes, sizeof(uint64_t));
	if(bv->vector == NULL){
		return NULL;
		}
	bv->length = length;
	return bv;
}

//bit vector print; prints out the bit vector
void bv_print(BitVector *bv)
{
	printf("bit vector: ");
	for(uint64_t i = 0; i < bv->length; i++){
		uint64_t bit_vector_byte = i / 64;
		uint64_t location_byte = i % 64;
		uint64_t bitwise_num = pow(2, (location_byte - 1));
		uint64_t bit_test = *(bv->vector+bit_vector_byte) & bitwise_num;
		if(bit_test > 0){
			printf("1");
			}
		else{
			printf("0");
			}
	}
	printf("\n");
}

//bit vector length: returns the length of the bit vector
uint32_t bv_length(BitVector *bv){
	return bv->length;
}

//bit vector set bit. Sets the ith bit of the bit vector
void bv_set_bit(BitVector *bv, uint32_t i){
	uint32_t i2 = i - 1;
	uint64_t bit_vector_byte = i2 / 64;
	uint64_t location_byte = i2 % 64;
	uint64_t bitwise_num = pow(2, (location_byte - 1));
	*(bv->vector+bit_vector_byte) = *(bv->vector+bit_vector_byte) | bitwise_num;
	return;
}

//bit vector clear: clears the it bit in the bit vector
void bv_clr_bit(BitVector *bv, uint32_t i){
	uint32_t i2 = i - 1;
	uint64_t bit_vector_byte = i2 / 64;
	uint64_t location_byte = i2 % 64;
	uint64_t bitwise_num = pow(2, (location_byte - 1));
	bitwise_num = ~bitwise_num;
	*(bv->vector+bit_vector_byte) = *(bv->vector+bit_vector_byte) & bitwise_num;
	return;
}

int main()
{
	BitVector* bv = bv_create(20);
	printf("Vector Length: %d\n", bv_length(bv));
	bv_set_bit(bv, 4);
	bv_print(bv);
	bv_set_bit(bv, 6);
	bv_print(bv);
	bv_clr_bit(bv, 4);
	bv_print(bv);
	bv_set_bit(bv, 20);
	bv_print(bv);
	bv_clr_bit(bv, 6);
	bv_print(bv);
	bv_clr_bit(bv, 20);
	bv_print(bv);
}
