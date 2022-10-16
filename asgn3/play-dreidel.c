#include <stdio.h> //for printf()
#include "dreidel.h" //for dreidel functions
#include "mtrand.h" //for RNG machine
#include <unistd.h> //for getopt()
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
				p = *optarg;
				break;
			case 'c':
				c = *optarg;
				break;
			case 's':
				s = *optarg;
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
	
}
