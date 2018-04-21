#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "memory.h"

double* runge(double* x, int n);
double* lar(double* x, double* y, int n);
double** tri(double* x, double* y, int n);

int main(){
	int n, i;
	double h = 0.0;
	double *x;
	double *y;
	for(n = 10; n <= 20; n += 10){
		h = 10.0 / n;
		x = (double *)malloc((n+1)*sizeof(double));
		for(i = 0; i <= n; i++){
			x[i] = -5.0 + i*h;
		}
		y = runge(x, n);
		double *lar_param = lar(x, y, n);
		for (i = n; i >= 0; i--){
			printf("Degree[%d]: %.5f\n", i, lar_param[i]);
		}
		double **tri_param = tri(x, y, n);
		for(i = 0; i < n; i++){
			printf("Segment[%d]: %.5f x^3 + %.5f x^2 + %.5f x + %.5f\n", i, tri_param[i][0], tri_param[i][1], tri_param[i][2], tri_param[i][3]);
		}
		free(x);
		free(y);
		free(lar_param);
		for(i = 0; i < n; i++)
			free(tri_param[i]);
		free(tri_param);
	}
	return 0;
}

double* runge(double *x, int n){
	double *y = (double *)malloc((n+1)*sizeof(double));
	int i;
	for(i = 0; i <= n; i++){
		y[i] = 1.0 / (1.0 + 16.0 * x[i]);
	}
	return y;
}

double* lar(double* x, double* y, int n){
	double *para = (double *)malloc((n+1)*sizeof(double));
	memset(para, 0, sizeof(double)*(n+1));
	int i, j, k;
	double *l = (double *)malloc((n+1)*sizeof(double));
	for(i = 0; i <= n; i++){
		memset(l, 0, sizeof(double)*(n+1));
		l[0] = 1.0;
		//consider every base function
		double w = 1.0;
		for(j = 0; j <= n; j++){
			if(j != i){
				for(k = n; k >= 1; k--){
					l[k] = l[k-1] - x[j]*l[k];
				}
				l[0] = -x[j]*l[0];
				w *= (x[i] - x[j]);
			}
		}
		for(j = 0; j <= n; j++){
			para[j] += y[i]*l[j]/w;
		}
	}
	free(l);
	return para;	
}

double** tri(double* x, double* y, int n){
	int i;
	double dl = 160.0/(401.0*401.0);
	double dr = -dl;
	double h = 10.0/n;
	double **tri_param = (double **)malloc(n*sizeof(double *));
	for(i = 0; i < n; i++){
		tri_param[i] = (double *)malloc(4*sizeof(double));
		memset(tri_param[i], 0, 4*sizeof(double));
	}

	//Calculate the value of vec(d)
	double *d = malloc((n+1)*sizeof(double));
	d[0] = 6.0/h*((y[1] - y[0])/h-dl);
	d[n] = 6.0/h*(dr - (y[n] - y[n-1])/h);
	for(i = 1; i < n; i++){
		d[i] = 3.0*(y[i-1] + y[i+1] - 2*y[i])/(h*h);
	}
	double *M = malloc((n+1)*sizeof(double));
	double *beta = malloc(n*sizeof(double));
	double *yy = malloc((n+1)*sizeof(double));
	
	//Proofread process
	beta[0] = 1.0/2.0;
	for(i = 1; i < n; i++){
		beta[i] = 1.0/(4.0 - beta[i]);
	}
	yy[0] = d[0]/2.0;
	for(i = 1; i <= n-1; i++){
		yy[i] = (d[i] - 1.0/2.0*yy[i-1])/(2.0 - 1.0/2.0*beta[i-1]);
	}
	yy[n] = (d[i] - yy[n-1])/(2.0 - beta[i-1]);
	
	//Correct process
	M[n] = yy[n];
	for(i = n-1; i>=0; i--){
		M[i] = yy[i] - beta[i]*M[i+1];
	}

	//Calculate original parameters
	for(i = 0; i < n; i++){
		double aa,bb,cc,dd;
		aa = M[i]/(6.0*h);
		bb = M[i+1]/(6.0*h);
		cc = y[i]/h - M[i]*h/6.0;
		dd = y[i+1]/h - M[i+1]*h/6.0;
		tri_param[i][0] = bb - aa;
		tri_param[i][1] = 3.0*aa*x[i+1] - 3.0*bb*x[i];
		tri_param[i][2] = dd - cc + 3.0*bb*x[i]*x[i] - 3.0*aa*x[i+1]*x[i+1];
		tri_param[i][3] = aa*x[i+1]*x[i+1]*x[i+1] - bb*x[i]*x[i]*x[i] + cc*x[i+1] - dd*x[i];
	}
	free(M);
	free(beta);
	free(yy);
	free(d);
	return tri_param;
}

