#include "parserobject.h"
#include "version.h"


int main(int argc, char **argv){

    int i;

    printf("VERSION = %d\n", progcmake_VERSION_MAJOR);

    char *input = "Rel + (Rct+Wdox) / Qdl ";

    printf("Input=%s\n", input);

    
    Lexer *lexer = Lexer__init__(input);

    // Token *token = NULL;
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
    
    printf("QUEUE\n");
    for (i=0; i<parser->nqueue; i++){
        printf("%s %d %c\n", parser->queue[i]->value,
                                parser->queue[i]->precedence,
                                parser->queue[i]->associative);
       
    }

    AstVisitor *visitor = AstVisitor__init__(parser->ast);
    visitor->visit(visitor);

    printf("value = %s", visitor->value);

    lexer->__del__(lexer);

    return 0;

}
