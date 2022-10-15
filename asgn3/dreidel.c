#include <stdio.h> // for print f statements
//include "dreidel.h" // for tranferring declared functions to other files
#include "mtrand.h" // for random number generator
// game logic for simulated games of dreidel

//name array
char * names[] = {"Aharon",
	"Batsheva",
	"Chanah",
	"David",
	"Ephraim",
	"Faige",
	"Gamaleil",
	"Hannah"};

//spin dreidel
char spin_dreidel(){
	char * rolls[] =  {"G","H","N","S"};
	uint64_t num = (mtrand_rand64() % 4);
	return *rolls[num];
}

//Play dreidel
int play_dreidel(int num_players, int num_coins, int *rounds, int print){
	int players = num_players;
	int coins = num_coins;
	int pot = 0;
	int message = print;
	int counter = num_players;
	int coin_array[] = {0,0,0,0,0,0,0,0,0};
	int player_counter = 0;
	while (player_counter < players){
		coin_array[counter] = coins;
		counter++;
		}
	while (players > 0){
		int player_id = counter % num_players;
		if (coin_array[player_id] < 0)
			break;
		char roll = spin_dreidel();
		switch (roll){
		case 'G': //player takes pot
			coin_array[player_id] += pot;
			pot = 0;
			break;
		case 'H': //player takes half pot
			coin_array[player_id] += (pot/2);
			pot = 0;
			break;
		case 'N': //player skips
			break;
		case 'S': //player loses coin to pot
			if (coin_array[player_id] == 0){
				coin_array[player_id] = -1;
				players -= 1;
				if (message == 1){
				printf("TO DO: player elim message");
				}
				}
			else {
			coin_array[player_id] -= 1;
			pot += 1;
			}
			}
			break;
		counter += 1;
		}
	int winner = 0;
	while (player_counter > 0){
		if (coin_array[player_counter] > 0){
			winner = player_counter;
			break;
		player_counter -= 1;
		}
		}
	*rounds = counter;
	return winner;
	}

int main(void) {
	mtrand_seed(613);
	int x = 0;
	int *b = &x;
	printf("%d, %d\n", play_dreidel(8,10,b,1), x);
	}


