#include <stdio.h>
#include <stdlib.h>
#include "AST.h"

Variable variables[MAX_VAR];
int variable_count = 0;

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
        printf("erreur 1\n");
        exit(1);
    }
}

// Fonction pour retirer une valeur de la pile
void *pop(Stack *stack) {
    if(!is_empty(stack)){
        return stack->data[stack->top--];
    }
    printf("Entree invalide\n");
    exit(2);
}

// Fonction pour voir la valeur au sommet de la pile
void *peek(Stack *stack) {
    if (!is_empty(stack)) {
        return stack->data[stack->top];
    }
    printf("Entree invalide\n");
    exit(3);
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

// Fonction pour créer un noeud d'operateur
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

// Fonction pour créer un noeud de l'AST qui correspond à un identifiant
ASTNode* create_ast_expression(const char *identifier_name, int value) {
    if (identifier_name == NULL) {
        printf("Erreur: identifier_name est NULL\n");
        exit(1);
    }

    ASTNode *node = malloc(sizeof(ASTNode));
    if (node == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    node->type = ASSIGN;
    node->left = malloc(sizeof(ASTNode));
    if (node->left == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    node->left->type = IDENTIFIER;
    strncpy(node->left->name, identifier_name, MAX);
    node->right = malloc(sizeof(ASTNode));
    if (node->right == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    // Stocke la valeur directement dans le nœud de droite en tant que NUMBER
    node->right->type = NUMBER;
    node->right->value = value;
    node->right->left = NULL;
    node->right->right = NULL;


    return node;
}




void print_ast(ASTNode *node, int level) {
    static int is_first_call = 1;
    if (is_first_call) {
        printf("\nArbre de syntaxe abstraite :\n");
        printf("-----------------------------\n");
        is_first_call = 0;
    }

    if (node == NULL) {
        return;
    }

    // Indentation en fonction du niveau
    for (int i = 0; i < level; i++) {
        printf("   ");
    }

    if (node->type == ASSIGN) {
        // Ne rien afficher pour les assignations
        return;
    }
    if (node->type == NUMBER) {
        printf("Nombre : %d\n", node->value);
    }
    else if (node->type == IDENTIFIER) {
        printf("Identifiant : %s\n", node->name);
    }
    else {
        printf("Operateur : ");
        switch (node->type) {
            case PLUS: printf("+\n"); break;
            case MINUS: printf("-\n"); break;
            case MULT: printf("*\n"); break;
            case DIV: printf("/\n"); break;
            default: printf("Inconnu\n"); break;
        }
        print_ast(node->left, level + 1);
        print_ast(node->right, level + 1);
    }
}

ASTNode *parser(Token *tokens) {
    Stack operators = create_stack(); // Contiendra les opérateurs
    Stack output = create_stack(); // Contiendra les noeuds de l'AST

    int pos = 0;
    Token current_token = tokens[pos];


    while (current_token.type != TOKEN_EOF) {
        if (current_token.type == NUMBER) { // Si le token est un nombre
            //printf("N ");
            push(&output, create_ast_node(current_token.value));
        }else if (is_operator(current_token.type)) {   // Si le token est un opérateur
            //printf("O ");
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
            //printf("LP ");
            Token *parentToken = malloc(sizeof(Token));
            *parentToken = current_token;
            push(&operators, parentToken);
        } else if (current_token.type == RPAREN) {  // Si le token est une parenthèse fermante
            //printf("LR ");
            while (!is_empty(&operators) && ((Token*)peek(&operators))->type != LPAREN) {
                Token *op = pop(&operators);
                ASTNode *right = pop(&output);
                ASTNode *left = pop(&output);
                push(&output, create_ast_operator(op->type, left, right));
            }
            if (!is_empty(&operators)) {
                pop(&operators);
            }
        }
        else if (current_token.type == IDENTIFIER) { // Si le token est un identifiant
            //printf("I ");
            Token nextToken = tokens[pos + 1];
            if (nextToken.type == ASSIGN) {
                //printf("IN\n");
                pos += 2;
                int value = eval_ast(parser(&tokens[pos]));

                return create_ast_expression(current_token.identifier, value);
            }
            //printf("OUT\n");
            push(&output, create_ast_expression(current_token.identifier, getVariable(current_token.identifier)));
        } else if (current_token.type == PRINT) {
            //printf("PRINT\n");
            Token nextToken = tokens[pos + 1];
            if (nextToken.type == LPAREN) {
                //printf("1\n");
                pos += 2;
                Token next = tokens[pos];
                if (next.type == IDENTIFIER) {
                    printf("%d\n\n", getVariable(next.identifier));
                } else {
                    printf("%d\n", eval_ast(parser(&tokens[pos])));
                }
            }
        }
        pos++;
        current_token = tokens[pos];
    }

    // Ajouter les opérateurs restants à la pile output
    while (!is_empty(&operators)) {
        Token *op = pop(&operators);
        ASTNode* right = pop(&output);
        ASTNode* left = pop(&output);
        push(&output, create_ast_operator(op->type, left, right));
    }

    if (is_empty(&output)) {
        return NULL;
    }

    ASTNode *result = pop(&output);

    while (!is_empty(&output)) {
        free_ast(pop(&output));
    }

    /*printf("parser\n");
    print_ast(result);
    printf("\n");*/

    return result;
}

// Fonction pour évaluer AST
int eval_ast(ASTNode *node) {
    if (node == NULL) {
        return 0;
    }

    // Évaluer les nœuds selon leur type
    switch (node->type) {
        case NUMBER:
            return node->value;
        case IDENTIFIER:
            return getVariable(node->name);
        case ASSIGN:
            int value = eval_ast(node->right);
            setVariable(node->left->name, value);
            return value;
        case PLUS:
            return eval_ast(node->left) + eval_ast(node->right);
        case MINUS:
            return eval_ast(node->left) - eval_ast(node->right);
        case MULT:
            return eval_ast(node->left) * eval_ast(node->right);
        case DIV:
            return eval_ast(node->left) / eval_ast(node->right);
        default:
            return 0;
    }
}


void free_ast(ASTNode *node) {
    if (node == NULL) {
        return;
    }
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}

void free_tokens(Token *tokens, int count) {
    for (int i = 0; i < count; i++) {
        if (tokens[i].identifier) {
            free(tokens[i].identifier);
        }
    }
    free(tokens);
}

int getVariable(const char *name) {
    //printf("\ngetVariable %s\n", name);
    for (int i = 0; i < variable_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }

    printf("\nErreur: Variable non declaree\n");
    exit(1);
}

void setVariable(const char *name, int value) {
    //printf("\nsetVariable name: %s, value: %d\n", name, value);
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