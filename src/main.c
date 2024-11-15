#include <stdio.h>
#include <stdlib.h>
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

void interpreteur(const char *input) {
    tokens = lexer(input);
    ast = parser(tokens);

    /*printf("\nretour node\n");
    print_ast(ast);*/
    //printf("\nretour node\n");
    print_ast(ast, 0);

    if (tokens[0].type == PRINT) {
    } else {
        int result = eval_ast(ast);
        //printf("\nResultat : %d\n\n", result);
    }

}



    interpreteur("x = 5 + 5");
    interpreteur("l = x + 5");
    interpreteur("y = 9");
    interpreteur("z = x + y");

}