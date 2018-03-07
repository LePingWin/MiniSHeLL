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
#include <errno.h>




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
//TODO Revoir le fonctionnement si on utilise les pipes
bool ExecuteCommand(char **argv)
{
    printf("[0] : %s - [1] : %s \n", argv[0], argv[1]);
    int pfd[2];
    int status;
    if (pipe(pfd) == -1)
    {
        perror("pipe failed\n");
        return false;
    }

    /* create the child */
    int pid;
    
    if ((pid = fork()) < 0)
    {
        perror("fork failed\n");
        return false;
    }

    if (pid == 0)
    {
        /* child */
        //close(STDIN);
        
        //dup2(pfd[0],STDIN);
        //close(pfd[0]);   /* close the unused read side */
        dup2(1, 2);      /* redirect stderr to stdout */
        dup2(pfd[1], 1); /* connect the write side with stdout */
        close(pfd[1]);
        execvp(argv[0],argv);
        exit(errno);
    }
    else
    {
        //wait(NULL);
        waitpid(pid,&status,0);
        int size = 1;
        // parent 
        close(pfd[1]); // close the unused write side 
        char reading_buf[size];
        while (read(pfd[0], reading_buf, size) > 0)
        {
          write(1, reading_buf, size);
        }
        if(WEXITSTATUS(status) == 0)
        {
            return true;
        }

        return false;
        
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
    char *commands[MAX_COMMAND_LENGTH];
    char* command;
    char cmd[MAX_COMMAND_LENGTH];


    char *stopShell = "exit";
    char *argv[MAX_COMMAND_LENGTH];
    do{
        for(int i=0;i < MAX_NUMBER_OF_CMD;i++){
            commands[i] = malloc(sizeof(cmd));
            commands[i] = "";
        }
        ReadInput(cmd, MAX_COMMAND_LENGTH);
        int nbCommand = parseStringBySep(cmd,commands,";");
        for(int i=0;i<nbCommand;i++)
        {
            command = commands[i];
            int size = parseStringBySpaces(command,argv);
            ProcessCommands(argv,size);
        }
    } while (strcmp(command, stopShell) != true);

}

    void ProcessCommands(char** argv,int argc)
    {
            char *parsed[MAX_COMMAND_LENGTH];
            Tree test;
            bool background = false;
            for(int j=0;j < MAX_COMMAND_LENGTH;j++){
                parsed[j] = malloc(sizeof(char*)*MAX_COMMAND_LENGTH);
                parsed[j] = "";
            }

            int sizeParsed = parseStringBySpecialChars(argv,parsed,argc);
            if(sizeParsed-1 >= 0 && strcmp(parsed[sizeParsed-1],"&") == true)
            {
                sizeParsed--;
                background = true;
            }
            
            if(sizeParsed % 2 != 0 )
            {
                perror("Wrong Syntax\n");
                return;
            }

            test = parseStringToStacks(parsed,sizeParsed);
            display(test);
            //parcoursPrefixe(test);
            if(background == true){
                //TODO
            }else{
                printf("CALL - EVALUATE TREE \n");
                evaluateTree(test);
            }
            free(test);
    }

bool Execute(char** argv)
{
        bool ok;
        if((ok = CallCommands(argv)) == false)
        {
            return ExecuteCommand(argv);
        }
        return ok;
}

//TODO Pipe avec pipe necessite de revoir le fonctionnement de Execute !
char* evaluateTree(Tree t) {
    perror("EVALUATE TREE \n");
    char* tmp[MAX_NUMBER_OF_PARAMS];
    for(int i=0;i < MAX_NUMBER_OF_PARAMS;i++){
        tmp[i] = malloc(sizeof(MAX_NUMBER_OF_PARAMS));
        tmp[i] = "";
    }
    display(t);
    if(sizeTree(t) == 1)
    {
        printf("EVALUATE TREE - SIZE 1 \n");
        
        parseStringBySpaces(root(t),tmp);
        
        printf("[0] : %s - [1] : %s \n", tmp[0], tmp[1]);
        //Execute(tmp);
        //dup(0);
        execvp(tmp[0], tmp);
        return "";
        
    }

    if(strcmp(root(t),"&&") == true || strcmp(root(t),"||") == true)
    {
        printf("EVALUATE TREE - && ||\n");
        parseStringBySpaces(root(left(t)),tmp);
        bool res = Execute(tmp);
            if(res == true && strcmp(root(t),"&&") == true)
            {          
                evaluateTree(right(t));
                
            }
            else if(res == false && strcmp(root(right(t)),"||") == true)
            {
                evaluateTree(right(right(t)));
            }
            else if(res == false)
            {
                evaluateTree(right(t));
            }
            else
            {
                return "";
            }

    }
    else if (strcmp(root(t),"|") == true)
    {
        //Pipe management
        printf("EVALUATE TREE - PIPE \n");
        char* cmd2[MAX_NUMBER_OF_PARAMS];
        for(int i=0;i < MAX_NUMBER_OF_PARAMS;i++){
            cmd2[i] = malloc(sizeof(MAX_NUMBER_OF_PARAMS));
            cmd2[i] = "";
        }
        parseStringBySpaces(root(left(t)),tmp);
        //parseStringBySpaces(root(right(t)),cmd2);
        //executePipe(tmp,cmd2);

        int fd[2];
        pid_t childPid;
        printf("PIPE executing \n");

        if (pipe(fd) != 0)
            //error("failed to create pipe");
            printf("failed to create pipe \n");
        if ((childPid = fork()) == -1)
            //error("failed to fork");
            printf("failed to fork \n");

        if (childPid == 0)
        {
            //printf("fils \n");
            dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            //Execute(tmp);
            execvp(tmp[0], tmp);
            return "";
            //error("failed to exec command 1");
        }
        else
        {       
            dup2(fd[0], 0);
            //parseStringBySpaces(root(right(t)),cmd2);

            close(fd[0]);
            close(fd[1]);
            
            //execvp(cmd2[0], cmd2);

            evaluateTree(right(t));     
            return "";
            
        }                                                       

        // TODO Bug de redirection des resultats des pipes intermediaires. 
        // + comment on enchaine de la suite de levaluation si le pipe est en plein milieu de la commande tapper dans le shell ?!
    }
    else if  (root(t)[0] == '<')
        {
            if (strcmp(root(t),"<<") == true)
            {
                char cat[1024];
                char chaine[255];
                fflush(stdin);
                //TODO : Saisie au clavier https://openclassrooms.com/courses/reprenez-le-controle-a-l-aide-de-linux/les-flux-de-redirection
                 char* tmp2 = root(right(t));
                 do{
                    printf("> ");
                    readerL(chaine,255);
                    // Use the input if you want to
                     // Throw away the input
                     
                     strcpy(cat,chaine);
                    chaine[strcspn(chaine, "\n") ] = '\0';
                   if(cat == NULL){
                       strcpy(cat,chaine);
                   }else{
                       strcat(cat,"\n");
                       strcat(cat,chaine);
                   }
                 }while(strcmp(chaine,tmp2) != true);

                 //close(STDIN);
                 //Execute(tmp);
               
                 //strcat(root(left(t))," ");
                 //strcat(root(left(t)),cat);
                evaluateTree(left(t));
                   
            //Reset
                //fflush(stdin);
            }
            else
            {
                int original_dup = dup(STDIN);
                freopen(root(right(t)), "r", stdin); 
                evaluateTree(left(t));
                fflush(stdin);
                dup2(original_dup,STDIN);
                close(original_dup); 
            }

        }
        else if (root(t)[0] == '>')
        {
            int original_dup = dup(STDOUT);
            if (strcmp(root(t),">>") == true)
            {
                freopen(root(right(t)), "a+", stdout); 
            }
            else
            {
                freopen(root(right(t)), "w", stdout); 
            }
            //Execute
            evaluateTree(left(t));
            //Reset
            fflush(stdout);
            dup2(original_dup,STDOUT);
            close(original_dup);
        }
    else
    {
        perror("EVALUATE TREE - ELSE \n");
        return root(t);
    }
    return "";
}




int spawn_proc (int in, int out, char** cmd)
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

      return execvp (cmd[0], cmd);
    }

  return pid;
}


void ReadInput(char *command, int size)
{
    printf("CALL - READInput \n");
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
