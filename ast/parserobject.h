#ifndef PARSER_H 
#define PARSER_H
#include <math.h>
#include <complex.h>
#include "lexerobject.h"
#include "astobject.h"




typedef struct parser_struct{

   Lexer *lexer;
   Token **queue;
   Token **operators;
   AstNode **nodes;
   AstNode *ast;
   int nqueue;
   int nops;
   int nnodes;
   Token *current_token;
   Token *previous_token;
   
   /* METHODS */
   void (*parse_elements)(struct parser_struct *self);
   void (*parse_operators)(struct parser_struct *self);
   void (*parse)(struct parser_struct *self);
   void (*parse_pop_operator)(struct parser_struct *self);
   void (*__del__)(struct parser_struct *self);

}Parser;


Parser *Parser__init__(Lexer *lexer);

void Parser__del__(Parser *self);

void Parser_eat(Parser *self);

void Parser_parse(Parser *parser);

void Parser_parse_operators(Parser *self);

void Parser_parse_elements(Parser *self);

void Parser_pop_operator(Parser *self);

double complex resistance(double *p, double w);

double complex capacitance(double *p, double w);


#endif
