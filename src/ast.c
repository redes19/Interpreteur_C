//
// Created by Mathéo Pion on 06/10/2024.
//
#include "ast.h"
#include "stdlib.h"
#include "stdio.h"

/*En gros on créé un noeud et on initialise le type et la valeur mais on laisse left et right null
pour agir dessus après*/
ASTNode *create_node(TokenType type, int value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ASTNode *create_operator_node(TokenType type, ASTNode *left, ASTNode *right) {
    ASTNode *node = create_node(type, 0);
    node->left = left;
    node->right = right;
    return node;
}

int eval(ASTNode *node) {
    if(node->type == NUMBER) {
        return node->value;
    }

    int left_val = eval(node->left);
    int right_val = eval(node->right);

    switch (node->type) {
        case PLUS: return left_val + right_val;
        case MINUS: return left_val - right_val;
        case MULT: return left_val * right_val;
        case DIV: return left_val / right_val;
        default:
            printf("Erreur: opération invalide \n");
            exit(1);
    }
}