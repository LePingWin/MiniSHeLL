/*
�* File:��  stack.c
�* Author:  zentut.com
�* Purpose: linked stack implementation
�*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"

/*
    init the stack
*/
void init(Stack head)
{
    head = NULL;
}

/*
    push an element into stack
*/
Stack push(Stack head,int data)
{
    Stack tmp = (Stack)malloc(sizeof(struct stackNode));
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
    pop an element from the stack
*/
Stack pop(Stack head,int *element)
{
    Stack tmp = head;
    *element = head->data;
    head = head->next;
    free(tmp);
    return head;
}
/*
    returns 1 if the stack is empty, otherwise returns 0
*/
int empty(Stack head)
{
    return head == NULL ? 1 : 0;
}

/*
    display the stack content
*/
void display(Stack head)
{
    Stack current;
    current = head;
    if(current!= NULL)
    {
        printf("Stack: ");
        do
        {
            printf("%d ",current->data);
            current = current->next;
        }
        while (current!= NULL);
        printf("\n");
    }
    else
    {
        printf("The Stack is empty\n");
    }

}
