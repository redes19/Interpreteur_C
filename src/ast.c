//
// Created by Mathéo Pion on 06/10/2024.
//
#include "ast.h"
#include "stdlib.h"
#include "stdio.h"

/*
 * Fonction pour créer un nœud de l'arbre AST (Abstract Syntax Tree) avec un type de token et une valeur.
 * Left et right sont initialisés à NULL, car on ne sait pas encore quels seront les enfants de ce nœud.
 */
ASTNode *create_node(TokenType type, int value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type; // initialise le type (opérateur ou nombre)
    node->value = value; // initialise la valeure du noeud
    node->left = NULL; //met les enfants à null
    node->right = NULL;
    return node;
}

/*
 * Fonction pour créer un nœud opérateur dans l'arbre AST avec des sous-nœuds gauche et droit.
 * Le type du nœud sera un opérateur (ex: PLUS, MINUS), et left/right représentent les sous-arbres opérés.
 */
ASTNode *create_operator_node(TokenType type, ASTNode *left, ASTNode *right) {
    ASTNode *node = create_node(type, 0);
    node->left = left;
    node->right = right;
    return node;
}

/*
 * Fonction d'évaluation récursive de l'AST. Elle calcule la valeur d'un nœud en fonction de son type.
 * Si c'est un nombre, elle retourne la valeur. Sinon, elle évalue les sous-arbres et applique l'opérateur.
 */
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