#include <omp.h>
#include <stdio.h>
int main()
{
  omp_set_num_threads(4);
  int N = 1100;
  int sum = 0;
  //start parallel
  #pragma omp parallel
  {
    #pragma omp for reduction(+ : sum) schedule(static)
    //for secure sum while we add i
    for(int i = 0; i <= N; i++)
    {
  	   sum += i;
  	}
  }
  printf("sum = %d\n", sum);
}
