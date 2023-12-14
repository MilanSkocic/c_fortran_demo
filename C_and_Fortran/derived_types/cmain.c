#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cmain.h"


int main(void){
    int i;

    /*SIMPLE FORTRAN DERIVED TYPE*/
    printf("%d\n", obj_simple_capi.n);
    for(i=0;i<3;i++){
        printf("%f\t", obj_simple_capi.array[i]);
    }
    printf("%s\n", obj_simple_capi.name);

    

    return EXIT_SUCCESS;
}
