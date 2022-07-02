#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


//Function, which fill recieved matrix with random numbers. 
//The first two parameters determine the size of the matrix
void initialization(const int n, const int m, unsigned long long* A){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			A[i * m + j] = rand() % 1000; //The restriction is made
		}				      //to try to avoid
	}					      //too huge numbers
}						 


//Function, which fill recieved matrix with zeroes
void zeros(const int n, const int m, unsigned long long* A){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			A[i * m + j] = 0;   
		}				  
	}					 
}						


//This function read the size of matrices
void readSize(int* n, int* m, int* p){
	char new_n, new_m, new_p;  //To avoid error if you enter smth what is
       				   //not a number	
	printf("We work with expression A * B = C.\n\
A = A[n][m], B = B[m][p] => C = C[n][p].\n\
Enter the size of matrices:\nn = ");
	scanf("%d", n); 

	printf("m = ");
	scanf("%d", m);

	printf("p = ");
	scanf("%d", p);

	//Check every parameter - it must be a positive number
	if(*n <= 0 || *m <= 0 || *p <= 0){
		printf("\nSorry, check your parameters\n");
		exit(1);
	}
}





int main(){
	srand(time(NULL)); //This is to generate new random numbers every start
			   //of the program
	
	int n = 0;  //Parameters, which determine the size
        int m = 0;  //of matrices, with default value equal to 0
        int p = 0;  
	readSize(&n, &m, &p);  //Read parameters

	//Matrices A, B, C. It's essential to allocate memory in the heap,
	//not in the stack, as we want to work with large matrices
	unsigned long long* A =
		(unsigned long long*)malloc(n * m * sizeof(unsigned long long));
	unsigned long long* B =
		(unsigned long long*)malloc(m * p * sizeof(unsigned long long));
	unsigned long long* C =
		(unsigned long long*)malloc(n * p * sizeof(unsigned long long));
	initialization(n, m, A);  //Fill A and B with random numbers
	initialization(m, p, B);
	zeros(n, p, C);		  //Fill C with zeroes


	time_t t_start = time(NULL);
//-----To avoid data dependence it's necessary to make loop on 'k' internal
//Besides, in order to make dynamic balancing an option 'schedule' with
//parameter 'guided' is used. 'Guided' allows to change the number iterations
//received by every thread every time. The second parameter is a start quantity
#pragma omp parallel
{
#pragma omp for schedule(guided, 100)
	for(int i = 0; i < n; i++){
		for(int j = 0; j < p; j++){
			for(int k = 0; k < m; k++){
				C[i * p + j] = A[i * m + k] + B[k * p + j];
			}
		}
	}
}

	time_t t_end = time(NULL);
	double time = difftime(t_end, t_start);
	printf("Time of multiplication: ~%lf sec\n", time);

//You can uncomment this, if you want to print the result matrix
/*
	for(int i = 0; i < n; i++){
		for(int j = 0; j < p; j++){
			printf("%llu ", C[i * p + j]);
		}
		printf("\n");
	}
*/

	return 0;
}
