#include <stdio.h>
#include <stdlib.h>
#include "AST.h"

// Fonction pour créer une pile stack (shunting yard algorithm)
Stack create_stack() {
    Stack stack;
    stack.top = -1; // Initialisation de la pile vide
    return stack;
}

// Fonction pour voir si un token est un opérateur
int is_operator(TokenType type) {
    return type == PLUS || type == MINUS || type == MULT || type == DIV || type == MOD;
}

// Fonction pour voir si la pile est vide
int is_empty(Stack *stack) {
    return stack->top == -1;
}

// Fonction pour ajouter une valeur à la pile
void push(Stack *stack, void *value) {
    if(stack->top < MAX - 1) {
        stack->data[++stack->top] = value; // increment le tableau et ajoute value
    } else {
        printf("Stack empty\n");
        exit(1);
    }
}

// Fonction pour retirer une valeur de la pile
void *pop(Stack *stack) {
    if(!is_empty(stack)){
        return stack->data[stack->top--];
    } else {
        printf("Stack empty\n");
        exit(1);
    }
}

// Fonction pour voir la valeur au sommet de la pile
void *peek(Stack *stack) {
    if (!is_empty(stack)) {
        return stack->data[stack->top];
    } else {
        printf("Stack empty\n");
        exit(1);
    }
}

// Fonction qui retourne la priorité d'un oparateur
int order(TokenType type) {
    if (type == MULT || type == DIV || type == MOD) {
        return 2;
    } else if (type == PLUS || type == MINUS) {
        return 1;
    } else {
        return 0;
    }
}

// Fonction pour créer un noeud d'operateur'
ASTNode* create_ast_operator(char operator, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (node == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    node->type = (unsigned char)operator;
    node->value = 0;
    node->left = left;
    node->right = right;
    return node;
}

// Fonction pour créer un noeud de l'AST qui correspond à un nombre
ASTNode* create_ast_node(int value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (node == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    node->type = NUMBER;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}


void print_ast(ASTNode *node) {
    if (node == NULL) {
        return;
    }
    print_ast(node->left);
    print_ast(node->right);

    if (node->type == NUMBER) {
        printf("%d ", node->value);
    } else {
        switch (node->type) {
            case PLUS:
                printf("+ ");
            break;
            case MINUS:
                printf("- ");
            break;
            case MULT:
                printf("* ");
            break;
            case DIV:
                printf("/ ");
            break;
            default:
                printf("? ");
            break;
        }
    }
}

ASTNode *parser(Token *tokens) {
    Stack operators = create_stack(); // Contiendra les opérateurs
    Stack output = create_stack(); // Contiendra les noeuds de l'AST

    int pos = 0;
    Token current_token = tokens[pos];

    while (current_token.type != TOKEN_EOF) {
        if (current_token.type == NUMBER) { // Si le token est un nombre
            printf("condition nombre \n");
            push(&output, create_ast_node(current_token.value));
        }else if (is_operator(current_token.type)) {   // Si le token est un opérateur
            // Tant que la pile d'opérateurs contient des opérateurs avec une priorité supérieure ou égale
            while(!is_empty(&operators) && order(((Token*)peek(&operators))->type) >= order(current_token.type)) {
                Token *op = pop(&operators);
                ASTNode *right = pop(&output);
                ASTNode *left = pop(&output);
                push(&output, create_ast_operator(op->type, left, right)); // Ajoute le noeud AST correspondant
            }
            // Ajoute l'opérateur actuel à la pile
            Token *opToken = malloc(sizeof(Token));
            *opToken = current_token;
            push(&operators, opToken);
        }
        else if (current_token.type == LPAREN) {  // Si le token est une parenthèse ouvrante
            printf("condition parenthèse gauche\n");
            push(&output, create_ast_node(current_token.type));
        } else if (current_token.type == RPAREN) {  // Si le token est une parenthèse fermante
            printf("condition droite\n");
            while (((Token*)peek(&operators))->type != RPAREN) {
                Token *op = pop(&operators);
                ASTNode *left = pop(&output);
                ASTNode *right = pop(&output);
                push(&output, create_ast_operator(op->type, left, right));
            }
            pop(&operators);
        }
        pos++;
        current_token = tokens[pos];
    }

    // Ajouter les opérateurs restants à la pile output
    while (!is_empty(&operators)) {
        printf("Finalizing operator stack\n");
        Token *op = pop(&operators);
        ASTNode* right = pop(&output);
        ASTNode* left = pop(&output);
        push(&output, create_ast_operator(op->type, left, right));
    }

    return pop(&output);
}