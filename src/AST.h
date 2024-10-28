#ifndef AST.H
#define AST.H
#define MAX 100
#define MAX_VAR 100
#include "lexer.h"
#include <string.h>

// Structure
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

typedef struct {
    char *name[MAX];
    int value;
}Variable;

// Variables
Variable variables[MAX_VAR];
int variable_count = 0;


// Function
void print_ast(ASTNode *node);

ASTNode *parser_ast(Token *tokens);

int eval_ast(ASTNode *node);

// Getter and Setterc'est(
inline int getVariable(char *name) {
    for (int i = 0; i < variable_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }

    printf("Erruer: Variable %s non déclarée\n", name);
    exit(1);
}

inline void setVariable(char *name, int value) {
    for (int i = 0; i < variable_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].value = value;
            return;
        }
    }

    if (variable_count < MAX_VAR) {
        strncpy(variables[variable_count].name, name, MAX);
        variables[variable_count].value = value;
        variable_count++;
    }
    else {
        printf(("Erreur avec la variable\n"));
        exit(1);
    }
}

#endif