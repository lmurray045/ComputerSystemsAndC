#include <stdio.h> // for print f statements
//include "dreidel.h" // for tranferring declared functions to other files
#include "mtrand.h" // for random number generator
// game logic for simulated games of dreidel

// define name array
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
	// define array of possible rolls
	char rolls[] =  {'G','H','N','S'};
	// generate a random number take the modulo of 4, giving 0-3
	uint64_t num = (mtrand_rand64() % 4);
	//return the letter corresponding to the number
	return rolls[num];
}

//Play dreidel
int play_dreidel(int num_players, int num_coins, int *rounds, int print){
	// declare an editable player count
	int players = num_players;
	//declares an edittable coin count
	int coins = num_coins;
	//store pot data
	int pot = 0;
	// determine whether the message was enabled
	int message = print;
	// make a counter
	int counter = num_players;
	// make an empty array for coin values
	int coin_array[] = {0,0,0,0,0,0,0,0,0};
	// make a variables to count rounds and to assign coins to players
	int player_counter = 0;
	int round_counter = 0;
	//use a loop to assign coins to the array for the number of players
	while (player_counter < players){
		coin_array[player_counter] = coins;
		player_counter++;
		}
	// use a do while() loop to begin simulating the game
	do{
		// create a player id by finding the % of the counter
		int player_id = (counter % num_players);
		// if its the first players turn, increment the round
		if(player_id == 0){
			round_counter += 1;}
		// if a player has less than zero coins, they're out
		if(coin_array[player_id] < 0){
			counter++;
			continue;
			}
		// collect a roll
		char roll = spin_dreidel();
		// sort the roll into possible catagories
		switch (roll){
		case 'G': //player takes pot
			coin_array[player_id] += pot;
			pot = 0;
			break;
		case 'H': //player takes half pot
			coin_array[player_id] += (pot/2);
			// ensure that no coins are lost due to rounding errors
			if(pot % 2 == 0){
				pot = (pot / 2);}
			else{
				pot = (pot / 2) + 1;}
			break;
		case 'N': //player skips
			break;
		case 'S': //player loses coin to pot
			// if they have no coins to give
			if (coin_array[player_id] == 0){
				//Set coin value to -1, eliminating them
				coin_array[player_id] = -1;
				// decrement player count
				players -= 1;
				//if a message was chosen, print it
				if (message == 1){
				printf("%s: eliminated in round %d of a %d player game.\n", gamers[player_id], round_counter, num_players);
				}
				break;
				}
			//other wise subract coin and add it to pot
			else {
				coin_array[player_id] -= 1;
				pot += 1;
				break;
				}
			}
		//increment counter, incrementing the turn cycle
		counter += 1;
		}
		//while condition for do while loop
		while (players > 1);
		//set winner variable
		int winner = 0;
		// reset player counter to function as loop counter
		player_counter = 0;
		//iterate through the array in a while loop
		while (player_counter < num_players){
			//when a player has more than 0 coins, they won
			if (coin_array[player_counter] > 0){
				winner = player_counter;
				break;
			// otherwise keep going
			}
			else{
				player_counter += 1;
			}
		}
		//set the pointer argument to the rounds in round_counter
		*rounds = round_counter;
		//return the winner
		return winner;
	}


