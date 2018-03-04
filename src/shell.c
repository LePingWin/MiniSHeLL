#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/shell.h"
#include "../include/builtin.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../include/typedef.h"
#include "../include/parser.h"
#include "../include/tree.h"




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

int spawn_proc (int in, int out, struct command *cmd)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          close (in);
        }

      if (out != 1)
        {
          dup2 (out, 1);
          close (out);
        }

      return execvp (cmd->argv [0], (char * const *)cmd->argv);
    }

  return pid;
}

int fork_pipes (int n, struct command *cmd)
{
  int i;
  pid_t pid;
  int in, fd [2];

  // Le premier processus devrait obtenir son entree du descripteur de fichier original 0
  in = 0;

  // Execution de toutes les commande sauf de la derniere
  for (i = 0; i < n - 1; ++i)
    {
      pipe (fd);

      // f [1] est la fin d'ecriture du pipe, 'in' = de la precedente iteration
      spawn_proc (in, fd [1], cmd + i);

      // Pas besoin d'ecrire a la fin du pipe, le fils ecrira dedans
      close (fd [1]);

      // Garde la fin de lecture du pipe, le prochain fils lira depuis celui-ci
      in = fd [0];
    }

    // Derniere etape du pipe, setter stdin en lecture de fin du precedent pipe 
    // et en sortie du descripteur 1 original  
    if (in != 0)
        dup2 (in, 0);

    // Execute la derniere etape avec le processus courant
    return execvp (cmd [i].argv [0], (char * const *)cmd [i].argv);
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
    Tree test;
    char *parsed[MAX_COMMAND_LENGTH];

    do{
        for(int i=0;i < MAX_COMMAND_LENGTH;i++){
            parsed[i] = malloc(sizeof(command));
            parsed[i] = "";
        }
        ReadInput(command, MAX_COMMAND_LENGTH);
        int size = parseStringBySpaces(command,argv);
        int sizeParsed = parseStringBySpecialChars(argv,parsed,size);
        test = parseStringToStacks(parsed,sizeParsed);
        display(test);
        /*if(CallCommands(argv) == false)
        {
            ExecuteCommand(argv);
        }*/
        // while(endOfCommand(command,size) != 1)
        // {
        //    readerL(command, size);
        //  printf("%s", command);
        //}    
        free(test);
    } while (strcmp(command, stopShell) != true);

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
