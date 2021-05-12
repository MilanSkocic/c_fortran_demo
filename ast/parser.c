#include "parser.h"

double complex resistance(double *p, double w){
    return (double complex) (*p);
}

double complex capacitance(double *p, double w){
    return 1/(I*w*(*p));
}

AstNode *AstNode__init__(int type, AstNode *top, AstNode * left, AstNode *right)
{
    AstNode *self = (AstNode *)calloc(1, sizeof(AstNode));
    self->type = type;
    self->top = NULL;
    self->right = NULL;
    self->left = NULL;
    self->op = NULL;
    self->eval = NULL;

    switch(self->type)
    {
        case AST_R:
            self->eval =  &resistance;
            break;
        case AST_C:
            self->eval = &capacitance;
            break;
        case AST_DIV:
        case AST_ADD:
            self->eval = NULL;
            self->left = left;
            self->right = right;
            break;
    }

    self->op = NULL;
    return self;
}

void AstNode__del__(AstNode* self){
    free(self);
}

Parser *Parser__init__(Lexer *lexer){
    Parser *self = (Parser *) calloc(1, sizeof(Parser));
    self->lexer = lexer;
    self->elements = NULL;
    self->nelmts = 0;
    self->operators = NULL;
    self->nops = 0; 
    self->current_token = NULL;
    self->previous_token = NULL;
    
    /* METHODS */
    self->parse_elements = &Parser_parse_elements;
    self->parse_operators = &Parser_parse_operators;
    self->parse = &Parser_parse;
    self->__del__ = &Parser__del__;
    
    return self;
}

void Parser_eat(Parser *self){
    self->previous_token = self->current_token;
    self->current_token = self->lexer->get_next_token(self->lexer);
}

void Parser_parse(Parser *self, int verbose){
    
    do{
        if(verbose){printf("EATING TOKEN...\n");}
        Parser_eat(self);
        if(verbose)
        {
            printf("\ttype=%d, value=%s, precedence=%d, %c\n", 
                    self->current_token->type,
                    self->current_token->value,
                    self->current_token->precedence,
                    self->current_token->associative);
        }
        
        switch(self->current_token->type){
        
            case TOKEN_ID:
                self->parse_elements(self);
                break;
            case TOKEN_EOF:
                break;   
            case TOKEN_DIV:
            
            case TOKEN_ADD:
            
            case TOKEN_POW:
            
            case TOKEN_MUL:
                self->parse_operators(self);
                break;
        }
    }while (self->current_token->type != TOKEN_EOF);
}

void Parser_parse_operators(Parser *self){     
        self->nops += 1;
        self->operators = (Token **) realloc(self->operators, self->nops * sizeof(Token *));
        self->operators[self->nops-1] = self->current_token;        
}


void Parser_parse_elements(Parser *self){
    self->nelmts += 1;
    self->elements = (Token **) realloc(self->elements, self->nelmts * sizeof(Token *));
    self->elements[self->nelmts-1] = self->current_token;  
}


void Parser__del__(Parser *self){

    int i;
    
    for (i=0;i<self->nops; i++){
        self->operators[i]->__del__(self->operators[i]);
    }
    
    for (i=0; i<self->nelmts; i++){
        self->elements[i]->__del__(self->elements[i]);
    }
    
    free(self->operators);
    free(self->elements);

}


