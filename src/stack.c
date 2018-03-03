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
Stack push(Stack head,char* data)
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
Stack pop(Stack head,char* *element)
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
bool empty(Stack head)
{
    return head == NULL ? true : false;
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
            printf("%s ",current->data);
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
