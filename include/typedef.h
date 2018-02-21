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
// Colors
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define BOLD  "\x1B[1m"

/**
 * \struct node
 * \brief Objet Arbre binaire
 *
 */
/*typedef struct node
{
    char* value;
    struct node* root;
    struct node* fd;
    struct node* fg;
}node;*/

/**
 * \struct tree
 * \brief Structure d'arbre binaire 
 *
 */
typedef struct tree Tree;
struct tree
{
    char value;
    Tree *brother;
    Tree *child;
};

#endif