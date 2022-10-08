//File containing self implemented math functions

#include <math.h> //for constants such as pi
#include <stdio.h>

// lower level math functions for assistance computting more complex functions

double EPSILON = 1e-10;

//Factorial Function

int my_factorial(int num) {
	int starting_val = num;
	int current = num;
	while (current > 1) {
		current -= 1;
		starting_val = starting_val * current;
	}
	return starting_val;
}

//Exponent Function

int my_exponent(int base, int exponent){
	int b_input = base;
	int m_value = base;
	int x_input = exponent;
	while (x_input > 0){
		b_input = b_input * m_value;
		x_input -= 1;
	}
	return b_input;
}

//Absolute Value Function
double my_abs(double x){
	double abs_x = x;
	if (x>0) {}
	else {abs_x=-abs_x;}
	return abs_x;
	} 

//Square Root function
//SOURCE CITATION: Taken from professor Miller's Piazza post.

double my_sqrt(double x) {
    double value = 1.0;
    double EPSILON = 1e-10;
    for (double guess = 0.0; my_abs(value - guess) > EPSILON; value = (value 
    + x / value) / 2.0) {
        guess = value;
    }
    return value;
}

int main(void)
{
printf("the absolute value of %d is %f \n",-4,my_abs(-4.0));
printf("the root of %d is %f \n",32,my_sqrt(32));
return 0;
}
	
