#ifndef ASTOBJECT_H
#define ASTOBJECT_H
#include "tokenobject.h"
#include "visitorobject.h"

/* enum ast_types{AST_R, AST_C, AST_L, AST_Q, AST_W, AST_Wd, AST_Wm, AST_OP}; */

typedef struct ast_node_struct{
    /* enum ast_types type; */
    struct token_struct *token;
    struct ast_node_struct *right;
    struct ast_node_struct *left;
    void (*eval)(struct ast_node_struct *self, AstVisitor *visitor);
}AstNode;


/* METHODS */
AstNode *AstNode__init__(Token *token, AstNode *left, AstNode *right);
void AstNode__del__(AstNode *self);


void AstNode_eval(AstNode *self, AstVisitor *visitor);

#endif
