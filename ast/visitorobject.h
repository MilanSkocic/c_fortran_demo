#ifndef VISITOROBJECT_H
#define VISITOROBJECT_H

#include"tokenobject.h"
#include"astobject.h"

typedef struct ast_visitor_struct{

    char *value;
    char*(*visit)(struct ast_visitor_struct *self, AstNode *node);


}AstVisitor;

/* METHODS */
AstVisitor *AstVisitor__init__(void);
char *AstVisitor_visit(AstVisitor *self, AstNode *node);

#endif
