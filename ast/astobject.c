#include "astobject.h"



AstNode *AstNode__init__(Token *token, AstNode *top, AstNode * left, AstNode *right)
{
    AstNode *self = (AstNode *)calloc(1, sizeof(AstNode));

    self->token = token;
    self->left = left;
    self->right = right;

    switch(self->token->type)
    {
    	case TOKEN_ELEMENT:
            self->leaf = 1;

        default:
            self->leaf = 0;
    }

    return self;
}

void AstNode__del__(AstNode* self){
    free(self);
}



