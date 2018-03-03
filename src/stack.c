// C program for linked list implementation of stack
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/typedef.h"
#include "../include/stack.h"
 
Stack newNode(char* data)
{
    Stack stackNode =
              (Stack) malloc(sizeof(struct stackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}
 
bool empty(Stack root)
{
    return root ? true : false;
}
 
void push(Stack* root, char* data)
{
    Stack stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}
 
char* pop(Stack* root)
{
    if (empty(*root))
        return NULL;
    Stack temp = *root;
    *root = (*root)->next;
    char* popped = temp->data;
    free(temp);
 
    return popped;
}
 
char* peek(Stack root)
{
    if (empty(root))
        return NULL;
    return root->data;
}