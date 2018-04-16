/**
 * \file builtin.h
 * \brief Fonctions du Shell
 * \author Loïc.B et Jean.S
 *
 * Reproduction des fonctions du Shell
 *
 */
#ifndef _BUILTIN_H_
#define _BUILTIN_H_

#include "typedef.h"

/**
 * \fn char* cdCmd(char** arg)
 * \brief Reproduit la commande "cd" 
 *
 * \param Chemin du répertoire cible
 * \return Chemin du répertoire cible
 */
void cdCmd(char** arg);
/**
 * \fn void pwdCmd()
 * \brief Reproduit la commande "pwd" 
 *
 * \return Chemin du répertoire courant
 */
void pwdCmd();
/**
 * \fn void echoCmd(char** arg)
 * \brief Reproduit la commande "echo" 
 *
 * \param Chaîne à afficher
 * \return Chaîne à afficher
 */
void echoCmd(char** arg);
#endif