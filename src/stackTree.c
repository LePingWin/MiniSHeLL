// C program for linked list implementation of stack
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
#include "../include/typedef.h"
#include "../include/stackTree.h"

StackTree newNodeStackTree(Tree data)
{
    StackTree stackNode =
              (StackTree) malloc(sizeof(struct stackTree));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}
 
bool isEmptyStackTree(StackTree root)
{
    return root ? true : false;
}
 
void pushStackTree(StackTree* root, Tree data)
{
    StackTree stackNode = newNodeStackTree(data);
    stackNode->next = *root;
    *root = stackNode;
}
 
Tree popStackTree(StackTree* root)
{
    if (isEmptyStackTree(*root))
        return NULL;
    StackTree temp = *root;
    *root = (*root)->next;
    Tree popped = temp->data;
    free(temp);
 
    return popped;
}
 
Tree peekStackTree(StackTree root)
{
    if (isEmptyStackTree(root))
        return NULL;
    return root->data;
}