#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <inttypes.h>
#include "node.h"

//node implementation

//node creation function
Node *node_create(uint8_t symbol, uint64_t frequency){
	Node *nd = (Node *)malloc(sizeof(Node));
	nd->symbol = symbol;
	nd->frequency = frequency;
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

//print node
void node_print(Node *n){
	if(n == NULL){
		printf("Node is NULL\n");
		return;
	}
	printf("Symbol: '");
	node_print_sym(n);
	printf("', Frequency: %lu.", n->frequency);
	//printf(" left child: '");
	//node_print_sym(n->left);
	//printf("'. right child: '");
	//node_print_sym(n->right);
	//printf("'");
	printf("\n");
	return;
}

//delete node
void node_delete(Node **n){
	free(*n);
	*n = NULL;
	return;
}

//node join
//joins two nodes, and makes a parent node from that data.
Node *node_join(Node *left, Node *right){
	uint64_t parfreq = left->frequency + right->frequency;
	Node * parent = node_create('$', parfreq);
	parent->left = left;
	parent->right = right;
	return parent;
}

//node print symbol
void node_print_sym(Node *n){
	if(iscntrl(n->symbol) == 0){
		printf("%c", n->symbol);
		return;
	}
	printf("0x%02"PRIx8"", n->symbol);
	return;
}
//node cmp: compares the frequency of two nodes. True if first is larger and vise versa
bool node_cmp(Node *n, Node *m){
	if(n->frequency > m->frequency){
		return true;
	}
	return false;
}

/*
int main(void){
	uint8_t hello = 65;
	Node* node_one = node_create(hello, 18);
	Node* node_two = node_create('\t', 4);
	Node* parent = node_join(node_one, node_two);
	printf("%d\n", node_cmp(node_two, node_one));
	node_print(node_one);
	node_print(node_two);
	node_print(parent);
	node_delete(&node_one);
	node_delete(&node_two);
	node_delete(&parent);
	return 0;
}
*/
