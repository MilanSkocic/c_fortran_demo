#ifndef PARSER_H 
#define PARSER_H
#include <math.h>
#include <complex.h>
#include "tokenizer.h"

enum ast_node_types{
    AST_R,
    AST_C,
    AST_L,
    AST_Q,
    AST_W,
    AST_WD,
    AST_WM,
    AST_ADD,
    AST_DIV,
};

typedef struct ast_node_struct{

    enum ast_node_types type;

    struct ast_node_struct *right;
    
    struct ast_node_struct *left;

    void (*op)(struct ast_node_struct *left, struct ast_node_struct *right);

    double complex (*eval)(double *p, double w);

}AstNode;


typedef struct parser_struct{

   Lexer *lexer;
   Token *current_token;
   Token *previous_token;

}Parser;

AstNode *AstNode__init__(int type, AstNode *left, AstNode *right);

void AstNode__del__(AstNode *self);

Parser *Parser__init__(Lexer *lexer);

void Parser_eat(Parser *self);

AstNode *Parser_parse(Parser *parser);


double complex resistance(double *p, double w);

double complex capacitance(double *p, double w);

#endif
