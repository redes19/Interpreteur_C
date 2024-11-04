/*#include <stdio.h>
#include <stdlib.h>
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


int main(int argc, char *argv[]) {
    const char *input;

    if (argc < 2) {
        printf("Aucun fichier fourni. Utilisation de l'expression par defaut.\n");
        input = "3 + 4 * 2 / (5 - 2)";
    } else {
        // Lire les instructions à partir du fichier au lieu de l'écrire en dur
        input = read_file(argv[1]);
    }

    Token *tokens = lexer(input);
    ASTNode *ast = parser_ast(tokens);

    int result = eval_ast(ast);
    printf("Resultat : %d\n", result);

    free_ast(ast);
    if (argc >= 2) free((void*)input);

    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "AST.h"

 int main()
 {
     const char *input = "3 + 4 * 2 / (5 - 2)";
     //const char *input = "xax = 3 + 3 * (2 + 1)";
     //const char *input = "a = (10 + 2) * 3";

     Token *tokens = lexer(input);

     ASTNode *ast = parser_ast(tokens);
     if (ast == NULL) {
         printf("Erreur: AST est NULL\n");
         exit(1);
     }
     printf("\nretour node\n");
     print_ast(ast);


     const int result = eval_ast(ast);
     printf("\nResult : %d\n", result);

     free_ast(ast);
     free(tokens);
     return 0;
 }