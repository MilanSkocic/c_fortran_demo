/**
 * @file main.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_multifit_nlinear.h>
#define P(i) (gsl_vector_get(p,(i)))
#define COV(i,j) (gsl_matrix_get(cov,(i),(j)))

/**
 * @brief Data structure
 */
struct data {
    int n; /**< Number of points */
    double *x; /**< x values memory block */
    double *y; /**< y values memory block */
    double (*model)(double *p, double x); /**< model to use for computing y values */
};

/**
 * @brief Model to be used.
 * @param p memory block for parameters
 * @param x x value
 * @return y value
 */
double model(double *p, double x){
    return p[0] + p[1]*x + p[2]*pow(x, 2);
}

/**
 * @brief 
 */
int gsl_model(const gsl_vector *p, void *data){
    
    size_t N, i;
    double *x, *y;
    
    N = ((struct data *) data)->n;
    x = ((struct data *) data)->x;
    y = ((struct data *) data)->y;
    
    double (*model)(double *p, double x) = ((struct data *) data)->model;

    for(i=0;i<N; i++){
        y[i] = model(p->data, x[i]);
    }
    return GSL_SUCCESS;
}

/**
 * @brief Function to be fitted by the Non Linear Least Square Algorithm
 * @param p pointer to a gsl vector
 * @param data pointer to a data structure
 * @param f pointer to a gsl vector for the output
 */
int gsl_residuals(const gsl_vector *p, void *data, gsl_vector *f){

    size_t N, i;
    double *x, *y;
    double xi, yi;
    
    N = ((struct data *) data)->n;
    x = ((struct data *) data)->x;
    y = ((struct data *) data)->y;


    for(i=0;i<N; i++){
        xi = *(x+i);
        yi = *(y+i);
        gsl_vector_set(f, i, model(p->data, xi)-yi);

    }

    return GSL_SUCCESS;

}

gsl_matrix *get_vandermonde(gsl_vector *x, gsl_vector *p){

    size_t i, j, n, k;

    n = x->size;
    k = p->size;
    gsl_matrix *X =  gsl_matrix_alloc(n,k);

    for(i=0;i<n;i++){
        for(j=0;j<k;j++){
            gsl_matrix_set(X, i, j, 1.0*pow(gsl_vector_get(x, i), j));
        }
    }
    
    return X;
}


gsl_vector *gsl_vector_linspace(double start, double end, const size_t n){

    double d, amp;
    size_t i;
    gsl_vector *x = gsl_vector_alloc(n);

    d = (end - start) / (n-1);
    
    for(i=0;i<n;i++){
        gsl_vector_set(x, i,  start + i*d);
    }

    return x;
}


void gsl_print_vector(gsl_vector *x){

    size_t i;

    for(i=0; i<x->size; i++){
        printf("x[%d]=%f\n", i, gsl_vector_get(x, i));
    }

}


int example_multifit_linear(const int n, const int k){

    double xi, yi, ei, chisq;
    int i;
    struct data data;

    gsl_matrix *X = gsl_matrix_alloc(n, k);
    gsl_matrix *cov = gsl_matrix_alloc(k,k);
    gsl_vector *x = gsl_vector_linspace(0, 5, n);
    gsl_vector *y = gsl_vector_alloc(n);
    gsl_vector *w = gsl_vector_alloc(n);
    gsl_vector *p = gsl_vector_alloc(k);

    gsl_vector_set(p, 0, 1);
    gsl_vector_set(p, 1, 2.3456);
    gsl_vector_set(p, 2, 3.45);

    gsl_vector_set_all(w, 1.0);

    X = get_vandermonde(x, p);

    data.n = n;
    data.x = x->data;
    data.y = y->data;
    data.model = &model;

    gsl_model(p, (void *) &data);
    
    
    gsl_multifit_linear_workspace * work = gsl_multifit_linear_alloc (n, k);
    gsl_multifit_wlinear (X, w, y, p, cov, &chisq, work);
    gsl_multifit_linear_free(work);
  
    printf ("# best fit: Y = %.3f + %.3f X + %.3f X^2\n", P(0), P(1), P(2));

    printf ("# covariance matrix:\n");
    printf ("[ %+.5e, %+.5e, %+.5e  \n", COV(0,0), COV(0,1), COV(0,2));
    printf ("  %+.5e, %+.5e, %+.5e  \n", COV(1,0), COV(1,1), COV(1,2));
    printf ("  %+.5e, %+.5e, %+.5e ]\n", COV(2,0), COV(2,1), COV(2,2));
    printf ("# chisq = %g\n", chisq);

    gsl_matrix_free(X);
    gsl_vector_free(x);
    gsl_vector_free(y);
    gsl_vector_free(w);
    gsl_vector_free(p);
    gsl_matrix_free(cov);

    return GSL_SUCCESS;
}

