#include <stdio.h>
#include <stdlib.h>

int main(int argv, char** argc)
{
    argv--;
    argc++;

    //Run the gcc preprocessor on file into stream
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "gcc -E -xc %s", *argc);
    FILE* pp = popen(cmd, "r");
    if(!pp)
    {
	perror("popen");
	return 1;
    }

    char buffer[256];
    while(fgets(buffer, sizeof(buffer), pp) != NULL)
    {
	printf("%s", buffer);
    }

    //Run lexer
    
    //Run Parser/Emitter
    
    //Run gcc on file

    pclose(pp);

    return 0;
}
