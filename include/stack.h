/**
 * \file stack.h
 * \brief Pile contenant des strings (et on parle bien des chaînes de caractères ;))
 * \author Loïc B.
 */
/*
�* File:��  stack.h
�* Author:  zentut.com
�* Purpose: linked stack header file
�*/

#ifndef _STACK_H_
#define _STACK_H_

#include "../include/typedef.h"


/**
 * \fn Stack newNode(char* data)
 * \brief Initialise une pile
 * 
 * \param char* donnée à stocker
 * \return Stack
 */ 
Stack newNode(char* data);
/**
 * \fn bool empty(Stack root)
 * \brief Si pile vide renvoi 0
 * 
 * \param Stack 
 * \return bool
 */ 
bool empty(Stack root);
/**
 * \fn void push(Stack* root, char* data)
 * \brief Ajoute un élément à la pile passée en paramètre
 * 
 * \param Stack* la pile et char* la donnée
 */ 
void push(Stack* root, char* data);
/**
 * \fn char* pop(Stack* root)
 * \brief Enlève l'élement au sommet de la pile et renvoi son contenu
 * 
 * \param Stack 
 * \return char* data
 */ 
char* pop(Stack* root);
/**
 * \fn char* peek(Stack root)
 * \brief Renvoi la donnée de l'élement au sommet de la pile
 *  
 * \param Stack 
 * \return char* data
 */ 
char* peek(Stack root);

#endif // LINKEDSTACK_H_INCLUDED
