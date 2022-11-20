#include "bv.h"
#include "bf.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "city.h"
#define N_HASHES 5

//bloom filter implementation

//bf structure definition and constructor, taken from assignment document


static uint64_t default_salts [] = {
0x5adf08ae86d36f21 ,
0x419d292ea2ffd49e ,
0x50d8bb08de3818df ,
0x272347aea4045dd5 ,
0x7c8e16f768811a21
};

struct BloomFilter {
	uint64_t salts[N_HASHES ]; // Salts for five hash functions
	uint32_t n_keys;
	uint32_t n_hits;
	uint32_t n_misses;
	uint32_t n_bits_examined;
	BitVector *filter;
};

//typedef struct BloomFilter BloomFilter;

BloomFilter *bf_create(uint32_t size) {
	BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
	if (bf) {
		bf->n_keys = bf ->n_hits = 0;
		bf->n_misses = bf->n_bits_examined = 0;
		for (int i = 0; i < N_HASHES; i++) {
			bf ->salts[i] = default_salts[i];
			}
		bf->filter = bv_create(size);
		if (bf->filter == NULL) {
			free(bf);
			bf = NULL;
			}
		}
	return bf;
}

//bf delete. Deletes the BloomFilter
void bf_delete(BloomFilter **bf){
	BitVector * bf_filter = (*bf)->filter;
	bv_delete(&bf_filter);
	free(*bf);
	return;
}

//bf print. Prints the bloom filter.
void bf_print(BloomFilter *bf){
	bv_print(bf->filter);
	printf("Keys: %u\n", bf->n_keys);
	printf("Hits: %u\n", bf->n_hits);
	printf("Misses: %u\n", bf->n_misses);
	printf("Bits Examined: %u\n", bf->n_bits_examined);
	return;
}

//bf size; returns the size of the bloomfilter
uint32_t bf_size(BloomFilter *bf){
	return bv_length((bf->filter));
}

//bf add. Adds a word to the bloom filter.
void bf_insert(BloomFilter *bf, char *oldspeak){
	bf->n_keys += 1;
	for(uint64_t i = 0; i < 5; i++){
		//printf("addr calc\n");
		//printf("string in question: %s\n", oldspeak);
		//printf("hash: %lu \n", hash((bf->salts[i]), oldspeak));
		uint64_t addr = (hash((bf->salts[i]), oldspeak)) % bf_size(bf);
		//printf("size: %u\n", bf_size(bf));
		//printf("setting bit, addr: %lu\n", addr);
		if(addr == 0){
			addr = 1;
		}
		bv_set_bit((bf->filter), addr);
		//printf("done\n");
	}
	return;
}

//bf probe. Probes and sees if a word in the bloomfilter is present
bool bf_probe(BloomFilter *bf, char *oldspeak){
	for(uint64_t i = 0; i < 5; i++){
		uint64_t addr = (hash((bf->salts[i]), oldspeak)) % bf_size(bf);
		uint8_t test = bv_get_bit((bf->filter), addr);
		bf->n_bits_examined += 1;
		if(test == 0){
			bf->n_misses += 1;
			return false;
		}
	}
	bf->n_hits += 1;
	return true;
}

//bf stats. Sets pointers to respective stat values.
void bf_stats(BloomFilter *bf, uint32_t *nk, uint32_t *nh, uint32_t *nm, uint32_t *ne){
	*nk = bf->n_keys;
	*nh = bf->n_hits;
	*nm = bf->n_misses;
	*ne = bf->n_bits_examined;
	return;
}
	
/*
int main(void){
	BloomFilter *bf = bf_create(64);
	bf_print(bf);
	bf_insert(bf, "hello");
	bf_print(bf);
	bf_insert(bf, "world");
	bf_print(bf);
	printf("hello: %d\n", bf_probe(bf, "hello"));
	printf("world: %d\n", bf_probe(bf, "world"));
	printf("hello: %d\n", bf_probe(bf, "hello"));
	printf("balls: %d\n", bf_probe(bf, "balls"));
	printf("size: %u\n", bf_size(bf));
	bf_print(bf);
	bf_delete(&bf);
	uint32_t k = 0;
	uint32_t *nk = &k;
	uint32_t h = 0;
	uint32_t *nh = &h;
	uint32_t m = 0;
	uint32_t *nm = &m;
	uint32_t e = 0;
	uint32_t *ne = &e;
	bf_stats(bf, nk, nh, nm, ne);
	printf("keys: %u\n", k);
	printf("hits: %u\n", h);
	printf("misses: %u\n", m);
	printf("examined: %u\n", e);
	return 0;
}
*/
