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

    // Se déplacer à la fin du fichier pour en obtenir la taille
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allouer de la mémoire pour le contenu du fichier
    char *content = malloc(file_size + 1);
    if (!content) {
        printf("Erreur : Allocation de mémoire échouée\n");
        exit(1);
    }

    // Lire le contenu du fichier
    fread(content, 1, file_size, file);
    content[file_size] = '\0';

    fclose(file);
    return content;
}

// Fonction REPL pour interpréter les expressions en direct
void repl() {
    char input[1024];
    printf("Mode Interpréteur - Entrez une expression (ou 'exit' pour quitter) :\n");
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
        Token *tokens = lexer(input);
        ASTNode *ast = parser_ast(tokens);

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
    // Vérifier si un fichier a été fourni
    if (argc < 2) {
        // Si aucun fichier n'est fourni, lancer le REPL
        printf("Aucun fichier fourni. Lancement du mode REPL...\n");
        repl();
    } else {
        // Lire les instructions à partir du fichier fourni
        const char *filename = argv[1];
        char *input = read_file(filename);

        // Analyser et évaluer le contenu du fichier
        Token *tokens = lexer(input);
        ASTNode *ast = parser_ast(tokens);

        // Évaluer l'AST et afficher le résultat
        int result = eval_ast(ast);
        printf("Résultat : %d\n", result);

        // Libérer les ressources
        free(tokens);
        free_ast(ast);
        free(input);
    }

    return 0;
}
