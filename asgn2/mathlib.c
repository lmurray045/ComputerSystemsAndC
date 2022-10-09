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
double my_sin(double x) {
	double num = my_abs(x);
	double last_entry = num;
	long double running_total = num;
	long double EPSILON = 1e-10;
	int counter_n = 1;
	while (my_abs(last_entry) >= EPSILON) 
		{
		double term1 = num / (2.0 * counter_n);
		double term2 = num / ((2.0 * counter_n) + 1);
		double current_val = (last_entry * term1) * term2;
		current_val = my_abs(current_val);
		if (counter_n % 2 == 1 | counter_n == 1) 
			{current_val = -current_val;}
		else {}
		counter_n++;
		running_total += current_val;
		last_entry = current_val;
		}
	if (x < 0)
		{running_total = -running_total;}
	if (-0.0000000001 <= running_total && running_total <= 0.0000000001)
		{running_total = my_abs(running_total);}
	return running_total;
}

// Cosine Function
// Cosine is actually just the sine function, with the inputted number being shifted via (pi/2 - x). Therefore, the more efficient implentation of cosine is simply a shifted over sine.
double my_cos(double x) {
	double input = x;
	input = (M_PI/2) - x;
	return my_sin(input);
}

// Arcsine function
double my_arcsin(double x) {
	double input = x;
	double last_val = input;
	double EPSILON = 1e-10;
	double prev;
	double new_term;
	do {
		prev = last_val;
		double term1 = my_sin(last_val) - x;
		double term2 = my_cos(last_val);
		new_term = last_val - (term1 / term2);
		last_val = new_term;}
	while (my_abs(new_term - prev) > EPSILON);
	return last_val;
}

int main(void)
{
printf("the arcsine of %f is %lf \n",(-1.0),my_arcsin(-1.0));
printf("the arcsine of %f is %lf \n",(0.0),my_arcsin(0.0));
printf("the arcsine of %f is %lf \n",(0.5),my_arcsin(0.5));
printf("the arcsine of %f is %lf \n",(1.0),my_arcsin(1.0));
return 0;
}
	
