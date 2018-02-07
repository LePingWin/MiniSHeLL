#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"../include/shell.h"

void shellReader()
{
    int size = 100;
    char command[size];
    while(1==1)
    {
        
        printf("Quelle est votre commande ? ");
        readerL(command, size);
        printf("Ah ! Votre commande est %s !\n\n", command);
    }
}
int readerL(char *chaine, int longueur)
{
    char *positionEntree = NULL;
 
    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

void clean(const char *buffer, FILE *fp)
{
    char *p = strchr(buffer, '\n');
    if(p != NULL)
        *p = 0;
    else
    {
        int c;
        while((c = fgetc(fp)) != '\n' && c != EOF);
    }
}