int example_multifit_nonlinear(const int n, const int k){

    double xi, yi, ei, chisq;
    int i;
    struct data data;
    double chisq0;
    int status, info;
    const double xtol = 1e-8;
    const double gtol = 1e-8;
    const double ftol = 0.0;

    gsl_vector *x, *p, *y, *f, *w;
    gsl_matrix *J, *covar;
    
    x = gsl_vector_linspace(0, 5, n);
    w = gsl_vector_alloc(n);
    p = gsl_vector_alloc(k);
    y = gsl_vector_alloc(n);
    covar = gsl_matrix_alloc (k, k);

    // set x
    for(i=0; i<n; i++){
        gsl_vector_set(x, i, i);
    }
    // set p
    gsl_vector_set(p, 0, 1);
    gsl_vector_set(p, 1, 2.3456);
    gsl_vector_set(p, 2, 3.45);

    //set w
    gsl_vector_set_all(w, 1.0);
    

    data.n = n;
    data.x = x->data;
    data.y = y->data;
    data.model = &model;

    // compute data to fit
    gsl_model(p, (void *) &data);
    

    //set fit workspace
    const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
    gsl_multifit_nlinear_workspace *work_nlin;
    gsl_multifit_nlinear_fdf fdf;
    gsl_multifit_nlinear_parameters fdf_params = gsl_multifit_nlinear_default_parameters();
    fdf_params.trs = gsl_multifit_nlinear_trs_lm;

    // set p with new parameter as initial guess
    gsl_vector_set_all(p, 1.2);
    
    //random env 
    gsl_rng * r;
    gsl_rng_env_setup();
    r = gsl_rng_alloc(gsl_rng_default);

    /* define the function to be minimized */
    fdf.f = gsl_residuals;
    fdf.df = NULL;   /* set to NULL for finite-difference Jacobian */
    fdf.fvv = NULL;     /* not using geodesic acceleration */
    fdf.n = n; /**< number of points */
    fdf.p = k; /**< number of parameters */
    fdf.params = &data;

    /* allocate workspace with default parameters */
    work_nlin = gsl_multifit_nlinear_alloc (T, &fdf_params, n, k);

    /* initialize solver with starting point and weights */
    gsl_multifit_nlinear_winit(p, w, &fdf, work_nlin);

    /* compute initial cost function */
    f = gsl_multifit_nlinear_residual(work_nlin);
    gsl_blas_ddot(f, f, &chisq0);

    /* solve the system with a maximum of 100 iterations */
    status = gsl_multifit_nlinear_driver(100, xtol, gtol, ftol, NULL, NULL, &info, work_nlin);

    /* compute covariance of best fit parameters */
    J = gsl_multifit_nlinear_jac(work_nlin);
    gsl_multifit_nlinear_covar (J, 0.0, covar);

    /* compute final cost */
    f = gsl_multifit_nlinear_residual(work_nlin);
    gsl_blas_ddot(f, f, &chisq);

    fprintf(stderr, "summary from method '%s/%s'\n", gsl_multifit_nlinear_name(work_nlin), gsl_multifit_nlinear_trs_name(work_nlin));
    fprintf(stderr, "number of iterations: %zu\n", gsl_multifit_nlinear_niter(work_nlin));
    fprintf(stderr, "function evaluations: %zu\n", fdf.nevalf);
    fprintf(stderr, "Jacobian evaluations: %zu\n", fdf.nevaldf);
    fprintf(stderr, "reason for stopping: %s\n", (info == 1) ? "small step size" : "small gradient");
    fprintf(stderr, "initial X2 = %f\n", sqrt(chisq0));
    fprintf(stderr, "final   X2 = %f\n", sqrt(chisq));
    fprintf(stderr, "final   X2/v = %f\n", sqrt(chisq/(n-k)));


    printf ("# best fit: Y = %.3f + %.3f X + %.3f X^2\n", gsl_vector_get(work_nlin->x, 0), gsl_vector_get(work_nlin->x, 1), gsl_vector_get(work_nlin->x, 2));
    gsl_multifit_nlinear_free (work_nlin);
    gsl_matrix_free (covar);
    gsl_rng_free (r);
    gsl_vector_free(p);
    gsl_vector_free(w);
    gsl_vector_free(x);
    gsl_vector_free(y);

    return GSL_SUCCESS;
}


int main(int argc, char **argv){

    example_multifit_linear(10, 3);
    example_multifit_nonlinear(10, 3);
    
    return EXIT_SUCCESS;
}
