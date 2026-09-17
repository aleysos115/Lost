#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "lexer.c"

int main(int argc, char** argv)
{
    argc--;
    argv++;

    //Run the gcc preprocessor on file into stream
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "gcc -E -xc %s", *argv);
    FILE* pp = popen(cmd, "r");
    if(!pp)
    {
	perror("popen");
	return 1;
    }

    token_list list;

    char buffer[256];
    while(fgets(buffer, sizeof(buffer), pp) != NULL)
    {
	//printf("%s", buffer);
	lex(buffer, &list);
    }

    //Run lexer
    
    //Run Parser/Emitter
    
    //Run gcc on file

    pclose(pp);

    return 0;
}
