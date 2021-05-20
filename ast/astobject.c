#include "astobject.h"

AstVisitor *AstVisitor__init__(AstNode *root){

    AstVisitor *self = (AstVisitor *)calloc(1, sizeof(AstVisitor));

    self->value = (char *)calloc(0, sizeof(char));
    self->root = root;
    self->visit = &AstVisitor_visit;

    return self;

}

AstNode *AstNode__init__(Token *token, AstNode * left, AstNode *right)
{
    AstNode *self = (AstNode *)calloc(1, sizeof(AstNode));

    self->token = token;
    self->left = left;
    self->right = right;
    return self;
}

void AstNode__del__(AstNode* self){
    free(self);
}



void AstVisitor_visit(AstVisitor *self){

    printf("CURRENT NODE TOKEN = %s\n", self->root->token->value);
    char *result;
    if ((self->root->left == NULL) & (self->root->right == NULL)){
        result = self->root->token->eval(self->root->token->value);
        self->value = (char *)realloc(self->value, strlen(result) + strlen(self->value) + 1 * sizeof(char));
        strcat(self->value, result);
        printf("value = %s \n", self->value);

    }

    if(self->root->left != NULL){
        printf("LEFT NOT NULL %s\n", self->root->left->token->value);
        result = self->root->token->value;
        self->value = (char *)realloc(self->value, strlen(result) + strlen(self->value) + 1 * sizeof(char));
        strcat(self->value, result);
        printf("value = %s \n", self->value);
        self->root = self->root->left;
        self->visit(self);
    }

        
    if(self->root->right != NULL){
        printf("RIGHT NOT NULL %s\n", self->root->right->token->value);
        result = self->root->right->token->value;
        self->value = (char *)realloc(self->value, strlen(result) + strlen(self->value) + 1 * sizeof(char));
        strcat(self->value, result);
        printf("value = %s \n", self->value);
        self->root = self->root->right;
        self->visit(self);
    }



}
