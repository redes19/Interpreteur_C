#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "AST.h"

// Fonction pour lire les instructions d'un fichier
char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);


    char *content = malloc(file_size + 1);
    if (!content) {
        printf("Erreur : Allocation de memoire echouee\n");
        exit(1);
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0';


    fclose(file);
    return content;
}

Token *tokens;
ASTNode *ast;
void interpreteur(const char *input) {
    tokens = lexer(input);
    ast = parser(tokens);

    print_ast(ast, 0);

    if (tokens[0].type == PRINT) {
    } else {
        int result = eval_ast(ast);
        printf("\nResultat : %d\n", result);
        printf("-----------------------------\n");
    }

}

// Fonction REPL pour interpréter les expressions en direct
void repl() {
    char input[1024];
    printf("Mode Terminal - Entrez une expression (ou 'exit' pour quitter) :\n");
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Retirer le saut de ligne
        input[strcspn(input, "\n")] = '\0';

        // Commande pour quitter le REPL
        if (strcmp(input, "exit") == 0) {
            printf("Quitter...\n");
            break;
        }

        // Analyser et évaluer l'expression
        tokens = lexer(input);
        ast = parser(tokens);

        // Évaluer l'AST et afficher le résultat
        int result = eval_ast(ast);
        printf("%d\n", result);

        // Libérer les ressources
        free(tokens);
        free_ast(ast);
    }
}

// Point d'entrée du programme
int main(int argc, char *argv[]) {
    const char *input = NULL;
    // Vérifier si un fichier a été fourni
    if (argc < 2) {
        // Si aucun fichier n'est fourni, lancer le REPL
        printf("Aucun fichier fourni. Lancement du mode REPL...\n");
        repl();
    } else {
        // Lire les instructions à partir du fichier fourni
        input = read_file(argv[1]);
    }

    interpreteur(input);
    interpreteur("x = 5 + 5");
    interpreteur("print(x)");
    interpreteur("l = x + 5");
    interpreteur("print(l)");
    interpreteur("y = 9");
    interpreteur("print(y)");
    interpreteur("z = x + y");
    interpreteur("print(z)");

    if (argc >= 2) free((void *)input);

    return 0;
}
