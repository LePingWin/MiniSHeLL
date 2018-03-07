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
    /*char* test1 = "cd";
    char* test2 = "grep";
    char* test3 = "ls";
    char* test4 = "grep";

    Tree a = createTree(test1,NULL,NULL);

    Tree b = createTree(test2, NULL,NULL);
    Tree d = createTree(test3,b,NULL);
    Tree c = createTree(test4,a,d);
    printf("%s\n",c->left->value);
    printf("%d\n",isEmpty(c));
    //parcoursPrefixe(a);
    save_dot(c,"graph.dot");
*/


    /*
    char* test = "ls -a | grep git && echo hallo || echo test";
    printf("Before build tree I\n");


    Tree I = createTree(test, NULL, NULL);
    printf("Before call\n");
    printf("%d",isEmpty(I));
    */

    /*const char *ls[] = { "ls", "-l", 0 };
    const char *awk[] = { "awk", "{print $1}", 0 };
    const char *sort[] = { "sort", 0 };
    const char *uniq[] = { "uniq", 0 };

    struct command cmd [] = { {ls}, {awk}, {sort}, {uniq} };

    return fork_pipes (4, cmd);*/
}



