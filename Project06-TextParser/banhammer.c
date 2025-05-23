#include "bf.h"
#include "bv.h"
#include "city.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "node.h"
#include "parser.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "ht:f:sm"

int main(int argc, char **argv) {
  uint32_t htsize = 10000;
  uint32_t bfsize = pow(2, 19);
  bool mtf = false;
  int statprint = 0;
  int opt = 0;
  while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
    switch (opt) {
    // if its p, set p param to the argument
    case 'h':
      fprintf(
          stderr,
          "Usage: ./banhammer [options]\n  ./banhammer will read in words from "
          "stdin, identify any badspeak or old speak and output an\n  "
          "appropriate punishment message. The badspeak and oldspeak (with the "
          "newspeak translation) \n  that caused the punishment will be "
          "printed after the message. If statistics are enabled\n  punishment "
          "messages are suppressed and only statistics will be printed.\n    "
          "-t <ht_size>: Hash table size set to <ht_size>. (default: 10000)\n  "
          "  -f <bf_size>: Bloom filter size set to <bf_size>. (default "
          "2^19)\n    -s          : Enables the printing of statistics.\n    "
          "-m          : Enables move-to-front rule.\n    -h          : "
          "Display program synopsis and usage.\n");
      return 0;
    case 't':
      htsize = strtoul(optarg, NULL, 10);
      break;
    case 'f':
      bfsize = strtoul(optarg, NULL, 10);
      break;
    case 'm':
      mtf = true;
      break;
    case 's':
      statprint = 1;
      break;
    }
  }
  BloomFilter *bf = bf_create(bfsize);
  HashTable *ht = ht_create(htsize, mtf);
  FILE *bs = fopen("badspeak.txt", "r");
  Parser *badparse = parser_create(bs);
  // pointer for badspeak, which has no newspeak translation
  char *nullnewspeak = NULL;
  char wordbuf[1001];
  char *word = &wordbuf[0];
  // int counter = 0;
  while (next_word(badparse, word) == true) {
    bf_insert(bf, word);
    ht_insert(ht, word, nullnewspeak);
    // counter += 1;
    // printf("counter: %d\n", counter);
  }
  fclose(bs);
  FILE *ns = fopen("newspeak.txt", "r");
  Parser *newparse = parser_create(ns);
  char newword[1000];
  char *new = &newword[0];
  while (next_word(newparse, word) == true) {
    next_word(newparse, new);
    bf_insert(bf, word);
    ht_insert(ht, word, new);
  }
  fclose(ns);
  // printf("loop two exited\n");
  FILE *std = stdin;
  Parser *censor = parser_create(std);
  LinkedList *crimes = ll_create(false);
  LinkedList *mistakes = ll_create(false);
  while (next_word(censor, word) == true) {
    // printf("first if\n");
    if (bf_probe(bf, word) == true) {
      // printf("second if\n");
      // printf("word: %s\n", word);
      Node *banned = ht_lookup(ht, word);
      // printf("banned made\n");
      if (banned != NULL) {
        // printf("third if\n");
        if ((banned->newspeak) != NULL) {
          // printf("final\n");
          ll_insert(mistakes, word, banned->newspeak);
        } else {
          // printf("first else\n");
          ll_insert(crimes, word, NULL);
        }
      } else {
      }
    }
  }
  fclose(std);
  // printf("check loop exited\n");
  if (statprint == 0) {
    if (ll_length(crimes) != 0 && ll_length(mistakes) != 0) {
      printf("%s", mixspeak_message);
      ll_print(crimes);
      ll_print(mistakes);
    } else if (ll_length(crimes) != 0 && ll_length(mistakes) == 0) {
      printf("%s", badspeak_message);
      ll_print(crimes);
    } else if (ll_length(crimes) == 0 && ll_length(mistakes) != 0) {
      printf("%s", badspeak_message);
      ll_print(mistakes);
    }
  }

  else {
    uint32_t ht_keys = 0;
    uint32_t ht_hits = 0;
    uint32_t ht_misses = 0;
    uint32_t ht_examined = 0;
    uint32_t bf_keys = 0;
    uint32_t bf_hits = 0;
    uint32_t bf_misses = 0;
    uint32_t bf_examined = 0;
    ht_stats(ht, &ht_keys, &ht_hits, &ht_misses, &ht_examined);
    bf_stats(bf, &bf_keys, &bf_hits, &bf_misses, &bf_examined);
    // uint32_t ht_probes = ht_hits + ht_misses;
    float bepm;
    float fb = bf_examined;
    float fh = bf_hits;
    float be = (fb - (N_HASHES * fh));
    if (bf_misses == 0) {
      bepm = 0.0000;
    } else {
      bepm = be / bf_misses;
    }
    float falsepos = ht_misses / fh;
    float bfc = bf_count(bf);
    float bfs = bf_size(bf);
    float bf_load = (bfc / bfs);
    float fht = ht_examined;
    float avg_seek_len = fht / (ht_hits + ht_misses);
    printf("ht keys: %u\n", ht_keys);
    printf("ht hits: %u\n", ht_hits);
    printf("ht misses: %u\n", ht_misses);
    printf("ht probes: %u\n", ht_examined);
    printf("bf keys: %u\n", bf_keys);
    printf("bf hits: %u\n", bf_hits);
    printf("bf misses: %u\n", bf_misses);
    printf("bf bits examined: %u\n", bf_examined);
    printf("Bits examined per miss: %.6f\n", bepm);
    printf("False Positives: %.6f\n", falsepos);
    printf("Average seek length: %.6f\n", avg_seek_len);
    printf("Bloom filter load: %.6f\n", bf_load);
  }

  // bf_print(bf);
  // ht_print(ht);

    ht_delete(&ht);
    bf_delete(&bf);
    ll_delete(&crimes);
    ll_delete(&mistakes);
    parser_delete(&badparse);
    parser_delete(&newparse);
    parser_delete(&censor);
  
  return 0;
}
