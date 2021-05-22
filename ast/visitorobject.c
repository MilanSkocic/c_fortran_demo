#include<stdlib.h>
#include"visitorobject.h"

AstVisitor *AstVisitor__init__(){

    AstVisitor *self = (AstVisitor *)calloc(1, sizeof(AstVisitor));

    self->value = "";
    self->visit = &AstVisitor_visit;

    return self;

}


char *AstVisitor_visit(AstVisitor *self, AstNode *node){

    char *left;
    char *right;
    char *value;
    size_t size;

    
    switch(node->token->type){
        case TOKEN_ADD:
        case TOKEN_SUB:
        case TOKEN_MUL:
            left = self->visit(self, node->left);
            right = self->visit(self, node->right);
            size = strlen(left)+strlen(right)+2;
            self->value = (char *)realloc(self->value, size*sizeof(char));
            strcat(self->value, left);
            strcat(self->value, "+");
            strcat(self->value, right);
            value = self->value;
            break;
        case TOKEN_POW:
        case TOKEN_DIV:
            left = self->visit(self, node->left);
            right = self->visit(self, node->right);
            size = strlen(left)+strlen(right)+2;
            self->value = (char *)realloc(self->value, size*sizeof(char));
            strcat(self->value, left);
            strcat(self->value, "/");
            strcat(self->value, right);
            value = self->value;
            break;
        case TOKEN_ELEMENT:
            value = node->token->value;
            size = strlen(value) + strlen(self->value) + 1;
            self->value = (char *)realloc(self->value, size*sizeof(char));
            strcat(self->value, value);
            break;
        default:
            value = NULL;
            break;
    }
    return value;
}
