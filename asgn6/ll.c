#include "node.h"
#include "ll.h"
#include <stdlib.h>
#include <stdio.h>

//seeks and links
uint64_t seeks;
uint64_t links;

//linked list code
struct LinkedList {
	uint32_t length;
	Node *head; // Head sentinel node.
	Node *tail; // Tail sentinel node.
	bool mtf;
};

//string compare function
bool stringcompare(char *str1, char *str2){
	uint64_t i;
	for(i = 0; *(str1 + i) != '\0'; i ++){
		if(*(str1 + i) != *(str2 + i)){
			return false;
		}
	}
	if(*(str1 + i) != *(str2 + i)){
		return false;
	}
	return true;
 }

//linked list creator. Creates a linked list
LinkedList *ll_create(bool mtf){
	LinkedList *ll = (LinkedList *)malloc(sizeof(LinkedList));
	//char old[] = "No data";
	//char new[] = "No data";
	char *op = NULL;
	char *np = NULL;
	ll->length = 0;
	ll->head = node_create(op, np);
	ll->tail = node_create(op, np);
	ll->mtf = mtf;
	ll->head->prev = NULL;
	ll->tail->next = NULL;
	ll->head->next = ll->tail;
	ll->tail->prev = ll->head;
	return ll;
}
 //linked list print
 void ll_print(LinkedList *ll){
 	Node *start = ll->head->next;
 	for(uint64_t i = 0; i != ll->length; i++){
 		node_print(start);
 		start = start->next;
 	}
 	return;
 }
 //linked list delete
void ll_delete(LinkedList **ll){
	Node *start = (*ll)->head;
	Node *next = NULL;
 	for(uint64_t i = 0; i != ((*ll)->length + 2); i++){
 		next = start->next;
 		node_delete(&start);
 		start = next;
 	}
 	free(*ll);
 	return;
}

//linked list lookup
Node *ll_lookup(LinkedList *ll, char *oldspeak){
	Node *start = ll->head->next;
	seeks += 1;
 	for(uint64_t i = 0; i != ll->length; i++){
 		links += 1;
 		if(stringcompare(start->oldspeak, oldspeak) == 1){
 			if(ll->mtf == true){
 				start->next->prev = start->prev;
 				start->prev->next = start->next;
 				Node* headnext = ll->head->next;
 				ll->head->next = start;
 				start->next = headnext;
 				start->prev = ll->head;
 				headnext->prev = start;
 				}
 			return start;
 			}
 		start = start->next;
 	}
 	Node *nl = NULL;
 	return nl;
}

//linked list insert
void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak){
	if(ll_lookup(ll, oldspeak) != NULL){
		return;
	}
	Node *nd = node_create(oldspeak, newspeak);
	Node *nextnd = ll->head->next;
	ll->head->next = nd;
	nextnd->prev = nd;
	nd->prev = ll->head;
	nd->next = nextnd;
	ll->length += 1;
	return;
	
}

//linked list length
uint32_t ll_length(LinkedList *ll){
	return ll->length;
}

//linked list stats
void ll_stats(uint32_t *n_seeks, uint32_t *n_links){
	*n_seeks = seeks;
	*n_links = links;
	return;
}
 /*
int main(void){
	LinkedList *ll = ll_create(true);
	//printf("list created\n");
	ll_insert(ll, "word", "play");
	//printf("worldplay \n");
	ll_insert(ll, "hello", "world");
	//printf("hello world \n");
	ll_insert(ll, "what the", "dog doing");
	char *none = NULL;
	ll_insert(ll, "badspeak", none);
	ll_print(ll);
	//printf("what the dog doing \n");
	node_print(ll_lookup(ll, "word"));
	node_print(ll_lookup(ll, "cat"));
	printf("Linked List: \n");
	ll_print(ll);
	printf("Length: %u\n", ll_length(ll));
	uint32_t s;
	uint32_t *sp = &s;
	uint32_t l;
	uint32_t *lp = &l;
	ll_stats(sp, lp);
	printf("Stats: %u, %u\n", s, l);
	ll_delete(&ll);
	return 0;
}
*/

