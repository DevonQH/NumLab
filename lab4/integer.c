#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EXP 2.718281828

void trapezium(double, double, int);

int main(){
	trapezium(0.0,1.0,476);
	return 0;
}

void trapezium(double l, double r, int steps){
	double h = (r-l)/(double)steps;
	int i = 0;
	double integer = 0.0, ll = 0.0, rr = h;
	for(i = 0; i < steps; i++){
		integer += (pow(EXP, ll)+pow(EXP,rr))*(h/2.0);
		ll += h;
		rr += h;
	}
	double real = EXP-1.0;
	printf("The trapezium integral is %.8f.\n", integer);
	printf("The real integral is %.8f.\n", real);
}


