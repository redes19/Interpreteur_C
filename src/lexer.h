#ifndef LEXER_H
#define LEXER_H

typedef enum {
    NUMBER, // 0-9
    IDENTIFIER, // a-z, A-Z
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
    int value;
    char *identifier;
} Token;


Token *lexer(const char *input);

#endif