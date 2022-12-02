#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include "stack.h"
#include "node.h"

//stack ADT implementation
struct Stack {
	uint32_t top;
	uint32_t capacity;
	Node **items;
};

//stack creator
Stack *stack_create(uint32_t capacity){
	Stack * stack = (Stack *)malloc(sizeof(Stack));
	stack->top = 0;
	stack->capacity = capacity;
	stack->items = (Node **)calloc(capacity, sizeof(Node));
	return stack;
}

//stack delete: deletes the stack
void stack_delete(Stack **s){
	for(uint32_t i = 0; i < (*s)->top; i++){
		node_delete(((*s)->items + i));
	}
	free(*s);
	*s = NULL;
	return;
}

//stack print
void stack_print(Stack *s){
	for(uint32_t i = 0; i < s->top; i++){
		node_print(*(s->items + i));
	}
	return;
}

//stack full: returns true if the stack is full
bool stack_full(Stack *s){
	if(s->top == s->capacity){
		return true;
	}
	return false;
}

//stack empty: returns true if the stack is empty
bool stack_empty(Stack *s){
	if(s->top == 0){
		return true;
	}
	return false;
}

//stack size: returns number of nodes in the stack
uint32_t stack_size(Stack *s){
	return s->top;
}

//push a node onto the stack
bool stack_push(Stack *s, Node *n){
	if(stack_full(s) == true){
		return false;
	}
	*(s->items+(s->top)) = n;
	s->top += 1;
	return true;
}

//stack pop: returns and removes the top element in the stack
bool stack_pop(Stack *s, Node **n){
	if(stack_empty(s) == true){
		return false;
	}
	s->top -= 1;
	*n = *(s->items + s->top);
	return true;
}
/*
int main(void){
	Node* n1 = node_create('H', 10);
	Node* n2 = node_create('I', 12);
	Node* n3 = node_create('T', 2);
	Node ** nstore = &n1;
	Stack *stack = stack_create(10);
	//printf("stack full: %d\n", stack_full(stack));
	//printf("stack empty: %d\n", stack_empty(stack));
	stack_push(stack, n1);
	stack_push(stack, n2);
	stack_push(stack, n3);
	stack_print(stack);
	stack_pop(stack, nstore);
	printf("popped node: ");
	node_print(*nstore);
	stack_print(stack);
	stack_delete(&stack);
	return 0;
}
*/
