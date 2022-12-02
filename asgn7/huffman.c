#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "huffman.h"
#include "pq.h"
#include <math.h>

//huffman code implementation

//build a huffman tree, and return its root node
Node *build_tree(uint64_t hist[static ALPHABET]){
	PriorityQueue *pq = pq_create(ALPHABET);
	for(uint64_t i = 0; i < ALPHABET; i ++){
		if(hist[i] > 0){
			
			Node * n = node_create(i, hist[i]);
			enqueue(pq, n);
		}
	}
	pq_print(pq);
	Node * parent;
	while(pq_size(pq) > 1){
		Node * n1;
		dequeue(pq, &n1);
		Node * n2;
		dequeue(pq, &n2);
		//if(n1 != NULL && n2 != NULL){
		parent = node_join(n1, n2);
		//}
		//else{
		enqueue(pq, parent); 
		//}
	}
	return parent;
}

int main(void){
	uint64_t hist[ALPHABET];
	for(uint64_t i = 0; i < ALPHABET; i++){
		hist[i] = 0;
	}
	hist['H'] = 50;
	hist['c'] = 25;
	hist['l'] = 5;
	hist['w'] = 15;
	Node * parent;
	parent = build_tree(hist);
	printf("\n");
	node_print(parent);
	printf("parent left: ");
	node_print(parent->left);
	printf("parent right: ");
	node_print(parent->right);
	printf("\n");
	printf("left left: ");
	node_print(parent->left->left);
	printf("left right: ");
	node_print(parent->left->right);
	printf("\n");
	printf("left left left: ");
	node_print(parent->left->left->left);
	printf("left left right: ");
	node_print(parent->left->left->right);
	return 0;
}
