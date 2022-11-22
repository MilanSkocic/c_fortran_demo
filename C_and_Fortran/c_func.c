/**
 * @file
 * @author Milan Skocic
 * @brief C functions that can be called from Fortran
 * 
 */
#include <stdio.h>

/**
 * @brief Print a rank-2 array
 * 
 * @param C rank-2 array
 * @param M integer number of rows
 * @param N integer number of cols
 */
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

/**
 * @brief Transform a Fortran array to a C array
 * 
 * @param farray rank-2 array stored as column major layout
 * @param row number of rows
 * @param col number of columns
 * @param carray rank-2 array stored as row major layout.
 */
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

/**
 * @brief Transform a C array into a Fortran array
 * 
 * @param carray rank-2 array stored as row major layout
 * @param row number of rows
 * @param col number of columns
 * @param farray rank-2 array stored as column major layout.
 */
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
/**
 * @brief Print a Fortran string
 * 
 * @param string null-terminated String
 */
void c_print_string(char *string){
    printf("%s\n", string);
}