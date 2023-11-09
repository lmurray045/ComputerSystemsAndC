Liam Murray
Lijamurr
CSE13s
November 20, 2022

#### Assignment 6: The Great Firewall of Santa Cruz

Goal: To create a firewall to censor and monitor the speech of the citizens of the People's Republic of Santa Cruz.

##### Included Files
	banhammer.c - contains main program and firewall filter code.
	
	ht.c - contains functions and logic for the chained hashtable.
	
	bf.c - contains functions and logic for the bloomfilter.
	
	bv.c - contains functions and logic for the bit vector used in the 
	bloomfilter.
	
	ll.c - contains functions and logic for the doubly linked list used 
	in the hashtable.
	
	node.c - contains functions and logic for the nodes used in the 
	linked list.
	
	parser.c - contains functions and logic for the parsing function, 
	used to gather input from the input file, stdin.
	
	city.c - contains code for the hash function used in the Hashtable
	and the bloom filter.
	
	all .h files: function definitions for respective .c files.
	
	badspeak.txt: list of all banned badspeak words.
	
	newspeak.txt: list of all banned oldspeak words with newspeak 
	translations.
	
	DESIGN.pdf: contains the implementation of included programs with
	pseudocode.
	
	WRITEUP.pdf: contains a writeup of the program performance and 
	statistics.
	
	Messages.h: contains the messages printed by banhammer.c.
	
	Makefile: makes banhammer executable and related files.
	
##### Creation and Usage

Create the banhammer executable by navigating to the appropriate directory on
the command line, and running "make" or "make all". 

The program can then be run using "./banhammer -[args]". Pipe input into the 
program using 'echo "[input]" | ./banhammer'.

##### Available Options

Usage: ./banhammer [options]
  ./banhammer will read in words from stdin, identify any badspeak or old speak and output an
    appropriate punishment message. The badspeak and oldspeak (with the newspeak translation) 
    that caused the punishment will be printed after the message. If statistics are enabled
      punishment messages are suppressed and only statistics will be printed.
      -t <ht_size>: Hash table size set to <ht_size>. (default: 10000)
      -f <bf_size>: Bloom filter size set to <bf_size>. (default 2^19)
      -s          : Enables the printing of statistics.
      -m          : Enables move-to-front rule.
      -h          : Display program synopsis and usage.
      
###### Additional "make" Commands

"Make clean" removes derived files made during "make" process. 
"Make format" formats code in clang-format. 
"Make Spotless" removes all derived files.

      
