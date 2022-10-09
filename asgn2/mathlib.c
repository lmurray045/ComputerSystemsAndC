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
	if (x>=0) {}
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

//Sine Function
double my_sine(double x) {
	double last_entry = x;
	long double running_total = x;
	long double EPSILON = 1e-10;
	int counter_n = 1;
	while (my_abs(last_entry) >= EPSILON) 
		{
		double term1 = x / (2.0 * counter_n);
		double term2 = x / ((2.0 * counter_n) + 1);
		double current_val = (last_entry * term1) * term2;
		current_val = my_abs(current_val);
		if (counter_n % 2 == 1 | counter_n == 1) 
			{current_val = -current_val;}
		else {}
		printf("iteration: %d, value: %lf\n", counter_n,
			current_val);
		counter_n++;
		running_total += current_val;
		last_entry = current_val;
		}
	if (-0.0000000001 <= running_total && running_total <= 0.0000000001)
		{running_total = my_abs(running_total);}
	return running_total;
}

int main(void)
{
printf("the sine of %f is %lf \n",(M_PI/2),my_sine(M_PI/2));
printf("the sine of %f is %lf \n",(M_PI),my_sine(M_PI));
printf("the sine of %f is %lf \n",(0.0),my_sine(0.0));
return 0;
}
	
