//
// Created by Mathéo Pion on 06/10/2024.
//

#ifndef INTERPRETEUR_C_AST_H
#define INTERPRETEUR_C_AST_H

#include "lexer.h"

typedef struct ASTNode {
    TokenType type;
    int value;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode *create_node(TokenType type, int value);
ASTNode *create_operator_node(TokenType type, ASTNode *left, ASTNode *right);
int eval(ASTNode *node);

#endif //INTERPRETEUR_C_AST_H
