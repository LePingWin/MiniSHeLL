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
void ReadInput(char* command, int size);

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
/**
 * \fn bool CallCommands(char *cmd,char* cmdArg)
 * \brief Selectionne la bonne commande à appeler
 *
 * \param Chaîne d'entrée
 * \return Vrai si executé, faux si doit déléguer
 */
bool CallCommands(char **argv);

/**
 * \fn bool ExecuteCommand(char** argv)
 * \brief Délègue l'appel via fork/execvp à un processus fils
 *
 * \param Chaîne d'entrée
 */
bool ExecuteCommand(char **argv);


/**
 * \fn int spawn_proc(int in, int out, struct command *cmd)
 * \brief Creer un processus pour ecrire le resultat dans le pipe de sortie, redirection d'entree standard
 *
 * \param int in entree du pipe, int out sortie du pipe, struct command *cmd commande a executer
 * \return pid du processus
 */
int spawn_proc(int in, int out, char** cmd);

/**
 * \fn int fork_pipes(int n, struct command *cmd)
 * \brief Execute les commandes precedente au dernier pipe puis execute la derniere commande depuis les resultats des precedentes
 *
 * \param int n nombre de commandes, struct command *cmd commande a executer
 * \return statut de la fonction
 */
//int fork_pipes(int n, struct command *cmd);


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
void PrintWorkingDirColored();
/**
 * \fn void DecryptArgs(char* arg,char** params)
 * \brief Sépare la chaine de commande en deux chaînes de caractères
 */
void DecryptArgs(char* cmd,char** params);


char* evaluateTree(Tree t);

void ProcessCommands(char** argv,int argc);

#endif