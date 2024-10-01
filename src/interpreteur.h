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
    TOEKN_EOF,
} tokenType;

typedef struct {
    tokenType type;
    int value;
} token;


void interpreteur();

#endif