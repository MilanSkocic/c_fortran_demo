#include "parser.h"


AstNode *AstNode__init__(int type)
{
    AstNode *self = (AstNode *)calloc(1, sizeof(AstNode));
    self->type = type;
    self->right = NULL;
    self->left = NULL;
    self->eval = NULL;
    self->op = NULL;
    return self;
}

void AstNode__del__(AstNode* self){
    free(self);
}

Parser *Parser__init__(Lexer *lexer){
    Parser *self = (Parser *) calloc(1, sizeof(Parser));
    self->lexer = lexer;
    self->current_token = self->lexer->get_next_token(lexer);
    self->previous_token = self->current_token;
    return self;
}

void Parser_eat(Parser *self, int token_type){

    if (self->current_token->type == token_type){
        self->previous_token = self->current_token;
        self->current_token = self->lexer->get_next_token(self->lexer);
    }
    else{
        printf("Unexpected token %s of type %d", self->current_token->value, self->current_token->type);
    }
}

AstNode *Parser_parse(Parser *self){
    self->current_token = self->lexer->get_next_token(self->lexer);
    
    if (self->current_token->type == TOKEN_ID){
        NULL;
    }
}

/*Ast *Parser_parse_statements(Parser *parser){
    
    AstNode *compound = Ast__init__(AST_COMPOUND);
    compound->compound_value = (AstNode **) calloc(1, sizeof(Ast*));
    Ast *ast_statement = parser_parse_statement(parser);
    compound->compound_value[0] = ast_statement;
    
    while(parser->current_token == TOKEN_SEMI){
        Parser_eat(parser, TOKEN_SEMI);
        Ast *ast_statement = parser_parse_statement(parser);
        compound->compound_size += 1;
        compound->compound_value = realloc(
                compound->compound_value, 
                compound->compound_size*sizeof(Ast *)
        );
        compound->compound_value[compound->compound_size-1] = ast_statement;
    }

    return compound;
}*/
