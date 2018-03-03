/*
�* File:��  StackTree.c
�* Author:  zentut.com
�* Purpose: linked StackTree implementation
�*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/stackTree.h"

/*
    initStackTree the StackTree
*/
void initStackTree(StackTree head)
{
    head = NULL;
}

/*
    pushStackTree an element into StackTree
*/
StackTree pushStackTree(StackTree head,Tree data)
{
    StackTree tmp = (StackTree)malloc(sizeof(StackTree));
    if(tmp == NULL)
    {
        exit(0);
    }
    tmp->data = data;
    tmp->next = head;
    head = tmp;
    return head;
}
/*
    popStackTree an element from the StackTree
*/
StackTree popStackTree(StackTree head,Tree *element)
{
    StackTree tmp = head;
    *element = head->data;
    head = (StackTree)head->next;
    free(tmp);
    return head;
}
/*
    returns 1 if the StackTree is emptyStackTree, otherwise returns 0
*/
bool emptyStackTree(StackTree head)
{
    return head == NULL ? true : false;
}

/*
    displayStackTree the StackTree content
*/
void displayStackTree(StackTree head)
{
    StackTree current;
    current = head;
    if(current!= NULL)
    {
        printf("StackTree: ");
        do
        {
            printf("%s ",current->data->value);
            current = (StackTree)current->next;
        }
        while (current!= NULL);
        printf("\n");
    }
    else
    {
        printf("The StackTree is emptyStackTree\n");
    }

}
