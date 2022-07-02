clang -Xpreprocessor -fopenmp -lomp hello.c -o hello
#gcc -fopenmp hello.c -o hello
OMP_NUM_THREADS=1000 ./hello
