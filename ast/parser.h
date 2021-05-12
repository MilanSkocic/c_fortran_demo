#ifndef PARSER_H 
#define PARSER_H
#include <math.h>
#include <complex.h>
#include "lexerobject.h"

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
    AST_ROOT
};

typedef struct ast_node_struct{

    enum ast_node_types type;
    
    struct ast_node_struct *top;

    struct ast_node_struct *right;
    
    struct ast_node_struct *left;

    void (*op)(struct ast_node_struct *left, struct ast_node_struct *right);

    double complex (*eval)(double *p, double w);

}AstNode;


typedef struct parser_struct{

   Lexer *lexer;
   Token **elements;
   Token **operators;
   int nelmts;
   int nops;
   Token *current_token;
   Token *previous_token;
   
   /* METHODS */
   void (*parse_elements)(struct parser_struct *self);
   void (*parse_operators)(struct parser_struct *self);
   void (*parse)(struct parser_struct *self, int verbose);
   void (*__del__)(struct parser_struct *self);

}Parser;

AstNode *AstNode__init__(int type, AstNode *top, AstNode *left, AstNode *right);

void AstNode__del__(AstNode *self);

Parser *Parser__init__(Lexer *lexer);

void Parser__del__(Parser *self);

void Parser_eat(Parser *self);

void Parser_parse(Parser *parser, int verbose);

void Parser_parse_operators(Parser *self);

void Parser_parse_elements(Parser *self);

double complex resistance(double *p, double w);

double complex capacitance(double *p, double w);

#endif
