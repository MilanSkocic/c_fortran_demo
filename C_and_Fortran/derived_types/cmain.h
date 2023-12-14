#ifndef CMAIN_H
#define CMAIN_H

/* SIMPLE DERIVED TYPE*/
/* C structure mirroring the derived type in Fortran */
struct fobj_simple_capi{
    int n;
    float array[3];
    char name[33];
};

extern struct fobj_simple_capi obj_simple_capi;




#endif
