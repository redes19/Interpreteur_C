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
    TOKEN_EOF,  // Fin de l'input
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;


Token *lexer(const char *input);

#endif