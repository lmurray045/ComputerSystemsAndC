#include <stdio.h> //for printf()
#include "dreidel.h" //for dreidel functions
#include "mtrand.h" //for RNG machine
#include <unistd.h> //for getopt()
#include <stdlib.h> //for atoi()
#define OPTIONS "p:c:s:v"


// main function

int main(int argc, char **argv) {
	int p = 4;
	int c = 3;
	uint64_t s = 613;
	int v = 0;
	int opt = 0;
	while ((opt = getopt(argc, argv, OPTIONS)) != -1){
		switch(opt){
			case 'p':
				//SOURCE: atoi(var) command taken from optarg manual, first example
				p = atoi(optarg);
				if (p < 2 || p > 8) {
					return 1;
				}
				break;
			case 'c':
				c = atoi(optarg);
				if (c < 1 || c > 20) {
					return 1;
				}
				break;
			case 's':
				s = strtoul(optarg,NULL,10);
				if (s < 1 || s > 9999999999) {
					return 1;
				}
				break;
			case 'v':
				v = 1;
				break;
		}
	}
	mtrand_seed(s);
	int rounds = 0;
	int *b = &rounds;
	int dg = play_dreidel(p, c, b, v);
	printf("%s %d %d %d %lu\n", (names[dg]), p, c, rounds, s);
	return 0;
}
