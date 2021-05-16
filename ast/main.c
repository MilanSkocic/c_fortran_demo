#include "parser.h"
#include "version.h"


int main(int argc, char **argv){

    int i, verbose;

    printf("VERSION = %d\n", progcmake_VERSION_MAJOR);

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
    
    verbose = 1;
    Parser_parse(parser, verbose);
    
    printf("nops=%d\n", parser->nops);
    printf("OPERATORS\n"); 
    for (i=0; i<parser->nops; i++){
        printf("%s %d %c\n", parser->operators[i]->value,
                                parser->operators[i]->precedence,
                                parser->operators[i]->associative);
       
    }
    
    printf("ELEMENTS\n");
    for (i=0; i<parser->nelmts; i++){
        printf("%s %d %c\n", parser->elements[i]->value,
                                parser->elements[i]->precedence,
                                parser->elements[i]->associative);
       
    }

    lexer->__del__(lexer);

    return 0;

}
