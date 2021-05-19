#include "astobject.h"



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



