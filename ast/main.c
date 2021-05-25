#include <stdio.h>
#include <stdlib.h>
#include "parserobject.h"
#include "visitorobject.h"
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
    AstNode *ast = parser->parse(parser);
    
    
    printf("QUEUE\n");
    for (i=0; i<parser->nqueue; i++){
        printf("%s %d %c\n", parser->queue[i]->value,
                                parser->queue[i]->precedence,
                                parser->queue[i]->associative);
       
    }

    AstVisitor *visitor = AstVisitor__init__();
    
    char *infix ;
    infix = visitor->get_infix(visitor, ast);

    printf("Result=%s\n", infix);

    lexer->__del__(lexer); /*  */
    ast->__del__(ast); /* delete all nodes and tokens */
    visitor->__del__(visitor); /* delete visitor */

    return 0;
}
