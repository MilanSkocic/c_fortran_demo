#include <stdio.h>


void c_func(double *C, int *M, int *N){
    // print C
    printf("\n");
    size_t i, j;
    int n = *N;
    int m = *M;
    for (i=0;i<m; i++)
    {
        for (j=0;j<n; j++)
        {
            printf("%10.5f\t", *(C+j+n*i));
        }
        printf("\n");
    }
}

// transform Column Major to row_major
void colmajor_to_rowmajor(double *farray, int *row, int *col, double *carray){
    size_t i, j;
    int m = *row;
    int n = *col;
    for (i=0;i<m; i++)
    {
        for (j=0;j<n; j++)
        {
            *(carray+j+n*i) =  *(farray+i+m*j);
        }
    }
}

// transform Row Major to Column major
void rowmajor_to_colmajor(double *carray, int *row, int *col, double *farray){
    size_t i, j;
    int m = *row;
    int n = *col;
    for (i=0;i<m; i++)
    {
        for (j=0;j<n; j++)
        {
            *(farray+i+m*j) =  *(carray+j+n*i);
        }
    }
}

void c_print_string(char *string){
    printf("%s\n", string);
}