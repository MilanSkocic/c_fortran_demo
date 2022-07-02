#include "object.h"


struct object_t{
    size_t n;
    double *data;

    void (*init)(Object *, size_t);
    void (*destroy)(Object *);
    void (*print)(Object *);
};

void Object_init(Object *self, size_t n){
    self->n = n;
    self->data = (double *)calloc(self->n, sizeof(double));
}

void Object_destroy(Object *self){
    free(self->data);
    free(self);
}

void Object_print(Object *self){

    size_t i;
    for(i=0; i<self->n; i++){
        printf("data[%ld]=%f\n", i, self->data[i]);
    }
}

Object *Object_create(size_t n){
    Object *self;
    self = (Object *)calloc(1, sizeof(Object));
    self->init = &Object_init;
    self->destroy = &Object_destroy;
    self->print = &Object_print;

    self->init(self, n);
    return self;
}


int main(int argc, char **argv){

    Object *obj = Object_create(10);
    obj->print(obj);
    obj->destroy(obj);

    return EXIT_SUCCESS;
}