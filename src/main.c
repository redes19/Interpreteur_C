#include <stdio.h>
#include "lexer.h"
#include <stdlib.h>
#include "parser.h"
#include "ast.h"

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
        printf("Erreur : Allocation de mémoire échouée\n");
        exit(1);
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0';

    fclose(file);
    return content;
}

 int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <fichier>\n", argv[0]);
        return 1;
    }

    // Lire les instructions à partir du fichier au lieu de l'écrire en dur
    const char *input = read_file(argv[1]);

    Token *tokens = lexer(input);

    Parser parser = init_parser(tokens);
    ASTNode *ast = parse_expression(&parser);

    int result = eval(ast);
    printf("Résultat : %d\n", result);

    free(tokens);
    free((void*)input);
    return 0;
}