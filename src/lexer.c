#include "lexer.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


const char *token_string(TokenType token) {
    switch (token) {
        case PLUS:
            return "+";
        case MINUS:
            return "-";
        case MULT:
            return "*";
        case DIV:
            return "/";
        case LPAREN:
            return "(";
        case RPAREN:
            return ")";
        case ASSIGN:
            return "=";
        case IDENTIFIER:
            return "IDENTIFIER";
        case PRINT:
            return "PRINT";
        default:return "NUMBER";
    }
}

void create_token(TokenType type, int value, Token **tokens, int *i_token) {
    Token *temp = realloc(*tokens, sizeof(Token) * (*i_token + 1));

    // Vérifier si l'allocation de mémoire a réussi
    if (temp == NULL) {
        printf("Erreur d'allocation de memoire\n");
        exit(1);
    }

    // Réassigner le pointeur après realloc
    *tokens = temp;

    // Ajouter le nouveau token
    (*tokens)[*i_token].type = type;
    (*tokens)[*i_token].value = value;

    // Incrémenter le compteur de tokens
    (*i_token)++;
}

void create_token_identifier (const char *name, Token **tokens, int *i_token) {
    Token *temp = realloc(*tokens, sizeof(Token) * (*i_token + 1));
    if (temp == NULL) {
        printf("Erreur d'allocation de mémoire \n");
        exit(1);
    }

    *tokens = temp;

    (*tokens)[*i_token].type = IDENTIFIER;
    (*tokens)[*i_token].identifier = strdup(name);

    (*i_token)++;
}

Token *lexer(const char *input)
{
    Token *tokens = NULL;
    int position = 0;
    int i_token = 0;

    while (input[position] != '\0') {
        char pos_char = input[position];

        if (pos_char == '\n') {
            position++;
            continue;
        }

        if(pos_char == ' ') {
            position++;
            continue;
        }

        // Tokeniser les nombres dans l'input
        if(isdigit(pos_char)) {
            int number = 0;
            while (isdigit((input[position]))) {
                // Convertir le caractère en entier
                number = number * 10 + (input[position] - '0');
                position++;
            }
            create_token(NUMBER, number, &tokens, &i_token);
            continue;
        }

        // tokeniser les identifiants dans l'input
        if(isalpha(pos_char)) {
            int start_pos = position;
            while (isalnum(input[position])) {
                position ++;
            }
            int length = position - start_pos; // taille de la variable
            char *identifier = malloc(length + 1);
            if (identifier == NULL ) {
                printf("Erreur de mémoire\n");
                exit(1);
            }
            memcpy(identifier, &input[start_pos], length); // copier la variable dans l'identifiant
            identifier[length] = '\0';

            if (strncmp(identifier, "print", 5)==0) {
                create_token(PRINT,0, &tokens, &i_token);
            } else {
                create_token_identifier(identifier, &tokens, &i_token);
            }

            free(identifier);
            continue;
        }

        // Tokeniser les opérateurs dans l'input
        switch (pos_char) {
            case '+':
                create_token(PLUS, 0, &tokens, &i_token);
                break;
            case '-':
                create_token(MINUS, 0, &tokens, &i_token);
                break;
            case '*':
                create_token(MULT, 0, &tokens, &i_token);
                break;
            case '/':
                create_token(DIV, 0, &tokens, &i_token);
                break;
            case '(':
                create_token(LPAREN, 0, &tokens, &i_token);
                break;
            case ')':
                create_token(RPAREN, 0, &tokens, &i_token);
                break;
            case '=':
                create_token(ASSIGN, 0, &tokens, &i_token);
                break;
            default:
                printf("Caractere invalide a la position %d : %c\n", position, pos_char);
                exit(1);
        }
        position++;
    }

    /*for (int i = 0; i < i_token; i++) {
        if (tokens[i].type == IDENTIFIER) {
            printf("Token %d: Type : '%s', Identifier : %s\n", i, token_string(tokens[i].type), tokens[i].identifier);
        } else {
            printf("Token %d: Type : '%s', Value : %d\n", i, token_string(tokens[i].type), tokens[i].value);
        }
    }*/

    // Marquer la fin des tokens
    tokens[i_token].type = TOKEN_EOF;
    return tokens;
}
