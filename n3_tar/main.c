#include <stdio.h>
#include <omp.h>

#define QUANTITY 100


double sum(double a, double b, double c){ //For elements with 1..QUANTITY-2 
	return (a * b * c) / 3;		  //indecies
}

double SumForBorders(double a, double b){ //For the first and the last
	return (a * b) / 2;		  //elements
}



int main(){

	double a[QUANTITY];
	double b[QUANTITY] = { 0 };
	for (int i = 0; i < QUANTITY; i++){ //Initializing
		a[i] = i;
	}	


//-----To avoid data dependence it's necessary not read and write on different
//iterations, so the nested loop has a step equal to 3. In order to cover all
//the elements an external loop exists.
#pragma omp for
	for (long int i = 0; i < 3; i++){   
		for (long int j = i; j < QUANTITY; j += 3){ 
			if (j == 0){
				b[j] = SumForBorders(a[j],  a[j + 1]);
			}
			else if (j == QUANTITY - 1){
				b[j] = SumForBorders(a[j], a[j - 1]);
			}
			else {
				b[j] = sum(a[j - 1], a[j], a[j + 1]);
			}
		}
	}

//A part with printing, was used for testing
/*
	for (long int i = 0; i < QUANTITY; i++){
		printf("b[%ld]) %.2f\n", i, b[i]);
	}
*/

	return 0;
}
