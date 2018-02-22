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


#define MAX_COMMAND_LENGTH 100
#define MAX_NUMBER_OF_PARAMS 10
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
 * \struct tree
 * \brief Structure d'arbre binaire 
 *
 */
typedef struct node *Tree;
struct node
{
    char* value;
    Tree left;
    Tree right;
};

#endif
