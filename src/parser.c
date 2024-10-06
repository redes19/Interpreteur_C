//
// Created by Mathéo Pion on 06/10/2024.
//
#include "parser.h"
#include "stdio.h"
#include "stdlib.h"

Token current_token(Parser *parser) {
    return parser->tokens[parser->position];
}

void advance(Parser *parser) {
    parser->position++;
}

ASTNode *parse_factor(Parser *parser) {
   Token token = current_token(parser);

   if(token.type == NUMBER){
       advance(parser);
       return create_node(NUMBER, token.value);
   }

   if(token.type == LPAREN) {
       advance(parser);
       ASTNode *node = parse_expression(parser);
       if(current_token(parser).type != RPAREN) {
           printf("Erreur : parenthèse manquante \n");
           exit(1);
       }
       advance(parser);
       return node;
   }
   printf("Erreur : facteur non valide \n");
   exit(1);
}

ASTNode *parse_term(Parser *parser) {
    ASTNode *node = parse_factor(parser);

    while(current_token(parser).type == MULT || current_token(parser).type == DIV){
        Token token = current_token(parser);
        advance(parser);
        ASTNode *right = parse_factor(parser);
        node = create_operator_node(token.type, node, right);
    }

    return node;
}

ASTNode *parse_expression(Parser *parser) {
    ASTNode *node = parse_term(parser);

    while(current_token(parser).type == PLUS || current_token(parser).type == MINUS) {
        Token token = current_token(parser);
        advance(parser);
        ASTNode *right  = parse_term(parser);
        node = create_operator_node(token.type, node, right);
    }

    return node;
}

Parser init_parser(Token *tokens) {
    Parser parser;
    parser.tokens = tokens;
    parser.position = 0;
    return parser;
}