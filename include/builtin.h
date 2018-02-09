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

/**
 * \fn char* cdCmd(char* arg)
 * \brief Reproduit la commande "cd" 
 *
 * \param Chemin du répertoire cible
 * \return Chemin du répertoire cible
 */
char* cdCmd(char* arg);
/**
 * \fn char* pwdCmd()
 * \brief Reproduit la commande "pwd" 
 *
 * \return Chemin du répertoire courant
 */
char* pwdCmd();
/**
 * \fn void exitCmd()
 * \brief Quitte le processus courant
 */
void exitCmd();
/**
 * \fn char* echoCmd(char* arg)
 * \brief Reproduit la commande "echo" 
 *
 * \param Chaîne à afficher
 * \return Chaîne à afficher
 */
char* echoCmd(char* arg);
/**
 * \fn char* execOutsideFunction(char* arg)
 * \brief Tente un exec de la chaîne en entrée 
 *
 * \param Chaîne à executer
 * \return Resultat
 */
char* execOutsideFunction(char* arg);
#endif