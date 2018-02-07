#ifndef _TOOLS_H_ /* L'écriture ici présente n'est pas universelle */
#define _TOOLS_H_ /* Edit suite aux corrections des posts suivants -> */

/**
 * Fonction de lecture des commande en boucle sur la console
 *
 * \return void
 */
void shellReader();

/**
 * Lecture des elements renseignes par
 * l'utilisateur afin d'executer les
 * commandes avec ses parametres
 *
 * \return void
 */
int readerL(char *chaine, int longueur);
/**
 * Permet de savoir si la chaine contient le caractere de fin de chaine
 * 
 *
 * \return int 1 si caract de fin, 0 sinon
 */
int endOfCommand(char *chaine, int longueur);

/**
 * Vide le buffer
 *
 * \return void
 */
void cleanBuffer();
#endif