#include "astobject.h"



AstNode *AstNode__init__(Token *token, AstNode *top, AstNode * left, AstNode *right)
{
    AstNode *self = (AstNode *)calloc(1, sizeof(AstNode));

    self->token = token;

    switch(self->token->type)
    {
    	case TOKEN_ELEMENT:
		self->left = NULL;
		self->right = NULL;
		self->leaf = 1;

	case TOKEN_ADD:
	case TOKEN_MUL:
	case TOKEN_DIV:
	case TOKEN_SUB:
		self->left = left;
		self->right = right;
		self->leaf = 0;

	default:
		self->left = NULL; 
		self->right = NULL;
		self->leaf = 0;
    }

    return self;
}

void AstNode__del__(AstNode* self){
    free(self);
}



