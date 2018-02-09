#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/shell.h"
#include "../include/builtin.h"

char* callCommands(char * arg)
{
    char* returnString;
    char* token;
    token = strtok(arg," ");
    if(token == NULL){
        return "Aucune commande entrée";
    }
    //Récupère les arguments
    char* cmd = token;
    token = strtok(NULL," ");
    char* cmdArg;
    if(token != NULL)
    {
        cmdArg = token;
    }
    //Appel les bonnes fonctions
    if(strcmp(cmd,"cd") == true)
    {
       returnString = cdCmd(cmdArg);
    }
    else if(strcmp(cmd,"pwd") == true)
    {
       returnString = pwdCmd();
    }
    else if(strcmp(cmd,"echo") == true)
    {
        returnString = echoCmd(cmdArg);
    }
    else
    {
        returnString = strerror(execOutsideFunction(arg));
    }
    return returnString;
}

void shellReader()
{
    int size = 100;
    char command[size];
    char* stopShell = "exit";
    while(strcmp(command,stopShell) != false)
    {
        printf("%s $ ",pwdCmd());
        readerL(command, size); 
        printf("%s\n",callCommands(command));

        //int res = execOutsideFunction(command);
       // while(endOfCommand(command,size) != 1)
       // {
        //    readerL(command, size); 
          //  printf("%s", command);
        //}
    }
}

int endOfCommand(char *chaine, int longueur)
{
    int i = 0;
    int isEnd = 0;
    while(i <10 && isEnd == 0)
    {
        if(*chaine == '\n' )
            isEnd = 1;

        chaine = chaine+1;
    }

    return isEnd;
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
        else
        {
            cleanBuffer();
        }
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        cleanBuffer();
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

void cleanBuffer()
{
    char c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
