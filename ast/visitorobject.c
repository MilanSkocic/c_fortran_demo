#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"visitorobject.h"

AstVisitor *AstVisitor__init__(){

    AstVisitor *self = (AstVisitor *)calloc(1, sizeof(AstVisitor));
    self->value = NULL;
    self->p = NULL;
    self->n = 0;
    self->init_parameters = &AstVisitor_init_parameters;
    self->get_infix = &AstVisitor_get_infix;
    self->eval = &AstVisitor_eval;
    self->__del__ = &AstVisitor__del__;

    return self;

}

void AstVisitor__del__(AstVisitor *self){
    
    free(self->value);
    free(self->p);
    free(self);

}

void AstVisitor_init_parameters(AstVisitor *self, AstNode *node){
>>>>>>> 5da561d3b16b8f53c342c23876f7feeaed65508f

    switch(node->token->type){
        case TOKEN_ADD:
        case TOKEN_SUB:
        case TOKEN_MUL:
        case TOKEN_POW:
        case TOKEN_DIV:
            self->init_parameters(self, node->left);
            self->init_parameters(self, node->right);
            break;
        case TOKEN_ELEMENT:  
            switch(node->token->value[0]){ 
                case 'R': 
                case 'L': case 'C':
                    self->n += 1;
                    break;
                case 'Q':
                    self->n += 2;
                    break;
                case 'W':
                    switch(node->token->value[1]){
                        case 'd':
                        case 'D':
                        case 'm':
                        case 'M':
                            self->n += 3;
                            break;
                        default:
                            self->n += 1;
                            break;
                    }
            }
            self->p = (double *)realloc(self->p, self->n * sizeof(double));
            break;
        default:
            break;
    }
}

char *AstVisitor_get_infix(AstVisitor *self, AstNode *node){

    char *left;
    char *right;
    char *value = (char *)calloc(1, sizeof(char));
    value[0]  = '\0';
    size_t size;


    switch(node->token->type){
        case TOKEN_ADD:
        case TOKEN_SUB:
        case TOKEN_POW:
        case TOKEN_DIV:
        case TOKEN_MUL:
            left = self->get_infix(self, node->left);
            right = self->get_infix(self, node->right);
            size = strlen(left) + strlen(right) + strlen(node->token->value) + 3;
            value = (char *)realloc(value, size*sizeof(char));
            strcat(value, "(");
            strcat(value, left);
            strcat(value, node->token->value);
            strcat(value, right);
            strcat(value, ")");
            free(left);
            free(right);
            self->value = value;
            break;
        case TOKEN_ELEMENT:
            size = strlen(node->token->value) + 1;
            value = (char *)realloc(value, size*sizeof(char));
            strcpy(value, node->token->value);
            self->value = value;
            break;
        default:
            break;
    }
    return value;
}

double complex AstVisitor_eval(AstVisitor *self, AstNode *node, double *p, double *w){
    
    double complex left, right;
    double complex value;
    
    
    switch(node->token->type){
        case TOKEN_SUB:
        case TOKEN_ADD:
            left = self->eval(self, node->left, p, w);
            right = self->eval(self, node->right, p, w);
            value = left + right;
            break;
        case TOKEN_MUL:
        case TOKEN_POW:
        case TOKEN_DIV:
            left = self->eval(self, node->left, p, w);
            right = self->eval(self, node->right, p, w);
            value = left * right / (left + right);
            break;
        case TOKEN_ELEMENT:
            switch(node->token->value[0]){
                case 'R':
                    value = resistance(self->p, *w);
                    break;
                case 'C':
                case 'L':
                case 'Q':
                    value = 2.2;
                    break;
                case 'W':
                    switch(node->token->value[1]){
                        case 'd':
                        case 'D':
                            value = warburg(self->p+3, *w);
                            break;
                        case 'm':
                        case 'M':
                            value = 1.0;
                            break;
                        default:
                            value = 0.0;
                            break;
                    }
                }
                break;
        default:
            value = 0.0;
            break;
        
    }

    return value;
}

