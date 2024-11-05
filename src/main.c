#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "AST.h"
#include <string.h>

#define MAX_INPUT_LENGTH 1024

int main() {
    char input[MAX_INPUT_LENGTH];

    printf("Bienvenue dans le super interpréteur ! Tapez 'exit' pour quitter.\n");

    while (1) {
        // Affiche un prompt
        printf(">>> ");

        // Lire l'entrée de l'utilisateur
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Supprimer le caractère de nouvelle ligne à la fin de l'entrée
        input[strcspn(input, "\n")] = '\0';

        // Vérifier si l'utilisateur veut quitter
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Tokeniser l'entrée
        Token *tokens = lexer(input);

        // Parser les tokens en AST
        ASTNode *ast = parser_ast(tokens);

        if (ast == NULL) {
            printf("Erreur : AST est NULL\n");
            free(tokens);
            continue;
        }

        // Afficher l'AST
        printf("Arbre syntaxique : ");
        print_ast(ast);
        printf("\n");

        // Évaluer l'AST et afficher le résultat
        int result = eval_ast(ast);
        printf("Résultat : %d\n", result);

        // Libérer la mémoire utilisée
        free_ast(ast);
        free(tokens);
    }

    printf("Merci d'avoir utilisé le REPL de l'interpréteur C.\n");

    return 0;
}
