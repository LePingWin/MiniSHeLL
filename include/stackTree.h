/**
 * \file stackTree.h
 * \brief Pile contenant des arbres
 * \author Loïc.B et Jean.S
 */
/*
�* File:  stackTree.h
�* Author:  zentut.com
�* Purpose: linked StackTree header file
�*/

#ifndef _STACK_TREE_H_
#define _STACK_TREE_H_

#include "../include/typedef.h"

/**
 * \fn StackTree newNodeStackTree(Tree data)
 * \brief Initialise une pile
 * 
 * \param Tree* donnée à stocker
 * \return StackTree
 */ 
StackTree newNodeStackTree(Tree data);
/**
 * \fn bool isEmptyStackTree(StackTree root)
 * \brief Si pile vide renvoi 0
 * 
 * \param StackTree 
 * \return bool
 */ 
bool isEmptyStackTree(StackTree root);
 /**
 * \fn pushStackTree(StackTree* root, Tree data)
 * \brief Ajoute un élément à la pile passée en paramètre
 * 
 * \param StackTree* la pile et Tree la donnée
 */ 
void pushStackTree(StackTree* root, Tree data);
/**
 * \fn Tree popStackTree(StackTree* root)
 * \brief Enlève l'élement au sommet de la pile et renvoi son contenu
 * 
 * \param StackTree* 
 * \return Tree data
 */ 
Tree popStackTree(StackTree* root);
/**
 * \fn Tree peekStackTree(StackTree root)
 * \brief Renvoi la donnée de l'élement au sommet de la pile
 *  
 * \param StackTree 
 * \return Tree data
 */ 
Tree peekStackTree(StackTree root);
#endif // LINKEDStackTree_H_INCLUDED