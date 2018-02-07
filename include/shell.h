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
 * Permet de lire plus de caracteres sur
 * l'entree standard
 *
 * \return void
 */
void clean(const char *buffer, FILE *fp);
#endif