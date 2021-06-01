#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "parserobject.h"
#include "visitorobject.h"
#include "version.h"


int main(int argc, char **argv){

    int i, verbose;

    printf("VERSION = %d\n", progcmake_VERSION_MAJOR);

    char *input = "Rel + (Rox / Wdox) + Rox";

    printf("Input=%s\n", input);
    
    Lexer *lexer = Lexer__init__(input);
    
    verbose = 1;
    Parser *parser = Parser__init__(lexer, verbose);
    AstNode *ast = parser->parse(parser);
    
    AstVisitor *visitor = AstVisitor__init__();
    
    char *infix ;
    infix = visitor->get_infix(visitor, ast);
    printf("Result=%s\n", infix);
    
    visitor->init_parameters(visitor, ast);
    printf("visitor->n = %d\n", visitor->n);
    visitor->p[0] = 150.0;
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
