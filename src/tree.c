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

void addNode(Tree t, char* val)
{
    if(isEmpty(t))
        t = createTree(val,NULL,NULL);
    else if(isEmpty(left(t)))
        t->left = createTree(val,NULL,NULL);
    else if(isEmpty(right(t)))
        t->right = createTree(val,NULL,NULL);
    else
        addNode(left(t),val);
}

void constructTree()
{
    
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

Tree left(Tree t)
{
    if(isEmpty(t))
        return NULL;
    else
        return t->left;
}

Tree right(Tree t)
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
    else if (isEmpty(left(t)) && isEmpty(right(t)))
        return true;
    else
        return false;
}