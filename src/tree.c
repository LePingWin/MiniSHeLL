#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/tree.h"

Tree createTree(char* val, Tree ls, Tree rs)
{
    Tree res;
    printf("%s\n",val);
    res = malloc(sizeof(*res));

    if(res == NULL)
    {
        perror("Impossible d'allouer le noeud");
        return NULL;
    }

    res->value = val;
    res->left = ls;
    res->right = rs;
    printf("%s\n",res->value);
    return res;
}

void displayTree(Tree t)
{




}

int sizeTree(Tree t)
{
    



}

bool isEmpty(Tree t)
{
    if (t == NULL)
        return true;
    else
        return false;

}

Tree Left(Tree t)
{
    if(isEmpty(t))
        return NULL;
    else
        return t->left;
}

Tree Right(Tree t)
{
    if(isEmpty(t))
        return NULL;
    else
        return t->right;
}

bool isLeaf(Tree t)
{
    if(isEmpty(t))
        return false;
    else if (isEmpty(Left(t)) && isEmpty(Right(t)))
        return true;
    else
        return false;
}