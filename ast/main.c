#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "parserobject.h"
#include "visitorobject.h"
#include "version.h"


int main(int argc, char **argv){

    int i;

    printf("VERSION = %d\n", progcmake_VERSION_MAJOR);

    char *input = "Rel + (Rct+Wdox) / Rox ";

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
    
    visitor->init_parameters(visitor, ast);
    printf("visitor->n = %d\n", visitor->n);
    visitor->p[0] = 150.0;
    visitor->p[1] = 10.0;
    visitor->p[2] = 1.0;
    visitor->p[3] = 12.0;
    visitor->p[4] = 551.0;
    visitor->p[5] = 4551.0;
    for(i=0; i<visitor->n; i++){
        printf("p[%d]=%.1f\n", i, visitor->p[i]);
    }
    
    double w = 1.0;
    double complex result;
    for(i=0; i<1; i++){
        result = visitor->eval(visitor, ast, NULL, &w);
        printf("Final %.1f %.1f\n", creal(result), cimag(result));
    }


    lexer->__del__(lexer); /* delete lexer */
    parser->__del__(parser); /* delete queue and operators */
    ast->__del__(ast); /* delete all nodes and tokens */
    visitor->__del__(visitor); /* delete visitor */

    return 0;
}
