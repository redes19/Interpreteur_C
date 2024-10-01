#ifndef INTERPRETEUR_H
#define INTERPRETEUR_H

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
} tokenType;

typedef struct {
    tokenType type;
    int value;
} token;


void interpreteur();

#endif