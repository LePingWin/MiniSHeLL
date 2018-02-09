/**
 * \file builtin.h
 * \brief Gestion du Shell
 * \author Jean.S
 *
 *  Gestion du Shell et de l'IHM
 *
 */
#ifndef _SHELL_H_ /* L'écriture ici présente n'est pas universelle */
#define _SHELL_H_ /* Edit suite aux corrections des posts suivants -> */

/**
 * \fn void shellReader()
 * \brief Fonction de lecture des commande en boucle sur la console
 *
 */
void shellReader();

/**
 * \fn int readerL(char *chaine, int longueur)
 * \brief Lecture des elements renseignes par l'utilisateur afin d'executer les commandes avec ses parametres
 *
 * \param Chaîne d'entrée
 * \param Longueur de la chaîne d'entrée
 * \return resultat
 */
int readerL(char *chaine, int longueur);
/**
 * \fn int endOfCommand(char *chaine, int longueur)
 * \brief Permet de savoir si la chaine contient le caractere de fin de chaine
 *
 * \param Chaîne d'entrée
 * \param Longueur de la chaîne d'entrée
 * \return int 1 si caract de fin, 0 sinon
 */
int endOfCommand(char *chaine, int longueur);

/**
 * \fn void cleanBuffer()
 * \brief Vide le buffer
 *
 */
void cleanBuffer();
#endif