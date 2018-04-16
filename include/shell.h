/**
 * \file shell.h
 * \brief Gestion du Shell
 * \author Loïc.B et Jean.S
 *
 *  Gestion du Shell et de l'IHM
 *
 */
#ifndef _SHELL_H_ /* L'écriture ici présente n'est pas universelle */
#define _SHELL_H_ /* Edit suite aux corrections des posts suivants -> */

#include "typedef.h"

/**
 * \fn void shellReader()
 * \brief Fonction de lecture des commande en boucle sur la console
 *
 */
void shellReader();


/**
 * \fn ReadInput(char command, int size)
 * \brief Wrapper 
 * \param Chaîne d'entrée
 * \param Longueur de la chaîne d'entrée
 */
void readInput(char* command, int size);

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
 * \fn bool CallCommands(char *cmd,char* cmdArg)
 * \brief Selectionne la bonne commande à appeler
 *
 * \param Chaîne d'entrée
 * \return Vrai si executé, faux si doit déléguer
 */
bool callCommands(char **argv);

/**
 * \fn bool executeCommand(char** argv)
 * \brief Délègue l'appel via fork/execvp à un processus fils
 *
 * \param Chaîne d'entrée
 */
bool executeCommand(char **argv);

/**
 * \fn bool executeCommand(char** argv)
 * \brief Redirige l'execution des cmds vers les commandes programmees maison quand c'est necessaire
 *
 * \param Chaîne d'entrée, cmd + args
 */
bool execute(char **argv);


/**
 * \fn void ExecuteCommand(char *cmd,char* cmdArg)
 * \brief Historise les commandes dans un fichier
 *
 * \param Chaîne d'entrée
 */
void historize(char* arg);

/**
 * \fn void PrintWorkingDirColored()
 * \brief Affiche le chemin du répertoire courant
 *
 */
void printWorkingDirColored();
/**
 * \fn void DecryptArgs(char* arg,char** params)
 * \brief Sépare la chaine de commande en deux chaînes de caractères
 */
void decryptArgs(char* cmd,char** params);

/**
 * \fn char* evaluateTree(Tree t)
 * \brief Permet d'evaluer l'arbre compose des commandes et operateurs
 * 
 * \param Tree noeud a évaluer
 * \return resultat d'exécution du noeuf passé en paramètre
 */ 
bool evaluateTree(Tree t);

/**
 * \fn char* evaluateTree(Tree t)
 * \brief Permet d'executer la commande et d'evaluer si cette derniere doit s'executer en arriere plan
 */ 
void processCommands(char** argv,int argc);

#endif