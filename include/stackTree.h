/*
�* File:��  StackTree.h
�* Author:  zentut.com
�* Purpose: linked StackTree header file
�*/
#ifndef _STACK_TREE_H_
#define _STACK_TREE_H_

#include "../include/typedef.h"

bool emptyStackTree(StackTree s);
/**
 * \fn StackTree pop(StackTree s,char* *data)
 * \brief Empile le premier élement
 *
 * \param StackTree Pile
 */
StackTree pushStackTree(StackTree s,Tree data);
/**
 * \fn StackTree pop(StackTree s,char* *data)
 * \brief dépile le première élément
 *
 * \param StackTree Pile
 */
StackTree popStackTree(StackTree s,Tree *data);
/**
 * \fn void init(StackTree s)
 * \brief Initialise la pile
 *
 * \param StackTree Pile
 */
void initStackTree(StackTree s);
/**
 * \fn void display(StackTree head)
 * \brief Affiche la pile
 *
 * \param StackTree Pile
 */
void displayStackTree(StackTree head);
#endif // LINKEDStackTree_H_INCLUDED