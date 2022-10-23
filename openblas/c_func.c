#include <stdio.h>


void c_func_(double *C, int *M, int *N){
    // print C
    printf("In C func\n");
    printf("\n");
    size_t i, j;
    int n = *N;
    int m = *M;
    for (i=0;i<m; i++)
    {
        for (j=0;j<n; j++)
        {
            printf("%10.5f\t", *(C+i*n+j));
        }
        printf("\n");
    }
    printf("End C func\n");
}