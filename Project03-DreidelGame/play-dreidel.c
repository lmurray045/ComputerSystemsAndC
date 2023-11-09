#include <stdio.h> //for printf()
#include "dreidel.h" //for dreidel functions
#include "mtrand.h" //for RNG machine
#include <unistd.h> //for getopt()
#include <stdlib.h> //for atoi()
#define OPTIONS "p:c:s:v"


// main function

int main(int argc, char **argv) {
	// set default paramters
	int p = 4;
	int c = 3;
	uint64_t s = 613;
	int v = 0;
	int opt = 0;
	//while there are still unparsed arguments
	while ((opt = getopt(argc, argv, OPTIONS)) != -1){
		//filter argument into catagories
		switch(opt){
			//if its p, set p param to the argument 
			case 'p':
				//SOURCE: atoi(var) command taken from optarg manual, first example
				p = atoi(optarg);
				//ensure p is in paramters
				if (p < 2 || p > 8) {
					return 1;
				}
				break;
			//if c, set c to parameters passes
			case 'c':
				c = atoi(optarg);
				//ensure c is in range
				if (c < 1 || c > 20) {
					return 1;
				}
				break;
			// if its s, set seed to parameters
			case 's':
				s = strtoul(optarg,NULL,10);
				//ensure s is in range
				if (s < 1 || s > 9999999999) {
					return 1;
				}
				break;
			// if v is passed, set message to true
			case 'v':
				v = 1;
				break;
		}
	}
	//generate a seed based on s
	mtrand_seed(s);
	//set rounds variable
	int rounds = 0;
	// create rounds pointer
	int *b = &rounds;
	// create a game with selected paramters
	int dg = play_dreidel(p, c, b, v);
	//print it
	printf("%s %d %d %d %lu\n", (names[dg]), p, c, rounds, s);
	//return 0, all good
	return 0;
}
