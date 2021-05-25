#ifndef VISITOROBJECT_H
#define VISITOROBJECT_H

#include"tokenobject.h"
#include"astobject.h"

typedef struct ast_visitor_struct{
    
    char *value;
    char *(*get_infix)(struct ast_visitor_struct *self, AstNode *node);
    void (*__del__)(struct ast_visitor_struct *self);


}AstVisitor;

/* METHODS */
AstVisitor *AstVisitor__init__(void);
char *AstVisitor_get_infix(AstVisitor *self, AstNode *node);
void AstVisitor__del__(AstVisitor *self);

#endif
