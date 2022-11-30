#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <inttypes.h>
#include "node.h"
#include "pq.h"
//implementation of the priority queue abstract data type

struct PriorityQueue {
    Node *head;
    Node *tail;
    uint64_t capacity;
    uint64_t elements;
};

//priority queue creator
PriorityQueue *pq_create(uint32_t capacity){
	PriorityQueue * pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
	pq->capacity = capacity;
	pq->elements = 0;
	pq->head = node_create('H', 0); //lowest possible frequency
	pq->tail = node_create('T', -1); //highest possible frequency
	pq->tail->left = pq->head;
	pq->head->right = pq->tail;
	return pq;
}

//pq print
void pq_print(PriorityQueue *q){
	Node * start = q->head;
	for(uint64_t i = 0; i < q->elements; i++){
		Node * next = start->right;
		node_print(next);
		start = next;
	}
	return;
}

//pq empty. Returns true if the pq is empty
bool pq_empty(PriorityQueue *q){
	if(q->elements == 0){
		return true;
	}
	return false;
}

//pq full. Returns true if the pq is full
bool pq_full(PriorityQueue *q){
	if(q->elements == q->capacity){
		return true;
	}
	return false;
}

//pq size. Returns the elements in pq
uint32_t pq_size(PriorityQueue *q){
	return q->elements;
}

//pq enqueue: add something to the queue
bool enqueue(PriorityQueue *q, Node *n){
	if(pq_full(q) == true){
		return false;
	}
	Node *start = q->head;
	Node * next;
	if(pq_empty(q) == true){
		next = start->right;
		start->right = n;
		next->left = n;
		n->left = start;
		n->right = next;
		q->elements += 1;
		return true;
	}
	for(uint64_t i = pq_size(q); i >= 0; i--){
		next = start->right;
		if((start->frequency < n->frequency < next->frequency)){
			start->right = n;
			next->left = n;
			n->left = start;
			n->right = next;
			q->elements += 1;
			return true;
		}
		start = next;
	}
	return false;
}

//dequeue: remove item from queue
bool dequeue(PriorityQueue *q, Node **n){
	if(pq_empty(q) == true){
		return false;
	}
	*n = q->head->right;
	q->head->right = q->head->right->right;
	q->head->right->right->left = q->head;
	q->elements -= 1;
	return true;
}

//pq delete: deletes a priority queue
void pq_delete(PriorityQueue **q){
	Node * start = (*q)->head;
	for(uint64_t i = 0; i <= pq_size(*q) + 1; i++){
		Node * next = start->right;
		node_delete(&start);
		start = next;
	}
	free(*q);
	return;
}

int main(){
	PriorityQueue * pq = pq_create(10);
	Node * n1 = node_create('A', 12);
	Node * n2 = node_create('B', 10);
	Node * n3 = node_create('C', 8);
	Node * n4 = node_create('w', 1);
	enqueue(pq, n1);
	enqueue(pq, n2);
	enqueue(pq, n3);
	printf("pq elements: %lu\n", pq->elements);
	pq_print(pq);
	dequeue(pq, &n4);
	printf("Node 4: ");
	node_print(n4);
	printf("pq elements: %lu\n", pq->elements);
	pq_print(pq);
	pq_delete(&pq);
	return 0;
}
