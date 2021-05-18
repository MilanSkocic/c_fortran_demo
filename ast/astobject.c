#ifndef ASTOBJECT_H
#define ASTOBJECT_H

#include "astobject.h"



AstNode *AstNode__init__(int type, AstNode *top, AstNode * left, AstNode *right)
{
    AstNode *self = (AstNode *)calloc(1, sizeof(AstNode));

    if (left == NULL & right == NULL){
        self->leaf = 1;
    }
    self->type = type;
    self->right = NULL;
    self->left = NULL;
    self->leaf = 0;

    switch(self->type)
    {
        case AST_R:
        case AST_C:
        case AST_L:
        case AST_Q:
        case AST_W:
        case AST_Wd:
        case AST_Wm:
        case AST_OP:
            self->left = left;
            self->right = right;
            break;
    }

    return self;
}

void AstNode__del__(AstNode* self){
    free(self);
}

#endif
