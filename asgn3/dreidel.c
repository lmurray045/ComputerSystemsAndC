#include <stdio.h> // for print f statements
//include "dreidel.h" // for tranferring declared functions to other files
#include "mtrand.h" // for random number generator
// game logic for simulated games of dreidel

char * gamers[] = {"Aharon",
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
	int round_counter = 0;
	while (player_counter < players){
		coin_array[player_counter] = coins;
		player_counter++;
		}
	do{
		int player_id = (counter % num_players);
		if(player_id == 0){
			round_counter += 1;}
		if(coin_array[player_id] < 0){
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
			if(pot % 2 == 0){
				pot = (pot / 2);}
			else{
				pot = (pot / 2) + 1;}
			break;
		case 'N': //player skips
			break;
		case 'S': //player loses coin to pot
			if (coin_array[player_id] == 0){
				coin_array[player_id] = -1;
				players -= 1;
				if (message == 1){
				printf("%s: eliminated in round %d of a %d player game.\n", gamers[player_id], round_counter, num_players);
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
		}
		while (players > 1);
	int winner = 0;
	player_counter = 0;
	while (player_counter < num_players){
		if (coin_array[player_counter] > 0){
			winner = player_counter;
			break;
			}
		else{
			player_counter += 1;
			}
		}
	*rounds = round_counter;
	return winner;
	}


