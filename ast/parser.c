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
    self->parse_pop_operator = &Parser_parse_pop_operator;
    self->__del__ = &Parser__del__;
    
    return self;
}

void Parser_eat(Parser *self){
    self->previous_token = self->current_token;
    self->current_token = self->lexer->get_next_token(self->lexer);
}

void Parser_parse(Parser *self, int verbose){

    Token *last_operator=NULL;
    
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
                if (self->nops > 0)
                {
                    last_operator = self->operators[self->nops-1];
                }else{
                    last_operator = self->current_token;
                }
                if (last_operator != NULL)
                {
                    while((self->nops > 0) 
                          &((last_operator->precedence > self->current_token->precedence)
                           |((last_operator->precedence == self->current_token->precedence) & (self->current_token->associative == 'L'))) 
                          & (last_operator->type != TOKEN_LPAREN))
                    { 
                        self->parse_pop_operator(self);
                    }
                    self->parse_operators(self);
                }
                break;
            case TOKEN_LPAREN:
                self->parse_operators(self);
                break;

            case TOKEN_RPAREN:
                while ((self->operators[self->nops-1]->type != TOKEN_LPAREN) & (self->nops>0))
                {
                
                    self->parse_pop_operator(self);
                
                }
                if(self->operators[self->nops-1]->type == TOKEN_LPAREN){
                    self->operators[self->nops-1]->__del__(self->operators[self->nops-1]);
                    self->nops -= 1;
                    self->operators = (Token **) realloc(self->operators, self->nops * sizeof(Token *));
                    self->current_token->__del__(self->current_token);
                }
                break;
        }
    int i;
    for(i=0;i<self->nops; i++){printf("stack %s\n", self->operators[i]->value);}
    }while (self->current_token->type != TOKEN_EOF);

    while (self->nops >0){
        self->parse_pop_operator(self);
    }
}

void Parser_parse_pop_operator(Parser *self){
        self->nelmts += 1;
        self->elements = (Token **) realloc(self->elements, self->nelmts * sizeof(Token *));
        self->elements[self->nelmts-1] = self->operators[self->nops-1];
        self->nops -= 1;
        self->operators = (Token **) realloc(self->operators, self->nops * sizeof(Token *));
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

/* This implementation does not implement composite functions,functions with variable number of arguments, and unary operators.


while there are tokens to be read:
    read a token.
    if the token is a number, then:
        push it to the output queue.
    else if the token is a function then:
        push it onto the operator stack 
    else if the token is an operator then:
        while ((there is an operator at the top of the operator stack)
              and ((the operator at the top of the operator stack has greater precedence)
                  or (the operator at the top of the operator stack has equal precedence and the token is left associative))
              and (the operator at the top of the operator stack is not a left parenthesis)):
            pop operators from the operator stack onto the output queue.
        push it onto the operator stack.
    else if the token is a left parenthesis (i.e. "("), then:
        push it onto the operator stack.
    else if the token is a right parenthesis (i.e. ")"), then:
        while the operator at the top of the operator stack is not a left parenthesis:
            pop the operator from the operator stack onto the output queue.
        #If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. 
        if there is a left parenthesis at the top of the operator stack, then:
            pop the operator from the operator stack and discard it
        if there is a function token at the top of the operator stack, then:
            pop the function from the operator stack onto the output queue.
#After while loop, if operator stack not null, pop everything to output queue
if there are no more tokens to read then:
    while there are still operator tokens on the stack:
        If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. 
        pop the operator from the operator stack onto the output queue.
exit.*/
