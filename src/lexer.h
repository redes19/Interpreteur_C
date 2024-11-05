#ifndef LEXER_H
#define LEXER_H

typedef enum {
    NUMBER = 0, // 0-9
    IDENTIFIER = 1, // a-z, A-Z
    PLUS,   // +
    MINUS,  // -
    MULT,   // *
    DIV,    // /
    MOD,    // %
    LPAREN, // (
    RPAREN, // )
    ASSIGN, // =
    PRINT,  // print
    TOKEN_EOF,  // Fin de l'input
} TokenType;

typedef struct {
    TokenType type;
    union {
        int value;
        char *identifier;
        char *command;
    };
} Token;


Token *lexer(const char *input);

#endif