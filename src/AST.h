#ifndef AST.H
#define AST.H
#define MAX 100
#include "lexer.h"

typedef struct ASTNode {
    TokenType type;
    int value;
    struct ASTNode *left;  // Fils gauche
    struct ASTNode *right; // Fils droit
} ASTNode;

typedef struct {
    void *data[MAX];
    int top;
}Stack;

void print_ast(ASTNode *node);

ASTNode *parser_ast(Token *tokens);



#endif