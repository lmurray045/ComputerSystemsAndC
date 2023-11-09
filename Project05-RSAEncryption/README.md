Assignment 5: Public key cryptography
Liam Murray
Lijamurr
CSE13s, November 6, 2022

Purpose: 
The purpose of the included files is to implement a rudamentary RSA 
encryption algorithm, in order to learn about and experience encryption in a 
tangible circumstance.

Included files:

Design: 
	Pseudocode describing program implementation.
	
Writeup:
	Writeup of program results.
	
Makefile: 
	Compiles files into executables.

randstate.c/.h:
	Includes functions for initilization and usage of random number 
	generators and random states.
numtheory.c/.h:
	Contains the mathamatical functions used in the creation and 
	calculation of rsa related numbers.
rsa.c/.h:
	Contains RSA related functions used when interacting with data
	directly, such as when encrypting and decrypting data.
Main Functions/ Executables:

keygen - ./keygen:
Generates a public / private key pair, placing the keys into the public and 
private key files as specified below. The keys have a modulus (n) whose 
length is specified in the program options.
   -s <seed>   : Use <seed> as the random number seed. Default: time()
   -b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024
   -i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50
   -n <pbfile> : Public key file is <pbfile>. Default: rsa.pub
   -d <pvfile> : Private key file is <pvfile>. Default: rsa.priv
   -v          : Enable verbose output.
   -h          : Display program synopsis and usage.
   

encrypt - ./encrypt:
Generates encoded cyphertext, reading a message from the input and storing it 
in the output as specified below. The cyphertext is generated based off of a 
public key, which is read via the input specified below.
    -i <input>   : read the message to be encrypted from <input>. Default: stdin
    -o <output>   : store the generated cyphertext into <output>. Default: stdout
    -n <public key file>  : gather the public key information from <public key file>. Default: 'rsa.pub'
    -v          : Enable verbose output.
    -h          : Display program synopsis and usage.
   
    
decrypt - ./decrypt
Decodes cyphertext, reading the encrypted message from the input and storing 
it in the output as specified below. The message is decrypted based off of a 
private key, which is read via the input specified below.
    -i <input>   : reads the cyphertext to decode from <input>. Default: stdin
    -o <output>   : store the decrypted message into <output>. Default: stdout
    -n <private key file>  : gather the private key information from <private key file>. Default: 'rsa.priv'
    -v          : Enable verbose output.
    -h          : Display program synopsis and usage.
    
