#include "huffman.h"
#include "io.h"
#include "pq.h"
#include "stack.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// huffman code implementation

// build a huffman tree, and return its root node
Node *build_tree(uint64_t hist[static ALPHABET]) {
  PriorityQueue *pq = pq_create(ALPHABET);
  for (uint64_t i = 0; i < ALPHABET; i++) {
    if (hist[i] > 0) {
      Node *n = node_create(i, hist[i]);
      enqueue(pq, n);
    }
  }
  Node *parent;
  while (pq_size(pq) > 1) {
    Node *n1;
    dequeue(pq, &n1);
    Node *n2;
    dequeue(pq, &n2);
    // if(n1 != NULL && n2 != NULL){
    parent = node_join(n1, n2);
    //}
    // else{
    enqueue(pq, parent);
    //}
  }
  return parent;
}

// auxillary function for recursive searching
void traverse_code(Code *code, Node *n, uint8_t pushcode,
                   Code table[static ALPHABET]) {
  uint8_t throwaway;
  if (pushcode == 1) {
    code_push_bit(code, 1);
  } else if (pushcode == 0) {
    code_push_bit(code, 0);
  }
  if (n != NULL) {
    traverse_code(code, n->left, 0, table);
    if (n->left == NULL && n->right == NULL) {
      table[n->symbol] = *code;
      code_pop_bit(code, &throwaway);
      return;
    }
    traverse_code(code, n->right, 1, table);
    if (n->left == NULL && n->right == NULL) {
      table[n->symbol] = *code;
      code_pop_bit(code, &throwaway);
      return;
    }
  }
  if (code_empty(code) == false) {
    code_pop_bit(code, &throwaway);
  }
  return;
}

// build codes: traverses code table and builds the codes for it.
void build_codes(Node *root, Code table[static ALPHABET]) {
  Code code = code_init();
  traverse_code(&code, root, 2, table);
  return;
}

// dump the tree, so that it can reconstructed
void dump_tree(int outfile, Node *root) {
  if (root != NULL) {
    dump_tree(outfile, root->left);
    dump_tree(outfile, root->right);
    if (root->left == NULL && root->right == NULL) {
      uint8_t buf[] = {'L', root->symbol};
      write_bytes(outfile, &buf[0], 2);
      return;
    } else {
      uint8_t buf[] = {'I'};
      write_bytes(outfile, &buf[0], 1);
      return;
    }
  }
  return;
}

// rebuild the tree based on what it dumped :)
Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
  Stack *s = stack_create(nbytes);
  for (uint16_t i = 0; i < nbytes; i++) {
    if (tree[i] == 'L') {
      Node *n1 = node_create(tree[i + 1], 1);
      i++;
      stack_push(s, n1);
    } else if (tree[i] == 'I') {
      Node *nr;
      stack_pop(s, &nr);
      Node *nl;
      stack_pop(s, &nl);
      Node *parent = node_join(nl, nr);
      stack_push(s, parent);
    }
  }
  Node *root;
  stack_pop(s, &root);
  return root;
}

// deletes a tree
void delete_tree(Node **root) {
  if ((*root) != NULL) {
    delete_tree(&((*root)->left));
    delete_tree(&((*root)->right));
    node_delete(root);
  }
  return;
}
/*
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
        for(counter = 1; counter != 500 && read_bit(fd, &bit) == true;
counter++){ printf("%d", bit); if(counter % 8 == 0 && counter != 0){ printf("
");
                }
        }
        printf("\n");
        int fdo = open("example2.txt", O_WRONLY | O_CREAT);
        dump_tree(fdo, parent);
        close(fdo);
        uint8_t dump[11];
        int fdi = open("example2.txt", O_RDONLY);
        read_bytes(fdi, &dump[0], 11);
        close(fdi);
        parent = rebuild_tree(11, dump);
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
        delete_tree(&parent);
        return 0;
}
*/
