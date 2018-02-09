/**
 * \file typedef.h
 * \brief Définition des types
 * \author Loïc.B
 *
 *  Définitions des types
 *
 */
#ifndef TYPEDEF_H
#define TYPEDEF_H

/**
 * \enum bool
 * \brief Booléen
 *
 */
typedef enum { true,false } bool;

#define STDOUT 1
#define STDERR 2

/**
 * \struct node
 * \brief Objet Arbre binaire
 *
 */
typedef struct node
{
    char* value;
    struct node* root;
    struct node* fd;
    struct node* fg;
}node;


#endif