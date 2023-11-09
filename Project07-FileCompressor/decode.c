#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "code.h"
#include "stack.h"
#include "pq.h"
#include "header.h"
#include "node.h"
#include "huffman.h"
#include "io.h"
#include "defines.h"
#define OPTIONS "hvi:o:"

//huffman encoding module. Contains main function. Executes huffman encoding on given inputs.
int main(int argc, char **argv) {
	char * infile = NULL;
	char * outfile = NULL;
	int stin = 1;
	int stout = 1;
	int printstats = 0;
	int opt = 0;
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch (opt) {
		// if its p, set p param to the argument
			case 'h':
				fprintf(stderr, "SYNOPSIS\n  A Huffman decoder.\n  Decompresses a file using the Huffman coding algorithm.\n\nUSAGE\n  ./decode [-h] [-i infile] [-o outfile]\nOPTIONS\n\n  -h             Program usage and help.\n  -v             Print compression statistics.\n  -i infile      Input file to decompress.\n  -o outfile     Output of decompressed data.\n");
				return 0;
			case 'v':
				printstats = 1;
				break;
			case 'i':
				infile = (char *)calloc(sizeof(optarg), sizeof(char));
				strcpy(infile, optarg);
				stin = 0;
				break;
			case 'o':
				outfile = (char *)calloc(sizeof(optarg), sizeof(char));
				strcpy(outfile, optarg);
				stout = 0;
				break;
		}
	}
	int f_in;
	int f_out;
	//open files
	if(stin == 1){
		f_in = 0;
		//temp = open("temp.txt", O_WRONLY | O_CREAT);
	}
	else{
		f_in = open(infile, O_RDONLY);
	}
	if(stout ==  1){
		f_out = 1;
	}
	else{
		f_out = open(outfile, O_WRONLY | O_CREAT);
	}
	//make a union to read in the header from the infile
	union hu {
		uint8_t headbuf[sizeof(Header)];
		Header header;
	};
	union hu hunion;
	//read in header
	read_bytes(f_in, &hunion.headbuf[0], sizeof(Header));
	if(hunion.header.magic != MAGIC){
		fprintf(stderr, "Invalid magic number.\n");
		return 1;
	}
	//set outfile permissions
	fchmod(f_out, hunion.header.permissions);
	//read in tree info from infile
	uint8_t * tree = (uint8_t *)calloc((hunion.header.tree_size), sizeof(uint8_t));
	read_bytes(f_in, tree, (hunion.header.tree_size));
	//rebuild the tree
	Node * root = rebuild_tree((hunion.header.tree_size), tree);
	Node * traverser = root;
	//time to traverse file and write to outfile
	uint8_t bit;
	uint8_t out_char[1]; //array for writing out symbols
	//dump_tree(f_out, root);
	//printf("tree size: %d\n", hunion.header.tree_size);
	for(uint64_t counter = 0; counter < (hunion.header.file_size);){
		read_bit(f_in, &bit);
		//fprintf(stderr, "%d", bit);
		if(bit == 0){
			traverser = traverser->left;
			if(traverser->left == NULL && traverser->right == NULL){
				//fprintf(stderr, "\n");
				//fprintf(stderr, "symbol: %c\n", traverser->symbol);
				out_char[0] = traverser->symbol;
				write_bytes(f_out, &out_char[0], 1);
				counter++;
				traverser = root;
			}
		}
		else if(bit == 1){
			traverser = traverser->right;
			if(traverser->left == NULL && traverser->right == NULL){
				//fprintf(stderr, "\n");
				//fprintf(stderr, "symbol: %c\n", traverser->symbol);
				out_char[0] = traverser->symbol;
				write_bytes(f_out, &out_char[0], 1);
				counter++;
				traverser = root;
			}
		}
		
	}
	//struct stat stats;
	//fstat(f_in, &stats);
	if(printstats == 1){
		fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_read);
		fprintf(stderr, "Uncompressed file size: %lu bytes\n", (bytes_written));
		float temphead = bytes_read;
		float tempsize = (bytes_written);
		float spacesave = 100 * (1 - (temphead / tempsize));
		fprintf(stderr, "Space saving: %.2f", spacesave);
		fprintf(stderr, "%%");
		fprintf(stderr, "\n");
	}
	close(f_in);
	close(f_out);
	return 0;
}
