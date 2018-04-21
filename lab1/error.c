#include "stdio.h"
#include "math.h"

#define IMAX 1000000

int main(){
	float n = 1.0, x = 0.0, real = 0.693147190546, err = 0.0;
	int i = 1;
	for(i = 1; i < IMAX; i++){
		if(i % 2) x += 1.0 / n;
		else x -= 1.0 / n;
		n += 1.0;
		err = real - x;
		if( err <= 0.00005 && err >= -0.00005 ) break;
	}
	printf("[%d] X:%f Err:%f\n", i, x, err);
	return 0;
}
