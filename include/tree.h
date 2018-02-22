/**
 * \file builtin.h
 * \brief Gestion du Shell
 * \author Jean.S
 *
 *  Gestion du Shell et de l'IHM
 *
 */
#ifndef _TREE_H_ /* L'ecriture ici presente n'est pas universelle */
#define _TREE_H_ /* Edit suite aux corrections des posts suivants -> */

#include "typedef.h"

/**
 * \fn Tree createTree(char* val, Tree ls, Tree rs)
 * \brief Cree un arbre
 *
 * \param char* valeur du noeud, Tree ls arbre de gauche,Tree ls arbre de droite
 * \return Tree : retourne l'arbre cree
 */
Tree createTree(char* val, Tree ls, Tree rs);

/**
 * \fn void displayTree(Tree t)
 * \brief Affiche l'arbre sur la sortie standard
 *
 * \param Tree arbre en entrée
 */
void displayTree(Tree t);

/**
 * \fn bool isEmpty(Tree t)
 * \brief Test si l'arbre est vide
 *
 * \param Tree arbre en entree
 * \return bool : resultat vrai si vide, faux sinon
 */
bool isEmpty(Tree t);

/**
 * \fn Tree Left(Tree t)
 * \brief Renvoie l'arbre a gauche de celui passe en parametre
 *
 * \param Tree arbre en entrée
 * \return Tree : resultat Tree si frere gauche non vide, NULL sinon
 */
Tree Left(Tree t);

/**
 * \fn Tree Right(Tree t)
 * \brief Renvoie l'arbre a droite de celui passe en parametre
 *
 * \param Tree arbre en entrée
 * \return Tree : resultat Tree si frere de droite non vide, NULL sinon
 */
Tree Right(Tree t);

/**
 * \fn Tree Right(Tree t)
 * \brief Renvoie si l
 *
 * \param Tree arbre en entrée
 * \return bool : retourne vrai si l'arbre est une feuille, faux sinon
 */
bool isLeaf(Tree t);

#endif