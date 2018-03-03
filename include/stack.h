/*
�* File:��  stack.h
�* Author:  zentut.com
�* Purpose: linked stack header file
�*/
#ifndef _STACK_H_
#define _STACK_H_

#include "../include/typedef.h"

Stack newNode(char* data);

bool empty(Stack root);
 
void push(Stack* root, char* data);

char* pop(Stack* root);

char* peek(Stack root);

#endif // LINKEDSTACK_H_INCLUDED
