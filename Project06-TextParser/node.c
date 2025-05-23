#include "node.h"
#include <stdio.h>
#include <stdlib.h>

// string copy function
static char *stringcopy(char *string) {
  int j;
  for (j = 0; *(string + j) != 0; j++) {
  }
  char *copy = (char *)calloc((j + 1), sizeof(char));
  int i;
  for (i = 0; i != j; i++) {
    *(copy + i) = *(string + i);
  }
  *(copy + i + 1) = '\0';
  return copy;
}

// definition and code for Node data type

Node *node_create(char *oldspeak, char *newspeak) {
  Node *nd = (Node *)malloc(sizeof(Node));
  if (oldspeak == NULL) {
    nd->oldspeak = NULL;
  } else {
    nd->oldspeak = stringcopy(oldspeak);
  }
  if (newspeak == NULL) {
    nd->newspeak = NULL;
  } else {
    nd->newspeak = stringcopy(newspeak);
  }
  nd->next = NULL;
  nd->prev = NULL;
  return nd;
}

// node print: prints node.
void node_print(Node *n) {
  if (n == NULL) {
    printf("ERROR: Node Not Found. Pointer passed is NULL.\n");
    return;
  }
  if (n->newspeak == NULL) {
    printf("%s\n", n->oldspeak);
    return;
  }
  printf("%s -> %s\n", n->oldspeak, n->newspeak);
  return;
}
// node delete: Deletes the node
void node_delete(Node **n) {
  free((*n)->oldspeak);
  free((*n)->newspeak);
  free(*n);
  return;
}

/*
int main(void){
        char hello[] = "hello world!";
        char world[] = "Goodbye...";
        char *h = &hello[0];
        char *w = &world[0];
        Node *nd = node_create(h, w);
        node_print(nd);
        node_delete(&nd);
        return 0;
}
*/
