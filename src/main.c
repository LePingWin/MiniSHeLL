#include <stdio.h>
#include <stdlib.h>
#include "../include/builtin.h"
#include "../include/shell.h"
#include "../include/tree.h"


int main(int argc, char* argv[])
{
    //shellReader();

    char* test = "teststet -dsfds -dfs | testes | fdsfds";
    printf("Before build tree I\n");


    Tree I = createTree(test, NULL, NULL);
    /*Tree H = {'H', &I, NULL};
    Tree G = {'G', &H, NULL};
    Tree F = {'F', NULL, &G};
    Tree E = {'E', NULL, NULL};
    Tree D = {'D', &E, NULL};
    Tree C = {'C', NULL, &F};
    Tree B = {'B', &C, &D};
    Tree A = {'A', NULL, &B};*/
    printf("Before call\n");
    printf("%d",isEmpty(I));

    return EXIT_SUCCESS;
}