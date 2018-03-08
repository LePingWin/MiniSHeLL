#include <stdio.h>
#include <stdlib.h>
#include "../include/builtin.h"
#include "../include/shell.h"
#include "../include/parser.h"
#include <string.h>

#define USAGE_SYNTAX "[OPTIONS] -c \"COMMAND\""
#define USAGE_PARAMS "OPTIONS:\n\
  -i, --command  COMMAND  : command string between double quotes\n\
"

/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name)
{
  dprintf(1, "USAGE: %s %s\n\n%s\n", bin_name, USAGE_SYNTAX, USAGE_PARAMS);
}




int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        if(strcmp(argv[1],"-c") == true){
            argv += 2;
            ProcessCommands(argv,argc-2);
        }
        else
        {
            print_usage(argv[0]);
        }
    }
    else
    {
        shellReader();
    }
    return 0;
}



