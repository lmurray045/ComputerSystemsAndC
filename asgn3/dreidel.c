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
char spin_dreidel(void){
	char rolls[] =  {'G','H','N','S'};
	uint64_t num = (mtrand_rand64() % 4);
	return rolls[num];
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
		coin_array[player_counter] = coins;
		player_counter++;
		}
	do{
		int player_id = (counter % num_players);
		printf("player id = %d \n", player_id);
		printf("player coins = %d \n", coin_array[player_id]);
		if(coin_array[player_id] < 0){
			printf("skipped player %d\n", player_id);
			counter++;
			continue;
			}
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
				printf("players left: %d\n", players);
				if (message == 1){
				printf("TO DO: player elim message\n");
				}
				break;
				}
			else {
				coin_array[player_id] -= 1;
				pot += 1;
				break;
				}
			}
		counter += 1;
		printf("players remaining: %d\n", players);
		}
		while (players > 1);
	printf("exited while loop\n");
	int winner = 0;
	player_counter = 0;
	while (player_counter < num_players){
		printf("player number: %d player coins: %d\n",player_counter, coin_array[player_counter]);
		if (coin_array[player_counter] > 0){
			winner = player_counter;
			break;
			}
		else{
			player_counter += 1;
			}
		}
	*rounds = counter;
	return winner;
	}

int main(void) {
	mtrand_seed(613);
	int x = 0;
	int *b = &x;
	printf("dreidel roll: %c\n", spin_dreidel());
	printf("%d, %d\n", play_dreidel(8,10,b,1), x);
	}


