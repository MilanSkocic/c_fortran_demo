#include "astobject.h"
#include "visitorobject.h"


AstNode *AstNode__init__(Token *token, AstNode * left, AstNode *right)
{
    AstNode *self = (AstNode *)calloc(1, sizeof(AstNode));

    self->token = token;
    self->left = left;
    self->right = right;
    self->eval = &AstNode_eval;
    return self;
}

void AstNode__del__(AstNode* self){
    free(self);
}

void AstNode_eval(AstNode *self, AstVisitor *visitor){
    if((self->left == NULL) & (self->right == NULL)){
        visitor->visit(visitor, self->token);
    }
    if(self->left != NULL){
        self->eval(self->left, visitor);
        
    }
    if(self->right != NULL){
        self->eval(self->right, visitor);
    }
}
