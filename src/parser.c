//
// Created by Mathéo Pion on 06/10/2024.
//
#include "parser.h"
#include "stdio.h"
#include "stdlib.h"

/*
 * Fonction qui renvoie le token actuel à la position du parser.
 * Le parser contient une liste de tokens et un pointeur sur la position actuelle.
 */
Token current_token(Parser *parser) {
    return parser->tokens[parser->position];
}

/*
 * Fonction qui fait avancer le parser en augmentant la position.
 * Cela permet de passer au token suivant dans la liste.
 */
void advance(Parser *parser) {
    parser->position++;
}

/*
 * Fonction qui analyse un "facteur" dans une expression (ex: un nombre ou une parenthèse).
 * Elle retourne un nœud de l'AST correspondant au facteur analysé.
 */
ASTNode *parse_factor(Parser *parser) {
    Token token = current_token(parser);

    if(token.type == NUMBER){
    advance(parser);
    return create_ast_node(token.value);
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

/*
 * Fonction qui analyse un "terme", c'est-à-dire une multiplication ou division dans une expression.
 * Elle retourne un nœud de l'AST correspondant à cette partie de l'expression.
 */
ASTNode *parse_term(Parser *parser) {
    ASTNode *node = parse_factor(parser);

    while(current_token(parser).type == MULT || current_token(parser).type == DIV){
        Token token = current_token(parser);
        advance(parser);
        ASTNode *right = parse_factor(parser);
        node = create_ast_operator(token.type, node, right);

    }

    return node;
}

/*
 * Fonction qui analyse une "expression", c'est-à-dire une addition ou soustraction.
 * Elle retourne un nœud de l'AST représentant l'expression complète.
 */
ASTNode *parse_expression(Parser *parser) {
    ASTNode *node = parse_term(parser);

    while(current_token(parser).type == PLUS || current_token(parser).type == MINUS) {
        Token token = current_token(parser);
        advance(parser);
        ASTNode *right  = parse_term(parser);
        node = create_ast_operator(token.type, node, right);

    }

    return node;
}

/*
 * Fonction qui initialise un parser avec une liste de tokens.
 * Elle met la position du parser à 0 (début de la liste).
 */
Parser init_parser(Token *tokens) {
    Parser parser;
    parser.tokens = tokens;
    parser.position = 0;
    return parser;
}