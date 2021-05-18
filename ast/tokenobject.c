#include"tokenobject.h"

char *ELEMENTS[] = {"R", "C", "L", "Q", "W", "Wd", "Wm"};


/**
 * @brief Token constructor
 * @param type Type of token
 * @param value Value of token
 */
Token *Token__init__(int type, char *value)
{

    Token *self = (Token *)calloc(1, sizeof(Token));
    self->type = type;
    self->value = value;
    self->set_eval = &Token_set_eval;
    self->set_eval(self);
    self->__del__ = &Token__del__;

    switch (self->type){
        case TOKEN_ELEMENT:
            self->precedence = 1;
            self->associative = 'L';
	    break;
        case TOKEN_ADD:
            self->precedence = 2;
            self->associative = 'L';
            break;
        case TOKEN_DIV:
            self->precedence = 3;
            self->associative = 'L';
        case TOKEN_MUL:
            self->precedence = 3;
            self->associative = 'L';
            break;
        case TOKEN_POW:
            self->precedence = 4;
            self->associative = 'R';
            break;
        default:
            self->precedence = 0;
            self->associative = 'L';
    }
    return self;

}

/**
 * @brief Token destructor
 */
void Token__del__(Token *self){
    free(self->value);
    free(self);

}

void Token_set_eval(Token *self){

	switch (self->value[0]){
	
		case 'R':
			self->eval = &resistance;
		case 'C':
			self->eval = &capacitance;
		default:
			self->eval = NULL;
	}

}
