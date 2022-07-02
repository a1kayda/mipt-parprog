#include <stdio.h>
#include <omp.h>
#include <malloc.h>
#include <math.h>


//This structure stores prime number and a pointer to the next prime number(the 
//same structure)
struct prime{
	struct prime* next;
	int value;	
};





int main(){
	
	int N = 0;  //Obvious, what it is
	printf("Enter N(>2 please, it was too lazy to write\
 an extra condition): ");
	scanf("%d", &N);  //Read N

	//Create first to elements of the list(1, 2)
	struct prime table = {NULL, 1};
	table.next = malloc(sizeof(struct prime));
	table.next->next = NULL;
	table.next->value = 2;

//Use 'omp parallel for' to divide iterations between several threads
//'Ordered' is used to follow the order of numbers. It's essential, because
//we mustn't miss any prime number before check any greater number
#pragma omp parallel for ordered
	for(int i = 3; i <= N; i++){
		//Create a pointer for iterating through the list
		struct prime* prime_number = table.next; 
							 
		#pragma omp ordered //Create an order of processing	 
		{	
			//If the current number divide by
			//any prime without a remainder, it means the number is
			//not a prime. However, if the number divide by any
			//prime with a remainder - the number is a prime
			while(i % prime_number->value != 0){
				//If there is the end of the list, it means
				//the numberis a prime, so we add it tothe list
				if(prime_number->next == NULL){
					prime_number->next =
						malloc(sizeof(struct prime));
					prime_number = prime_number->next;
					prime_number->next = NULL;
					prime_number->value = i;
					break;
				}
				prime_number = prime_number->next;
			}
		}
	}

	//Display the list of the primes
	struct prime* tmp = &table;
	do{
		printf("%d  ", tmp->value);
		tmp = tmp->next;
	}while(tmp->next != NULL);
	printf("%d\n", tmp->value);


	return 0;
}
