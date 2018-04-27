#include "stdio.h"
#include "math.h"
#include "memory.h"

#define N 3

void init(double ** H);
double abbs(double x) {return (x > 0)? x : -x;};
void print(double ** H);
void printt(double * x);
void calc(double ** H, double * b);
void solve(double ** H, double * b, double * x);
void error(double ** H, double * b, double * x);

int main() {

	int i, j, k;
	
	double ** H;
	H = (double **)malloc(N*sizeof(double *));
	for(i = 0; i < N; i++){
		H[i] = (double *)malloc(N*sizeof(double));
		memset(H[i], 0, sizeof(double)*N);
	}
	
	init(H);
	
	double *b = (double*)malloc(N*sizeof(double));
	memset(b, 0, sizeof(double)*N);
	calc(H, b);
	
	double *x = (double*)malloc(N*sizeof(double));
	memset(x, 0, sizeof(double)*N);
	solve(H, b, x);

	error(H, b, x);

	for(i = 0; i < N; i ++) b[i] += 1e-7;

	memset(x, 0, sizeof(double)*N);
	solve(H, b, x);

	error(H, b, x);

	return 0;
}

void print(double ** H){
	int i, j;
	for(i = 0; i < N; i ++){
		for(j = 0; j < N; j ++){
			printf("%.8f ", H[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void printt(double * x){
	int i;
	for(i = 0; i < N; i ++){
		printf("%.8f ", x[i]);
	}
	printf("\n");
	printf("\n");
}

void init(double ** H){
	int i, j;
	for(i = 0; i < N; i ++){
		for(j = 0; j < N; j ++){
			H[i][j] = 1.0/((double)i+j+1.0);
		}
	}
}

void calc(double ** H, double *b){
	int i, j;
	for(i = 0; i < N; i ++){
		for(j = 0; j < N; j ++){
			b[i] += H[i][j];
		}
	}
}

void solve(double ** H, double * b, double * x){
	
	int i, j, r;
	double ** L;
	double ** U;
	L = (double **)malloc(N*sizeof(double *));
	U = (double **)malloc(N*sizeof(double *));
	for(i = 0; i < N; i++){
		L[i] = (double *)malloc(N*sizeof(double));
		memset(L[i], 0, sizeof(double)*N);
		L[i][i] = 1.0;
		U[i] = (double *)malloc(N*sizeof(double));
		memset(U[i], 0, sizeof(double)*N);
	}
	for(i = 0; i < N; i ++){
		U[0][i] = H[0][i];
		L[i][0] = H[i][0]/U[0][0];
	}
	for(r = 1; r < N; r ++){
		for(i = r; i < N; i ++){
			double sum = 0.0;
			for(j = 0; j < r; j ++){
				sum += L[r][j]*U[j][i];
			}
			U[r][i] = H[r][i] - sum;
		}

		for(i = r+1; i < N; i ++){
			double sum = 0.0;
			for(j = 0; j < r; j ++){
				sum += L[i][j]*U[j][r];
			}
			L[i][r] = (H[i][r] - sum)/H[r][r];
		}
	}

	double *y = (double*)malloc(N*sizeof(double));
	memset(y, 0, sizeof(double)*N);

	y[0] = b[0];
	for(i = 1; i < N; i ++){
		double sum = 0.0;
		for(j = 0; j < i; j ++){
			sum += L[i][j]*y[j];
		}
		y[i] = b[i] - sum;
	}
	x[N-1] = y[N-1]/U[N-1][N-1];
	for(i = N-2; i >= 0; i --){
		double sum = 0.0;
		for(j = i+1; j < N; j ++){
			sum += U[i][j]*x[j];
		}
		x[i] = (y[i] - sum)/U[i][i];
	}
	//print(L);
	//print(U);
}

void error(double ** H, double * b, double * x){
	double err_x = 0, err = 0;
	int i, j;
	printt(x);
	for(i = 0; i < N; i ++){
		if(abbs(1.0 - x[i]) > err_x){
			err_x = abbs(1.0 - x[i]);
		}
	}

	double *r = (double*)malloc(N*sizeof(double));
	memset(r, 0, sizeof(double)*N);
	for(i = 0; i < N; i ++){
		for(j = 0; j < N; j++){
			r[i] += H[i][j]*x[i];
		}
		r[i] -= b[i];
		if(abbs(r[i]) > err){
			err = abbs(r[i]);
		}
	}
	printf("The error is r = %.8f, delta_x = %.8f.\n", err, err_x);
}