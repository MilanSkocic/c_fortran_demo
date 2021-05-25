#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"visitorobject.h"

AstVisitor *AstVisitor__init__(){

    AstVisitor *self = (AstVisitor *)calloc(1, sizeof(AstVisitor));
    self->value = NULL;
    self->get_infix = &AstVisitor_get_infix;
    self->__del__ = &AstVisitor__del__;

    return self;

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


void AstVisitor__del__(AstVisitor *self){
    
    free(self->value);
    free(self);

}
