#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"visitorobject.h"

AstVisitor *AstVisitor__init__(){

    AstVisitor *self = (AstVisitor *)calloc(1, sizeof(AstVisitor));
    self->value = NULL;
    self->get_infix = &AstVisitor_get_infix;
    self->eval = &AstVisitor_eval;
    self->__del__ = &AstVisitor__del__;

    return self;

}

void AstVisitor__del__(AstVisitor *self){
    
    free(self->value);
    free(self);

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
                case 'C':
                case 'L':
                case 'Q':
                    value = 2+I*2;
                case 'W':
                    switch(node->token->value[2]){
                        case 'd':
                        case 'D':
                            value = 0;
                            break;
                        case 'm':
                        case 'M':
                            value = 0.0;
                            break;
                        default:
                            value = 0.0;
                    }
            
            }
        
        default:
            value = 0.0 +I*0.0;
            break;
    }

    return value;
}

