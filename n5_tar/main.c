#include <stdio.h>


//Function, which calculates a factorial of the number n
int factorial(const int n){
	if(n == 0){
		return 1;
	}
	return (n > 2 ? n * factorial(n - 1) : n);
}


//Function, which calculates a multiplier for each member of the series
long double multiplier(const float alpha, const int k){
	long double numenator = 1;
	for(int i = 0; i < k - 1; i++){
		numenator *= (alpha - i);
	}
	return numenator/factorial(k);
}


//Function, which read the given parameter values
void readParameters(long double* x, float* alpha, int* n){
	printf("An expansion of (1 + x)^alpha in vicinity of 0.\n\
Enter the value of x: ");
	scanf("%Lf", x);
	
	printf("Enter the exponent alpha: ");
	scanf("%f", alpha);

	printf("Enter the polynomial degree n: ");
	scanf("%d", n);
}


//Function, which calculates the value for the number x and integer exponenta
long double power(const long double x, const int n){
	if (n == 0) {
		return 1;
	}
	else if (n > 0){
		return (n > 0 ? x * power(x, n - 1) : x);
	}
	else {
		return 1.0 / power(x, -n);
	}
}





int main(){
	long double x = 0;      //A variable
	float alpha = 0;  //and an exponent in (1 + x)^alpha
	int n = 0;        //A polynomial degree 
	long double sum = 0;    //The sum of the series
	readParameters(&x, &alpha, &n);

//Use reduction(...) in order to avoid race condition. Due to the loop
//each exponent is counted. Function schedule is used to balance workload
//among all the threads dynamically
#pragma omp parallel
{
#pragma omp for reduction(+ : sum) schedule(guided)
	for(int i = 0; i <= n; i++){
		sum += 	multiplier(alpha, i) * power(x, i);
	}
}

	printf("The sum of the series: %.8Lf\n", sum);


	return 0;
}
