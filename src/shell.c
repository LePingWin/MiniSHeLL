#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/shell.h"
#include "../include/builtin.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../include/typedef.h"




bool CallCommands(char **argv)
{
    //Appel les bonnes fonctions
    if (strcmp(argv[0], "cd") == true)
    {
        cdCmd(argv);
    }
    else if (strcmp(argv[0], "pwd") == true)
    {
        pwdCmd("");
    }
    else if (strcmp(argv[0], "exit") == true)
    {
        exitCmd("");
    }
    else if (strcmp(argv[0], "echo") == true)
    {
        echoCmd(argv);
    }
    else
    {
        return false;
    }
    printf("\n");
    return true;
}

void ExecuteCommand(char **argv)
{
    int pfd[2];
    if (pipe(pfd) == -1)
    {
        perror("pipe failed\n");
        return;
    }

    /* create the child */
    int pid;
    if ((pid = fork()) < 0)
    {
        perror("fork failed\n");
        return;
    }

    if (pid == 0)
    {
        /* child */
        close(pfd[0]);   /* close the unused read side */
        dup2(1, 2);      /* redirect stderr to stdout */
        dup2(pfd[1], 1); /* connect the write side with stdout */
        execvp(argv[0],argv);
        exit(0);
    }
    else
    {
        wait(NULL);
        int size = 1;
        /* parent */
        close(pfd[1]); /* close the unused write side */
        char reading_buf[size];
        while (read(pfd[0], reading_buf, size) > 0)
        {
          write(1, reading_buf, size);
        }
        
    }
}

void PrintWorkingDirColored()
{
    printf("%s", KYEL);
    pwdCmd("");
    printf("$ %s", KNRM);
}

void shellReader()
{
    char command[MAX_COMMAND_LENGTH];
    char *stopShell = "exit";
    char *argv[MAX_COMMAND_LENGTH];
    do{

        ReadInput(command, MAX_COMMAND_LENGTH);
        DecryptArgs(command,argv);
        if(CallCommands(argv) == false)
        {
            ExecuteCommand(argv);
        }
        // while(endOfCommand(command,size) != 1)
        // {
        //    readerL(command, size);
        //  printf("%s", command);
        //}
    } while (strcmp(command, stopShell) != true);
}

void DecryptArgs(char* cmd, char** params)
{       
    for(int i = 0; i < MAX_NUMBER_OF_PARAMS; i++) {
        params[i] = strsep(&cmd, " ");
        if(params[i] == NULL) break;
    }
}

void ReadInput(char *command, int size)
{
    PrintWorkingDirColored();
    readerL(command, size);
    historize(command);
}

int endOfCommand(char *chaine, int longueur)
{
    int i = 0;
    int isEnd = 0;
    while (i < 10 && isEnd == 0)
    {
        if (*chaine == '\n')
            isEnd = 1;

        chaine = chaine + 1;
    }

    return isEnd;
}

int readerL(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL) // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL)            // Si on a trouvé le retour à la ligne
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

void historize(char *arg)
{
    FILE *pFile = fopen("/tmp/hist.txt", "a");
    if (pFile == NULL)
    {
        return;
    }
    fprintf(pFile, "%s\n", arg);
    fclose(pFile);
}
