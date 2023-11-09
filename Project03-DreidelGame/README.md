Liam Murray
lijamurr
cse13s Assignment 3: I have a little Dreidel

The included files are intented to simulate a dreidel game between any number of players between 2-8.

Instructions for use:

run "$make" in your terminal to construct files.
run "./play-dreidel -args" to run, with -args being selected arguments

available arguments:

-p: Players. Selects the number of players in a game. Takes one parameter, an integer between 2 and 8. Default is 4.
-c: Coins. Selects the number of coins in a game. Takes one parameter, an integer between 1 and 20. Default is 3.
-s: Seed. Selects the seed for the random number generator. Takes one parameter, between 1 and 9999999999. Default is 613.
-v: Message. Toggles whether or not a message is displayed upon player elimination. No paramaters. Passing -v turns it on, default is off.
