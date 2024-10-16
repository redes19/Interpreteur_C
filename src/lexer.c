#include "lexer.h"

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
        default:return "Unknown";
    }
}

void new_token(TokenType type, int value, Token **tokens, int *i_token) {
    Token *temp = realloc(*tokens, sizeof(Token) * (*i_token + 1));

    // Vérifier si l'allocation de mémoire a réussi
    if (temp == NULL) {
        printf("Erreur d'allocation de mémoire\n");
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

Token *lexer(const char *input)
{
    Token *tokens = NULL;
    int position = 0;
    int i_token = 0;

    while (input[position] != '\0') {
        char pos_char = input[position];

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
            new_token(NUMBER, number, &tokens, &i_token);
            continue;
        }

        // Tokeniser les opérateurs dans l'input
        switch (pos_char) {
            case '+':
                new_token(PLUS, 0, &tokens, &i_token);
                break;
            case '-':
                new_token(MINUS, 0, &tokens, &i_token);
                break;
            case '*':
                new_token(MULT, 0, &tokens, &i_token);
                break;
            case '/':
                new_token(DIV, 0, &tokens, &i_token);
                break;
            case '(':
                new_token(LPAREN, 0, &tokens, &i_token);
                break;
            case ')':
                new_token(RPAREN, 0, &tokens, &i_token);
                break;
            default:
                printf("Entrée invalide: %c\n", pos_char);
                exit(1);
        }
        position++;
    }

    /*for (int i = 0; i < i_token; i++) {
        printf("Token %d: Type = %s, Value = %d\n", i, token_string(tokens[i].type), tokens[i].value);
    }*/

    // Marquer la fin des tokens
    tokens[i_token].type = TOKEN_EOF;
    return tokens;
}