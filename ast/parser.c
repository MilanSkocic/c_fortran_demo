#include "parser.h"

double complex resistance(double *p, double w){
    return (double complex) (*p);
}

double complex capacitance(double *p, double w){
    return 1/(I*w*(*p));
}

AstNode *AstNode__init__(int type, AstNode * left, AstNode *right)
{
    AstNode *self = (AstNode *)calloc(1, sizeof(AstNode));
    self->type = type;
    self->right = NULL;
    self->left = NULL;
    self->op = NULL;

    switch(self->type)
    {
        case AST_R:
            self->eval =  &resistance;
            break;
        case AST_C:
            self->eval = &capacitance;
            break;
        default:
            self->eval = NULL;
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
    self->current_token = NULL;
    self->previous_token = NULL;
    return self;
}

void Parser_eat(Parser *self){
    self->previous_token = self->current_token;
    self->current_token = self->lexer->get_next_token(self->lexer);
}

AstNode *Parser_parse(Parser *self){
    
    do{
        Parser_eat(self);
        
        if (self->current_token->type == TOKEN_ID){
           if (self->current_token->value[0] == 'R'){
            printf("Resistance = %s \n", self->current_token->value); 
            AstNode__init__(AST_R, NULL, NULL);
           }  
           if (self->current_token->value[0] == 'C'){
            printf("Capacitance = %s \n", self->current_token->value); 
            AstNode__init__(AST_C, NULL, NULL);
           }  
            if (self->current_token->value[0] == 'Q'){
            printf("CPE = %s \n", self->current_token->value); 
            AstNode__init__(AST_Q, NULL, NULL);
           } 
            if (self->current_token->value[0] == 'W'){
                switch (self->current_token->value[1]){
                    case 'D':
                    case 'd':
                        printf("Wd = %s \n", self->current_token->value); 
                        AstNode__init__(AST_WD,NULL, NULL);
                        break;
                    case 'M':
                    case 'm':
                        printf("Wm = %s \n", self->current_token->value); 
                        AstNode__init__(AST_WM,NULL,NULL);
                        break;
                }
            }
        }
    }while (self->current_token->type != TOKEN_EOF);
}




