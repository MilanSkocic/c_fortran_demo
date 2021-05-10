#ifndef PARSER_H 
#define PARSER_H
#include "tokenizer.h"

enum ast_node_types
{
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

typedef struct ast_node_struct
{

    enum ast_node_types type;

    struct ast_node_struct *right;
    
    struct ast_node_struct *left;

    void (*op)(struct ast_node_struct *left, struct ast_node_right *right);

    void (*eval)(struct ast_node_struct *self);

}AstNode;


typedef struct parser_struct{

   Lexer *lexer;
   Token *current_token;
   Token *previous_token;

}Parser;

AstNode *AstNode__init__(int type);

void AstNode__del__(AstNode *self);

Parser *Parser__init__(Lexer *lexer);

void Parser_eat(Parser *self, int token_type);

AstNode *Parser_parse(Parser *parser);

AstNode *Parser_parse_statement(Parser *parser);

AstNode *Parser_parse_statements(Parser *parser);



#endif
