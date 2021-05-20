#ifndef AST_H
#define AST_H
#include "tokenobject.h"

/* enum ast_types{AST_R, AST_C, AST_L, AST_Q, AST_W, AST_Wd, AST_Wm, AST_OP}; */

typedef struct ast_node_struct{
    /* enum ast_types type; */
    struct token_struct *token;
    struct ast_node_struct *right;
    struct ast_node_struct *left;
}AstNode;


/* METHODS */
AstNode *AstNode__init__(Token *token, AstNode *left, AstNode *right);
void AstNode__del__(AstNode *self);


typedef struct ast_visitor_struct{

    char *value;
    AstNode *root;
    void (*visit)(struct ast_visitor_struct *self);


}AstVisitor;

AstVisitor *AstVisitor__init__(AstNode *root);
void AstVisitor_visit(AstVisitor *self);

#endif
