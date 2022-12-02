#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "huffman.h"
#include "pq.h"
#include "io.h"
#include <fcntl.h>
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

//auxillary function for recursive searching
void traverse_code(Code * code, Node * n, uint8_t pushcode, Code table[static ALPHABET]){
	uint8_t throwaway;
	printf("iterating...\n");
	if(pushcode == 1){
		code_push_bit(code, 1);
	}
	else if(pushcode == 0){
		code_push_bit(code, 0);
	}
	if(n != NULL){
		node_print(n);
		printf("code: ");
		code_print(code);
		traverse_code(code, n->left, 0, table);
		if(n->left == NULL && n->right == NULL){
			table[n->symbol] = *code;
			code_pop_bit(code, &throwaway);
			return;
		}
		traverse_code(code, n->right, 1, table);
		if(n->left == NULL && n->right == NULL){
			table[n->symbol] = *code;
			code_pop_bit(code, &throwaway);
			return;
		}
	}
	if(code_empty(code) == false){
			code_pop_bit(code, &throwaway);
	}
	return;
}

//build codes: traverses code table and builds the codes for it.
void build_codes(Node *root, Code table[static ALPHABET]){
	Code code = code_init();
	traverse_code(&code, root, 2, table);
	return;
}

int main(void){
	uint64_t hist[ALPHABET];
	Code table[ALPHABET];
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
	printf("\n\n");
	build_codes(parent, table);
	printf("H code: ");
	code_print(&table['H']);
	printf("c code: ");
	code_print(&table['c']);
	printf("l code: ");
	code_print(&table['l']);
	printf("w code: ");
	code_print(&table['w']);
	
	int fdo = open("example2.txt", O_WRONLY | O_CREAT);
	write_code(fdo, &table['H']);
	write_code(fdo, &table['c']);
	write_code(fdo, &table['l']);
	write_code(fdo, &table['w']);
	flush_codes(fdo);
	close(fdo);
	printf("\n\n");
	uint8_t bit;
	int fd = open("example2.txt", O_RDONLY);
	printf("example2.txt in binary: ");
	int counter;
	for(counter = 1; counter != 500 && read_bit(fd, &bit) == true; counter++){
		printf("%d", bit);
		if(counter % 8 == 0 && counter != 0){
			printf(" ");
		}
	}
	printf("\n");
	
	return 0;
}
