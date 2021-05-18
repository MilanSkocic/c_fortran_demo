#ifndef TOKENOBJECT_H
#define TOKENOBJECT_H

#include<stdlib.h>
#include"eis.h"

#define SPACECHAR 10

/**
 * @brief Token types
 */
enum token_types {
    TOKEN_ELEMENT,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_ADD,
    TOKEN_DIV,
    TOKEN_POW,
    TOKEN_MUL,
    TOKEN_SUB,
    TOKEN_EOF};

/**
 * @brief Token structure
 * @detail Tokens found in contents.
 */
typedef struct token_struct{

    enum token_types type; /**< Token type */
    char *value; /**< Token value */
    int precedence; /**< Priority */
    char associative;
    void (*__del__)(struct token_struct *); /**< Destructore*/
    double complex (*eval)(double *, double );
    void (*set_eval)(struct token_struct *);
}Token;


/* METHODS */
Token *Token__init__(int type, char *value);
void Token__del__(Token *self);
void Token_set_eval(Token *self);


#endif
