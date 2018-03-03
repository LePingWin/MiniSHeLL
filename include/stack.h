/*
�* File:��  stack.h
�* Author:  zentut.com
�* Purpose: linked stack header file
�*/
#ifndef _STACK_H_
#define _STACK_H_

#include "../include/typedef.h"

int empty(Stack s);
Stack push(Stack s,int data);
Stack pop(Stack s,int *data);
void init(Stack s);
void display(Stack head);
#endif // LINKEDSTACK_H_INCLUDED
