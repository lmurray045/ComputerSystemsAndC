Liam Murray
Lijamurr
cse13s fall 2022

Included Files:

README.md	  - description of files with use instructions
mathlib.c         - contains self implemented versions of several 
		    math.h functions
mathlib-test.c    - Test harness for mathlib.c functions
mathlib.h         - Prototype file for functions in mathlib.c
DESIGN.pdf        - Contains a description and pseudocode for
 		    included source code files
WRITEUP.pdf       - Contains a discussion of the results of running 
		    tests on the math library
Makefile          - Used to compile and clean the included c 
		    source code.
		    
Instructions for use:
run: "$make all" or "$make" on your terminal to compile provided souce code files.
run "$./mathlib-test -[args]" to run the tests in mathlib-tests.
mathlib-test can accept any number of available arguments.

arguments accepted:
	-a: run all tests
	-s: run sine function tests
	-c: run cosine function tests
	-S: run arcsine function tests
	-C: run arccosine function tests
	-T: run arctangent function tests
	-l: run log function tests
	

