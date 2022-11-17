#include <stdio.h>
#include <stdlib.h>
#include "ll.h"
#include "node.h"
#include "ht.h"
#include "city.h"

//structure definition for hash table
//the structure definition and the creator were taken from the design document
struct HashTable {
	uint64_t salt;
	uint32_t size;
	uint32_t n_keys;
	uint32_t n_hits;
	uint32_t n_misses;
	uint32_t n_examined;
	bool mtf;
	LinkedList ** lists;
};

HashTable *ht_create(uint32_t size , bool mtf) {
	HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
	if (ht != NULL) {
		ht->mtf = mtf;
		ht->salt = 0x9846e4f157fe8840;
		ht->n_hits = ht->n_misses = ht->n_examined = 0;
		ht->n_keys = 0;
		ht->size = size;
		ht->lists = (LinkedList **) calloc(size , sizeof(LinkedList *));
		if (!ht->lists) {
			free(ht);
			ht = NULL;
		}
	}
	return ht;
}

//hash table print
void ht_print(HashTable *ht){
	for(uint64_t i = 0; i != (ht->size); i++){
		printf("list index %lu: \n", i);
		if(*(ht->lists + i)== NULL){
			printf("List not initilized.\n");
		}
		else{
			ll_print(*(ht->lists + i));
		}
	}
	return;
}

//hash table insert
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak){
	uint64_t addr = hash(ht->salt, oldspeak) % ht->size;
	printf("address of hash: %lu\n", addr);
	if(*(ht->lists + addr) == NULL){
		*(ht->lists + addr) = ll_create(ht->mtf);
		ll_insert(*((ht->lists + addr)), oldspeak, newspeak);
		ht->n_keys += 1;
	}
	else{	
		uint32_t temp = ll_length(*(ht->lists + addr));
		ll_insert(*(ht->lists + addr), oldspeak, newspeak);
		if((ll_length(*(ht->lists + addr))) != temp){
			ht->n_keys += 1;
		}
	}
	return;
}

//hash table lookup
Node *ht_lookup(HashTable *ht, char *oldspeak){
	uint64_t addr = hash(ht->salt, oldspeak) % ht->size;
	if(*(ht->lists + addr) == NULL){
		ht->n_misses += 1;
		ht->n_examined = links;
		return NULL;
	}
	Node* nd = ll_lookup(*(ht->lists + addr), oldspeak);
	if(nd == NULL){
		ht->n_misses += 1;
		ht->n_examined = links;
		return NULL;
	}
	ht->n_hits += 1;
	ht->n_examined = links;
	return nd;
}

//hash table size
uint32_t ht_size(HashTable *ht){
	return ht->size;
}

//hash table count: returns the number of initilzed linked list in the table
uint32_t ht_count(HashTable *ht){
	uint32_t counter = 0;
	for(uint32_t i = 0; i < ht->size; i++){
		if(*(ht->lists + i) != NULL){
			counter++;
		}
	}
	return counter;
}



int main(void){
	HashTable * ht = ht_create(10, true);
	printf("hash table created \n");
	printf("hash table size: %u \n", ht_size(ht));
	printf("hash table count: %u \n", ht_count(ht));
	ht_insert(ht, "hello", "world");
	ht_insert(ht, "whats u", "dog");
	ht_insert(ht, "whts up", "dog");
	ht_insert(ht, "whaup", "dog");
	ht_insert(ht, "whaup", "dog");
	ht_insert(ht, "whats", "dog");
	node_print(ht_lookup(ht, "whaup"));
	node_print(ht_lookup(ht, "whup"));
	node_print(ht_lookup(ht, "whts up"));
	ht_print(ht);
	printf("hash table count: %u \n", ht_count(ht));
	printf("\n");
	printf("hash table keys: %u\n", ht->n_keys);
	printf("hash table hits: %u\n", ht->n_hits);
	printf("hash table misses: %u\n", ht->n_misses);
	printf("hash table examined: %u\n", ht->n_examined);
	return 0;
}

