//
// Created by Mathéo Pion on 06/10/2024.
//

#ifndef INTERPRETEUR_C_PARSER_H
#define INTERPRETEUR_C_PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct {
    Token *tokens;
    int position;
} Parser;

Parser init_parser(Token *tokens);
ASTNode *parse_expression(Parser *parser);

#endif //INTERPRETEUR_C_PARSER_H
