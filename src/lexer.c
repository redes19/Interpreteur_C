#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

int is_number(char c) {
    return c >= '0' && c <= '9';
}

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
        default:return "Unknown";
    }
}

Token *lexer(const char *input)
{
    Token *tokens = malloc(sizeof(Token) * 100);
    int position = 0;
    int i_token = 0;

    while (input[position] != '\0') {
        char pos_char = input[position];

        if(pos_char == ' ') {
            position++;
            continue;
        }

        // Tokeniser les nombres dans l'input
        if(is_number(pos_char)) {
            int number = 0;
            while (is_number((input[position]))) {
                number = number * 10 + (input[position] - '0');
                position++;
            }
            tokens[i_token].type = NUMBER;
            tokens[i_token].value = number;
            i_token++;
            continue;
        }

        // Tokeniser les opérateurs dans l'input
        switch (pos_char) {
            case '+':
                tokens[i_token].type = PLUS;
                tokens[i_token].value = 0;
                break;
            case '-':
                tokens[i_token].type = MINUS;
                tokens[i_token].value = 0;
                break;
            case '*':
                tokens[i_token].type = MULT;
                tokens[i_token].value = 0;
                break;
            case '/':
                tokens[i_token].type = DIV;
                tokens[i_token].value = 0;
                break;
            case '(':
                tokens[i_token].type = LPAREN;
                tokens[i_token].value = 0;
                break;
            case ')':
                tokens[i_token].type = RPAREN;
                tokens[i_token].value = 0;
                break;
            default:
                printf("Entrée invalide: %c\n", pos_char);
                exit(1);
        }
        i_token++;
        position++;
    }

    for (int i = 0; i < i_token; i++) {
        printf("Token %d: Type = %s, Value = %d\n", i, token_string(tokens[i].type), tokens[i].value);
    }

    // Marquer la fin des tokens
    tokens[i_token].type = TOKEN_EOF;
    return tokens;
}