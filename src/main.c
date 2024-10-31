#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "AST.h"

 int main()
{
     //const char *input = "3 + 4 * 2 / (5 - 2)";
     const char *input = "xax = 3 + 3";
     Token *tokens = lexer(input);

     ASTNode *ast = parser_ast(tokens);
     if (ast == NULL) {
         printf("Erreur: AST est NULL\n");
         exit(1);
     }
     printf("retour node\n");
     print_ast(ast);


     const int result = eval_ast(ast);
     printf("\nResult : %d\n", result);

     free_ast(ast);
     free(tokens);
    return 0;
}