#include"visitorobject.h"

AstVisitor *AstVisitor__init__(){

    AstVisitor *self = (AstVisitor *)calloc(1, sizeof(AstVisitor));

    self->value = (char *)calloc(0, sizeof(char));
    self->visit = &AstVisitor_visit;

    return self;

}


void AstVisitor_visit(AstVisitor *self, Token *token){

    char *token_evaluation = token->eval(token->value);
    self->value = (char *)realloc(self->value, (strlen(token_evaluation)+strlen(self->value)+1) * sizeof(char));
    strcat(self->value, token_evaluation);
    printf("visitor->value=%s\n", self->value);

}
