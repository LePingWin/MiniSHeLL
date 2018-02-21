#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/tree.h"




void testTree(void)
{
    Tree I = {'I', NULL, NULL};
    Tree H = {'H', &I, NULL};
    Tree G = {'G', &H, NULL};
    Tree F = {'F', NULL, &G};
    Tree E = {'E', NULL, NULL};
    Tree D = {'D', &E, NULL};
    Tree C = {'C', NULL, &F};
    Tree B = {'B', &C, &D};
    Tree A = {'A', NULL, &B};
    //return 0;
}

void displayTree(Tree t)
{




}

int sizeTree(Tree t)
{
    



}