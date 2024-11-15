#ifndef AST_H
#define AST_H
#define MAX 100
#define MAX_VAR 100
#include "lexer.h"
#include <string.h>

// Structure
typedef struct ASTNode {
    TokenType type;
    int value;
    char name[MAX]; // Nom de la variable
    struct ASTNode *left;  // Fils gauche
    struct ASTNode *right; // Fils droit
} ASTNode;

typedef struct {
    void *data[MAX];
    int top;
}Stack;

typedef struct {
    char name[MAX];
    int value;
}Variable;

// Variables
extern Variable variables[MAX_VAR];
extern int variable_count;


// Function
void print_ast(ASTNode *node);

ASTNode *parser_ast(Token *tokens);
ASTNode* create_ast_node(int value);
ASTNode* create_ast_operator(char operator, ASTNode *left, ASTNode *right);

int eval_ast(ASTNode *node);

// Getter and Setter
int getVariable(const char *name);
void setVariable(const char *name, int value);


// Free memory
void free_ast(ASTNode *node);
void free_tokens(Token *tokens, int count);


#endif