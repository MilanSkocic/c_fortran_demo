#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"visitorobject.h"

AstVisitor *AstVisitor__init__(){

    AstVisitor *self = (AstVisitor *)calloc(1, sizeof(AstVisitor));
    self->value = calloc(1, sizeof(char));
    self->value[0] = '\0';
    self->visit = &AstVisitor_visit;

    return self;

}


char *AstVisitor_visit(AstVisitor *self, AstNode *node){

    char *left;
    char *right;
    char *value = NULL;
    size_t size;


    switch(node->token->type){
        case TOKEN_ADD:
        case TOKEN_SUB:
        case TOKEN_POW:
        case TOKEN_DIV:
        case TOKEN_MUL:
            left = self->visit(self, node->left);
            right = self->visit(self, node->right);
            size = strlen(self->value) + strlen(left) + strlen(right) + strlen(node->token->value) + 3;
            self->value = (char *)realloc(self->value, size*sizeof(char));
            strcat(self->value, "(");
            strcat(self->value, left);
            strcat(self->value, node->token->value);
            strcat(self->value, right);
            strcat(self->value, ")");
            value = self->value;
            break;
        case TOKEN_ELEMENT:
            value = node->token->value;
            break;
        default:
            value = self->value;
            break;
    }
    return value;
}
