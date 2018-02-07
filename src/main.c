#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"

int main(int argc, char* argv[])
{
    
 
    shellReader();
    cdCmd(argv[1]);

    
    return EXIT_SUCCESS;
}