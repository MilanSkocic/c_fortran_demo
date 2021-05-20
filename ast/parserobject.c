#include "parserobject.h"


Parser *Parser__init__(Lexer *lexer){
    Parser *self = (Parser *) calloc(1, sizeof(Parser));
    self->lexer = lexer;
    self->queue = NULL;
    self->nqueue = 0;
    self->operators = NULL;
    self->nodes = NULL;
    self->nops = 0;
    self->nnodes = 0;
    self->ast = NULL;
    self->current_token = NULL;
    self->previous_token = NULL;

    /* METHODS */
    self->push_element = &Parser_push_element;
    self->push_operator = &Parser_push_operator;
    self->parse = &Parser_parse;
    self->pop_operator = &Parser_pop_operator;
    self->discard_lparen = &Parser_discard_lparen;
    self->push_node = &Parser_push_node;
    self->__del__ = &Parser__del__;

    return self;
}

void Parser__del__(Parser *self){

    int i;

    for (i=0;i<self->nops; i++){
        self->operators[i]->__del__(self->operators[i]);
    }

    for (i=0; i<self->nqueue; i++){
        self->queue[i]->__del__(self->queue[i]);
    }

    free(self->operators);
    free(self->queue);

}

void Parser_eat(Parser *self){
    self->previous_token = self->current_token;
    self->current_token = self->lexer->get_next_token(self->lexer);
}

void Parser_parse(Parser *self){
    
    size_t i;
    Token *last=NULL;

    do{
        Parser_eat(self);

        switch(self->current_token->type){

            case TOKEN_ELEMENT:
                self->push_element(self);
                break;
            case TOKEN_EOF:
                break;
            case TOKEN_DIV:

            case TOKEN_ADD:

	        case TOKEN_SUB: 

            case TOKEN_POW:

            case TOKEN_MUL:
                if (self->nops > 0)
                {
                    last = self->operators[self->nops-1];
                }else{
                    last = self->current_token;
                }
                if (last != NULL)
                {
                    while((self->nops > 0)
                          &((last->precedence > self->current_token->precedence)
                           |((last->precedence == self->current_token->precedence) & (self->current_token->associative == 'L')))
                          & (last->type != TOKEN_LPAREN))
                    {
                        self->pop_operator(self);
                    }
                    self->push_operator(self);
                }
                break;
            case TOKEN_LPAREN:
                self->push_operator(self);
                break;

            case TOKEN_RPAREN:
                while ((self->operators[self->nops-1]->type != TOKEN_LPAREN) & (self->nops>0))
                {

                    self->pop_operator(self);

                }
                if(self->operators[self->nops-1]->type == TOKEN_LPAREN){
			self->discard_lparen(self);
                }
                break;
        }
    }while (self->current_token->type != TOKEN_EOF);

    while (self->nops > 0){
        self->pop_operator(self);
    }
    i = 0;
    while(self->queue[i]->type == TOKEN_ELEMENT){
	self->current_token = self->queue[i];
	self->push_node(self);
	i += 1;
	}
    for(i=i; i<self->nqueue; i++){
    	printf("QUEUE[%ld] = %s\n", i, self->queue[i]->value);
    }

}

void Parser_pop_operator(Parser *self){
        self->nqueue += 1;
        self->queue = (Token **) realloc(self->queue, self->nqueue * sizeof(Token *));
        self->queue[self->nqueue-1] = self->operators[self->nops-1];
        self->nops -= 1;
        self->operators = (Token **) realloc(self->operators, self->nops * sizeof(Token *));
}

void Parser_push_operator(Parser *self){
        self->nops += 1;
        self->operators = (Token **) realloc(self->operators, self->nops * sizeof(Token *));
        self->operators[self->nops-1] = self->current_token;
}

void Parser_push_element(Parser *self){
    self->nqueue += 1;
    self->queue = (Token **) realloc(self->queue, self->nqueue * sizeof(Token *));
    self->queue[self->nqueue-1] = self->current_token;
}

void Parser_push_node(Parser *self){
    self->nnodes += 1;
    printf("parser->nnodes = %d\n", self->nnodes);
    self->nodes = (AstNode **) realloc(self->nodes, self->nnodes * sizeof(AstNode *));
    self->nodes[self->nnodes-1] = AstNode__init__(self->queue[0], NULL, NULL);
}

void Parser_discard_lparen(Parser *self){

    self->operators[self->nops-1]->__del__(self->operators[self->nops-1]);
    self->nops -= 1;
    self->operators = (Token **) realloc(self->operators, self->nops * sizeof(Token *));
    self->current_token->__del__(self->current_token);
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
