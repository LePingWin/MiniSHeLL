/*
�* File:��  stack.h
�* Author:  zentut.com
�* Purpose: linked stack header file
�*/
#ifndef _STACK_H_
#define _STACK_H_

#include "../include/typedef.h"

bool empty(Stack s);
/**
 * \fn Stack pop(Stack s,char* *data)
 * \brief Empile le premier élement
 *
 * \param Stack Pile
 */
Stack push(Stack s,char* data);
/**
 * \fn Stack pop(Stack s,char* *data)
 * \brief dépile le première élément
 *
 * \param Stack Pile
 */
Stack pop(Stack s,char* *data);
/**
 * \fn void init(Stack s)
 * \brief Initialise la pile
 *
 * \param Stack Pile
 */
void init(Stack s);
/**
 * \fn void display(Stack head)
 * \brief Affiche la pile
 *
 * \param Stack Pile
 */
void display(Stack head);
#endif // LINKEDSTACK_H_INCLUDED
