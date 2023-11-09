Liam Murray
Professor Miller
CSE13s: Fall 2022
December 4, 2022

## A (Huffman Coding) Tree Grows in Santa Cruz: Assignment 7

The basic idea of this assignment is to create a file compression and
decompression program based on the huffman coding algorithm.

### Included Files

encode.c: contains main program for encoding and compressing a file.
decode.c/h: contains main program for encoding and compressing a file.
stack.c/h: contains implementation of stack ADT.
pq.c/h: contains implementation of Priority Queue ADT.
node.c/h: contains implementation of node ADT.
code.c/h: contains implementation for constructing character codes.
huffman.c/h: contains implementation of functions related to the huffman algorithm.
io.c/h: contains implementation of functions relating to file read/write io.
header.h: contains definition of "header" object type
defines.h: contains definitions of global variables
DESIGN.pdf: describes implementation of above files
README.md: contains program information and usage.

### Usage

#### Encode

SYNOPSIS
  A Huffman encoder.
    Compresses a file using the Huffman coding algorithm.
    
    USAGE
      ./encode [-h] [-i infile] [-o outfile]
      
      OPTIONS
        -h             Program usage and help.
        -v             Print compression statistics.
        -i infile      Input file to compress.
        -o outfile     Output of compressed data.
        
#### Decode

SYNOPSIS
  A Huffman Decoder.
    Decompresses a file using the Huffman coding algorithm.
    
    USAGE
      ./decode [-h] [-i infile] [-o outfile]
      
      OPTIONS
        -h             Program usage and help.
        -v             Print compression statistics.
        -i infile      Input file to decompress.
        -o outfile     Output of decompressed data.
        
#### Makefile

Generate Encode and Decode executables by running "Make encode" or "Make decode".
Running "Make" or "Make all" generates both.

Additonal commands:
	make clean: remove derived files
	make spotless: remove all derived files, including executables
	make format: formats the c code into clang format
	
        
