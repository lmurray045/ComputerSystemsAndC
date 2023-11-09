#include "pq.h"
#include "node.h"
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// priority queue nodes, called "Housing". They hold the nodes for the pq

typedef struct Housing Housing;

struct Housing {
  Housing *left;
  Housing *right;
  uint64_t frequency;
  Node *node;
};

// create a housing object
Housing *housing_create(Node *n) {
  Housing *h = (Housing *)malloc(sizeof(Housing));
  h->left = NULL;
  h->right = NULL;
  h->node = n;
  h->frequency = n->frequency;
  return h;
}

// delete a housing object
void housing_delete(Housing **h) {
  node_delete(&((*h)->node));
  free(*h);
  *h = NULL;
  return;
}

// housing print
void housing_print(Housing *h) {
  node_print(h->node);
  return;
}

// implementation of the priority queue abstract data type

struct PriorityQueue {
  Housing *head;
  Housing *tail;
  uint64_t capacity;
  uint64_t elements;
};

// priority queue creator
PriorityQueue *pq_create(uint32_t capacity) {
  PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
  pq->capacity = capacity;
  pq->elements = 0;
  pq->head = housing_create(node_create('/', 0));   // lowest possible frequency
  pq->tail = housing_create(node_create('\\', -1)); // highest possible
                                                    // frequency
  pq->tail->left = pq->head;
  pq->head->right = pq->tail;
  return pq;
}

// pq print
void pq_print(PriorityQueue *q) {
  Housing *start = q->head;
  for (uint64_t i = 0; i < q->elements; i++) {
    Housing *next = start->right;
    housing_print(next);
    start = next;
  }
  return;
}

// pq empty. Returns true if the pq is empty
bool pq_empty(PriorityQueue *q) {
  if (q->elements == 0) {
    return true;
  }
  return false;
}

// pq full. Returns true if the pq is full
bool pq_full(PriorityQueue *q) {
  if (q->elements == q->capacity) {
    return true;
  }
  return false;
}

// pq size. Returns the elements in pq
uint32_t pq_size(PriorityQueue *q) { return q->elements; }

// pq enqueue: add something to the queue
bool enqueue(PriorityQueue *q, Node *n) {
  Housing *h = housing_create(n);
  if (pq_full(q) == true) {
    return false;
  }
  Housing *start = q->head;
  Housing *next;
  if (pq_empty(q) == true) {
    next = start->right;
    start->right = h;
    next->left = h;
    h->left = start;
    h->right = next;
    q->elements += 1;
    return true;
  }
  for (uint64_t i = pq_size(q); i >= 0; i--) {
    next = start->right;
    if ((start->frequency <= h->frequency) &&
        (h->frequency < next->frequency)) {
      start->right = h;
      next->left = h;
      h->left = start;
      h->right = next;
      q->elements += 1;
      return true;
    }
    start = next;
  }
  return false;
}

// dequeue: remove item from queue
bool dequeue(PriorityQueue *q, Node **n) {
  if (pq_empty(q) == true) {
    return false;
  }
  *n = q->head->right->node;
  q->head->right = q->head->right->right;
  q->head->right->left = q->head;
  q->elements -= 1;
  return true;
}

// pq delete: deletes a priority queue
void pq_delete(PriorityQueue **q) {
  Housing *start = (*q)->head;
  for (uint64_t i = 0; i <= pq_size(*q) + 1; i++) {
    Housing *next = start->right;
    housing_delete(&start);
    start = next;
  }
  free(*q);
  return;
}
/*
int main(){
        PriorityQueue * pq = pq_create(10);
        Node * n1 = node_create('H', 50);
        Node * n2 = node_create('c', 2);
        Node * n3 = node_create('l', 5);
        Node * n4 = node_create('N', 1);
        Node * n5 = node_create('w', 15);
        enqueue(pq, n1);
        enqueue(pq, n2);
        enqueue(pq, n3);
        enqueue(pq, n5);
        printf("pq elements: %lu\n", pq->elements);
        pq_print(pq);
        dequeue(pq, &n4);
        printf("\n");
        printf("1st Node 4: ");
        node_print(n4);
        printf("pq elements: %lu\n", pq->elements);
        pq_print(pq);
        dequeue(pq, &n4);
        printf("\n");
        printf("2nd Node 4: ");
        node_print(n4);
        printf("pq elements: %lu\n", pq->elements);
        pq_print(pq);
        dequeue(pq, &n4);
        printf("\n");
        printf("3rd Node 4: ");
        node_print(n4);
        printf("pq elements: %lu\n", pq->elements);
        pq_print(pq);
        dequeue(pq, &n4);
        printf("\n");
        printf("3rd Node 4: ");
        node_print(n4);
        printf("pq elements: %lu\n", pq->elements);
        pq_print(pq);
        pq_delete(&pq);
        return 0;
}
*/
