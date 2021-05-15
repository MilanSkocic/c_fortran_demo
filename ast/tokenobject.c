#include"tokenobject.h"

/**
 * @brief Token constructor
 * @param type Type of token
 * @param value Value of token
 */
Token *Token__init__(int type, char *value)
{

    Token *new_token = (Token *)calloc(1, sizeof(Token));
    new_token->type = type;
    new_token->value = value;
    new_token->precedence = 0;
    new_token->associative = 'L';
    new_token->__del__ = &Token__del__;
    
    switch (new_token->type){
        case TOKEN_ID: 
            new_token->precedence = 1;
            new_token->associative = 'L';
            break;
        case TOKEN_ADD:
            new_token->precedence = 2;
            new_token->associative = 'L';
            break;
        case TOKEN_DIV:
            new_token->precedence = 3;
            new_token->associative = 'L';
        case TOKEN_MUL:
            new_token->precedence = 3;
            new_token->associative = 'L';
            break;
        case TOKEN_POW:
            new_token->precedence = 4;
            new_token->associative = 'R';
            break;
        default:
            new_token->precedence = 0;
            new_token->associative = 'L';
    }
    return new_token;

}

/**
 * @brief Token destructor
 */
void Token__del__(Token *self){
    free(self->value);
    free(self);

}

