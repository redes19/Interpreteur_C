#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "AST.h"

 int main()
{
     //const char *input = "3 + 4 * 2 / (5 - 2)";
     const char *input = "xax = 10";
     Token *tokens = lexer(input);

     /*ASTNode *ast = parser_ast(tokens);
     printf("retour node\n");
     print_ast(ast);


     const int result = eval_ast(ast);
     printf("\nResult : %d\n", result);*/

     free(tokens);
    return 0;
}