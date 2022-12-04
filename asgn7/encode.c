#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/stat.h>
#include <fcntl.h>
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
	uint64_t hist[ALPHABET] = {0};
	Code table[ALPHABET];
	char * infile = NULL;
	char * outfile = NULL;
	int stin = 1;
	int stout = 1;
	int opt = 0;
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch (opt) {
		// if its p, set p param to the argument
			case 'h':
				fprintf(stderr, "Help Message\n");
				return 0;
			case 'v':
				fprintf(stderr, "Statistics\n");
				break;
			case 'i':
				infile = (char *)calloc(sizeof(optarg), sizeof(char));
				*infile = *optarg;
				stin = 0;
				break;
			case 'o':
				outfile = (char *)calloc(sizeof(optarg), sizeof(char));
				*outfile = *optarg;
				stout = 0;
				break;
		}
	}
	int f_in;
	int temp;
	int f_out;
	//f_in 2 is used for reading the file a second time
	if(stin == 1){
		f_in = 0;
		temp = open("temp.txt", O_WRONLY | O_CREAT);
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
	uint8_t buf[1];
	while(read_bytes(f_in, &buf[0], 1) == true){
		hist[buf[0]] += 1;
		if(stin == 1){
			write_bytes(temp, &buf[0], 1); 
		}
	}
	if(stin == 1){
		close(temp);
	}
	if(hist[0] == 0){
		hist[0] = 1;
	}
	if(hist[1] == 1){
		hist[1] = 1;
	}
	//calculates the size of the tree
	uint16_t counter = 0;
	for(uint64_t i = 0; i < ALPHABET; i++){
		if(hist[i] != 0){
			counter++;
		}
	}
	counter = (3 * counter) - 1;
	//for(uint64_t i = 0; i < ALPHABET; i++){
	//	printf("%lu ", hist[i]);
	//}
	//printf("\n");
	//build tree and codes
	Node * root = build_tree(hist);
	build_codes(root, table);
	
	//make header and get file information
	struct stat stats;
	if(stin == 0){
		fstat(f_in, &stats);
	}
	else{
		int stat_file = open("temp.txt", O_RDONLY);
		fstat(stat_file, &stats);
		close(stat_file);
	}
	Header *header = (Header *)malloc(sizeof(Header));
	header->magic = MAGIC;
	header->permissions = stats.st_mode;
	header->tree_size = counter;
	header->file_size = stats.st_size;
	//store header in a union
	//SOURCE CITATION: the class discord pointed me to the use unions. I then searched up syntax and usage.
	union Head{
		uint8_t buf[sizeof(Header)];
		Header header;
	};
	union Head head;
	head.header = (*header);
	for(int i = 0; i < 16; i++){
		printf("%d ", head.buf[i]);
	}
	printf("\n");
	fchmod(f_out, (&stats)->st_mode);
	//write out the header
	write_bytes(f_out, &(head.buf)[0], sizeof(Header));
	//dump the tree
	dump_tree(f_out, root);
	//parse infile, writing to outfile for each character
	close(f_in);
	int f_in2;
	if(stin == 1){
		f_in2 = open("temp.txt", O_RDONLY);
	}
	else{
		f_in2 = open(infile, O_RDONLY);
	}
	uint8_t readbuf[1];
	while(read_bytes(f_in2, &readbuf[0], 1) > 0){
		write_code(f_out, &table[readbuf[0]]);
	}
	flush_codes(f_out);
	close(f_in2);
	//SOURCE CITATION: I had to lookup how to use the remove function. I found the man page for it, but still used google for help.
	remove("temp.txt");
	close(f_out);
	return 0;
	//
}
