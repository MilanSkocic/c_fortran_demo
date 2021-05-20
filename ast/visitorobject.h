#ifndef VISITOROBJECT_H
#define VISITOROBJECT_H

#include<stdlib.h>
#include"tokenobject.h"

typedef struct ast_visitor_struct{

    char *value;
    void (*visit)(struct ast_visitor_struct *self, Token *token);


}AstVisitor;

/* METHODS */
AstVisitor *AstVisitor__init__(void);
void AstVisitor_visit(AstVisitor *self, Token *token);

#endif
