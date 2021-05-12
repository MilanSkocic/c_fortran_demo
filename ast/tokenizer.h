#ifndef LEXER_H
#define LEXER_H
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#define SPACECHAR 10

enum token_types {
    TOKEN_ID,
    TOKEN_EQUALS,
    TOKEN_STRING,
    TOKEN_SEMI,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_RBRACE,
    TOKEN_LBRACE,
    TOKEN_COMMA,
    TOKEN_ADD,
    TOKEN_DIV,
    TOKEN_ROOT,
    TOKEN_EOF};

/**
 * @brief Token 
 * @detail Tokens found in contents.
 */
typedef struct token_struct{

    enum token_types type; /**< Token type */
    char *value; /**< Token value */
    int precedence; /**< Priority */
    void (*__del__)(struct token_struct *); /**< Destructore*/
}Token;

/**
 * @brief Lexer
 * @detail Lexer for tokenizing the content.
 */
typedef struct lexer_struct{

    char c; /**< Character */
    size_t i; /**< Character index */
    char *contents; /**< Content to tokenize */
    
    void (*__del__)(struct lexer_struct *self);
    void (*advance)(struct lexer_struct *self);
    struct token_struct *(*get_next_token)(struct lexer_struct *self);
    void (*skip_whitespace)(struct lexer_struct *self);
    struct token_struct *(*collect_id)(struct lexer_struct *self);
    struct token_struct *(*collect_string)(struct lexer_struct *self);
    char *(*get_current_char_as_string)(struct lexer_struct *self);

}Lexer;


/* TOKEN */
Token *Token__init__(int type, char *value);
void Token__del__(Token *self);

/* LEXER */
Lexer *Lexer__init__(char *contents);
void Lexer__del__(Lexer *self);
void Lexer_advance(Lexer *self);
void Lexer_skip_whitespace(Lexer *self);
Token *Lexer_get_next_token(Lexer *self);
Token *Lexer_collect_string(Lexer *self);
Token *Lexer_collect_id(Lexer *self);
Token *Lexer_advance_with_token(Lexer *self, Token *token);
char *Lexer_get_current_char_as_string(Lexer *self);


#endif
