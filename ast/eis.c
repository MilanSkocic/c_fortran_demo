#include"eis.h"

double complex resistance(double *p, double w){
    return (double complex) (*p);
}

double complex capacitance(double *p, double w){
    return 1/(I*w*(*p));
}
