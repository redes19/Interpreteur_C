#include <stdlib.h>
#include "lexer.h"
#include "AST.h"

Token *tokens;
ASTNode *ast;

void interpreteur(const char *input) {
    tokens = lexer(input);
    ast = parser(tokens);

    /*printf("\nretour node\n");
    print_ast(ast);*/

    if (tokens[0].type == PRINT) {
    } else {
        int result = eval_ast(ast);
        //printf("\nResultat : %d\n\n", result);
    }

}

void main()
{
    interpreteur("x = 5 + 5");
    interpreteur("print(x)");
    interpreteur("l = x + 5");
    interpreteur("print(l)");
    interpreteur("y = 9");
    interpreteur("print(y");
    interpreteur("z = x + y");
    interpreteur("print(z)");


    free_ast(ast);
    free(tokens);
}