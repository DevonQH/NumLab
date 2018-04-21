#include"math.h"
#include"stdio.h"

int num_points = 7;
double data_x[] = {-1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0};
double data_y[] = {-4.467, -0.452, 0.551, 0.048, -0.447, 0.549, 4.552};

void lin(double x[], double y[], int n);
void quad(double x[], double y[], int n);
void tri(double x[], double y[], int n);

int main(){

	lin(data_x, data_y, num_points);
	quad(data_x, data_y, num_points);
	tri(data_x, data_y, num_points);

	return 0;
}

double sum(int n, double x[], int mode){
	double summ = 0.0;
	int i = 0;
	for(i = 0; i < n; i++){
		if(mode) summ += x[i]*x[i];
		else summ+= x[i];
	}
	return summ;
}

double dot(int n, double x[], double y[]){
	double summ = 0.0;
	int i = 0;
	for(i = 0; i < n; i++){
		summ += x[i]*y[i];
	}
	return summ;
}

void lin(double x[], double y[], int n){
	//linear interpolate
	double phi00 = (double) n;
	double phi01 = sum(n, x, 0);
	double phi10 = phi01;
	double phi11 = sum(n, x, 1);
	double phi0f = sum(n, y, 0);
	double phi1f = dot(n, x, y);

	double a = (phi11*phi0f - phi10*phi1f)/((double)n*phi11 - phi10*phi01);
	double b = ((double)n*phi1f - phi10*phi0f)/((double)n*phi11 - phi10*phi01);

	int i = 0;
	double error = 0;
	for(i = 0; i < n; i++){
		error += (y[i] - (a*x[i]+b))*(y[i] - (a*x[i]+b));
	}
	
	printf("The linear regression is: %f *x + %f.\n", a, b);
	printf("The L2 error of linear regression is %f.\n", error);

}

void quad(double x[], double y[], int n){

	double phi01 = sum(n, x, 0);
	double phi0f = sum(n, y, 0);
	double phi1f = dot(n, x, y);
	double phi11 = sum(n, x, 1);
	double a1 = (n*phi1f - phi01*phi0f) / (n*phi11 - phi01*phi01);
	double a0 = phi0f/n - a1*phi01/n;
	double e = y[0] - a0 - a1*x[0];

	int i = 0;
	float error = 0.0;
	for(i = 0; i < n; i++){
		phi01 = y[i] - (e*x[i]*x[i] + a1*x[i] + a0);
		error += phi01*phi01;
	}

	printf("The quadratic regression is %f * x^2 + %f * x + %f.\n", e, a1, a0);
	printf("The L2 error of the quadratic regression is %f.\n", error);
}

void tri(double x[], double y[], int n){


}
