#include <stdio.h>
#include <stdlib.h>
#include "../include/builtin.h"
#include "../include/shell.h"


int main(int argc, char* argv[])
{
    shellReader();

    /*char* test = "ls -a | grep git && echo hallo || echo test";
    printf("Before build tree I\n");


    Tree I = createTree(test, NULL, NULL);
    printf("Before call\n");
    printf("%d",isEmpty(I));*/

    /*const char *ls[] = { "ls", "-l", 0 };
    const char *awk[] = { "awk", "{print $1}", 0 };
    const char *sort[] = { "sort", 0 };
    const char *uniq[] = { "uniq", 0 };

    struct command cmd [] = { {ls}, {awk}, {sort}, {uniq} };

    return fork_pipes (4, cmd);*/

    /*const char *ls[] = { "ls", "-a", 0 };
    const char *awk[] = { "grep", "git", 0 };
   

    struct command cmd [] = { {ls}, {awk} };

    return fork_pipes (2, cmd);*/
    return EXIT_SUCCESS;
}