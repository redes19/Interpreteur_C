#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "repl.h"

#define MAX_LINE_LENGTH 256

void repl() {
    char input[MAX_LINE_LENGTH];

    printf("Bienvenue dans l'interpréteur interactif ('exit' pour quitter)\n");

    // Boucle REPL
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // Si erreur de lecture, quitter
        }

        // Supprimer le saut de ligne
        input[strcspn(input, "\n")] = 0;

        // Si l'utilisateur tape 'exit', on sort de la boucle
        if (strcmp(input, "exit") == 0) {
            printf("Au revoir !\n");
            break;
        }

        // Analyser et évaluer l'entrée utilisateur
        Token *tokens = lexer(input);
        Parser parser = init_parser(tokens);
        ASTNode *ast = parse_expression(&parser);

        if (ast != NULL) {
            int result = eval(ast);
            printf("Résultat : %d\n", result);
        } else {
            printf("Erreur de parsing ou d'évaluation.\n");
        }

        // Libérer la mémoire allouée pour les tokens
        free(tokens);
    }
}
