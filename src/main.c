#include <stdio.h>
#include "lexer.h"
#include <stdlib.h>

 int main()
{
     const char *input = "3 + 4 * 8";
     Token *tokens = lexer(input);


     free(tokens);
    return 0;
}