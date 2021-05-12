#include "tokenizer.h"
#include "parser.h"


int main(int argc, char **argv){

    char *input = "Rel + (Rct+Wdox) / Qdl ";

    printf("Input=%s\n", input);

    
    Lexer *lexer = Lexer__init__(input);

    Token *token = NULL;
    
    /*do
    { 
        if (token != NULL){
            token->__del__(token);
        }
        token = Lexer_get_next_token(lexer);
        printf("TOKEN(%d, %s)\n", token->type, token->value);
    }
    while (token->type != TOKEN_EOF);*/

    Parser *parser = Parser__init__(lexer);
    
    Parser_parse(parser);

    lexer->__del__(lexer);

    return 0;

}
