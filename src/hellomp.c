// OpenMP program to print Hello World
// using C language
// To use type gcc hellomp.c -fopenmp then a.exe
// OpenMP header
#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char* argv[])
{
 
    // Beginning of parallel region
    #pragma omp parallel
    {
 
        printf("Hello World... from thread = %d\n",
               omp_get_thread_num());
    }
    // Ending of parallel region
}