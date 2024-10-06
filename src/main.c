#include <stdio.h>
#include "lexer.h"
#include <stdlib.h>
#include "parser.h"
#include "ast.h"

 int main()
{
     const char *input = "3 + 4 * 8";
     Token *tokens = lexer(input);

     Parser parser = init_parser(tokens);
     ASTNode *ast = parse_expression(&parser);

     int result = eval(ast);
     printf("Résultat : %d\n", result);

     free(tokens);
    return 0;
}