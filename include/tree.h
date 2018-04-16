/**
 * \file tree.h
 * \brief Gestion du Shell
 * \author Loïc.B et Jean.S
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
 * \fn void addNode(Tree t, char* val)
 * \brief Ajout d'un noeud a un arbre
 *
 * \param Tree t arbre source, char* val valeur du noeud
 */
void addNode(Tree t, char* val);

/**
 * \fn char* root(Tree t)
 * \brief Retourne la valeur de l'arbre
 *
 * \param Tree t arbre source
 * \return char* la valeur de la racine de l'arbre
 */
char* root(Tree t);

/**
 * \fn void writeTree(Tree t, File* fp)
 * \brief Ecrit l'arbre dans un fichier. Il sera interprete pour generer une visualisation de l'arbre
 *
 * \param Tree arbre en entree, File* fichier dans lequel sera ecrit l'arbre
 */
void writeTree(Tree t, FILE* fp);

/**
 * \fn void save_dot(Tree t, char* filename)
 * \brief dessine la representation de l'arbre.
 *
 * \param Tree arbre en entree, char* nom du fichier dans lequel sauvegarder la representation de l'arbre
 */
void save_dot(Tree t,char* filename);

/**
 * \fn void display(Tree t);
 * \brief affiche la representation de l'arbre.
 *
 */
void display(Tree t);

/**
 * \fn int sizeTree(Tree t)
 * \brief Calcul la taille de l'arbre
 *
 * \param Tree arbre en entree
 * \return int : retourne la taille de l'arbre, nombre de noeud
 */
int sizeTree(Tree t);

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
Tree left(Tree t);

/**
 * \fn Tree Right(Tree t)
 * \brief Renvoie l'arbre a droite de celui passe en parametre
 *
 * \param Tree arbre en entrée
 * \return Tree : resultat Tree si frere de droite non vide, NULL sinon
 */
Tree right(Tree t);

/**
 * \fn Tree Right(Tree t)
 * \brief Renvoie si l
 *
 * \param Tree arbre en entrée
 * \return bool : retourne vrai si l'arbre est une feuille, faux sinon
 */
bool isLeaf(Tree t);

/**
 * \fn parcoursPrefixe(Tree a)
 * \brief Parcours l'arbre e manière préfixé et affiche l'arbre
 *
 * \param Tree arbre en entrée
 */
void parcoursPrefixe(Tree a);

#endif