/**
 * \file builtin.h
 * \brief Fonctions du Shell
 * \author Loïc.B
 *
 * Reproduction des fonctions du Shell
 *
 */
#ifndef _BUILTIN_H_
#define _BUILTIN_H_

#include "typedef.h"

/**
 * \fn char* cdCmd(char* arg)
 * \brief Reproduit la commande "cd" 
 *
 * \param Chemin du répertoire cible
 * \return Chemin du répertoire cible
 */
void cdCmd(char* arg);
/**
 * \fn char* pwdCmd()
 * \brief Reproduit la commande "pwd" 
 *
 * \return Chemin du répertoire courant
 */
void pwdCmd(char* arg);
/**
 * \fn void exitCmd()
 * \brief Quitte le processus courant
 */
void exitCmd(char* arg);
/**
 * \fn char* echoCmd(char* arg)
 * \brief Reproduit la commande "echo" 
 *
 * \param Chaîne à afficher
 * \return Chaîne à afficher
 */
void echoCmd(char* arg);
/**
 * \fn char* execOutsideFunction(char* arg)
 * \brief Tente un exec de la chaîne en entrée 
 *
 * \param Chaîne à executer
 * \return Code Erreur
 */
void execOutsideFunction(char* arg);
#endif