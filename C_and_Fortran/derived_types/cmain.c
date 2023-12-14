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

    void *obj = fobj_cmpl_capi_init(3, 4.5);
    fobj_cmpl_capi_print(obj);
    fobj_cmpl_capi_del(obj);

    return EXIT_SUCCESS;
}
