#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "AST.h"

 int main()
{
     const char *input = "3 + 4 * 8";
     Token *tokens = lexer(input);

     ASTNode *ast = parser_ast(tokens);
     print_ast(ast);

     free(tokens);
    return 0;
}