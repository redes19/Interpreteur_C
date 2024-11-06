#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
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

// Fonction REPL pour interagir avec l'utilisateur
void repl() {
    char input[1024];

    printf("Entrez une expression (ou 'exit' pour quitter) :\n");

    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Supprimer le retour à la ligne final de l'entrée
        input[strcspn(input, "\n")] = '\0';

        // Si l'utilisateur tape "exit", on quitte le REPL
        if (strcmp(input, "exit") == 0) {
            printf("Quitter...\n");
            break;
        }

        // Tokeniser l'expression
        Token *tokens = lexer(input);

        // Parser l'expression et obtenir l'AST
        Parser parser = init_parser(tokens);
        ASTNode *ast = parse_expression(&parser);

        // Évaluer l'AST
        int result = eval_ast(ast);
        printf("Résultat : %d\n", result);

        // Libérer les ressources
        free(tokens);
        free_ast(ast);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Démarrer en mode REPL si aucun fichier n'est fourni
        repl();
    } else {
        // Lire l'expression à partir du fichier
        const char *input = read_file(argv[1]);

        // Tokeniser l'expression
        Token *tokens = lexer(input);

        // Parser l'expression et obtenir l'AST
        Parser parser = init_parser(tokens);
        ASTNode *ast = parse_expression(&parser);

        // Évaluer l'AST
        int result = eval_ast(ast);
        printf("Résultat : %d\n", result);

        // Libérer les ressources
        free(tokens);
        free_ast(ast);
        free((void*)input);
    }

    return 0;
}
