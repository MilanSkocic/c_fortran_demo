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
            printf("%10.5f\t", *(C+i+n*j));
        }
        printf("\n");
    }
    printf("End C func\n");
}

// transform Column Major to row_major
void colmajor_to_rowmajor_(double *farray, int *row, int *col, double *carray){
    size_t i, j;
    int m = *row;
    int n = *col;
    for (i=0;i<m; i++)
    {
        for (j=0;j<n; j++)
        {
            *(carray+i+n*j) =  *(farray+i+m*j);
        }
    }
}

// transform Row Major to Column major
void rowmajor_to_colmajor_(double *carray, int *row, int *col, double *farray){
    size_t i, j;
    int m = *row;
    int n = *col;
    for (i=0;i<m; i++)
    {
        for (j=0;j<n; j++)
        {
            *(farray+i+m*j) =  *(carray+i+n*j);
        }
    }
}
