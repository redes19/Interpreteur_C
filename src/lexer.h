#ifndef LEXER_H
#define LEXER_H

typedef enum {
    NUMBER,
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD,
    POW,
    LPAREN,
    RPAREN,
    TOKEN_EOF,
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;


Token *lexer(const char *input);

#endif