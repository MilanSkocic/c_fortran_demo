#ifndef PARSER_H 
#define PARSER_H
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
   void (*push_element)(struct parser_struct *self);
   void (*push_operator)(struct parser_struct *self);
   void (*parse)(struct parser_struct *self);
   void (*pop_operator)(struct parser_struct *self);
   void (*discard_lparen)(struct parser_struct *self);
   void (*push_node)(struct parser_struct *self, AstNode *left, AstNode *right);
   void (*pop_node)(struct parser_struct *self);
   void (*__del__)(struct parser_struct *self);

}Parser;

/* METHODS */
Parser *Parser__init__(Lexer *lexer);
void Parser__del__(Parser *self);

void Parser_eat(Parser *self);
void Parser_parse(Parser *parser);
void Parser_push_operator(Parser *self);
void Parser_push_element(Parser *self);
void Parser_pop_operator(Parser *self);
void Parser_pop_node(Parser *self);
void Parser_discard_lparen(Parser *self);
void Parser_push_node(Parser *self, AstNode *left, AstNode *right);

#endif
