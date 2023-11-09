#pragma once

//define name array
char * names[] = {"Aharon",
	"Batsheva",
	"Chanah",
	"David",
	"Ephraim",
	"Faige",
	"Gamaleil",
	"Hannah"};
	
//define the functions and constants used universally

extern char spin_dreidel(void);

extern int play_dreidel(int num_players, int num_coins, int *rounds, int print);

int max_players = 8;
int max_coins = 10;
