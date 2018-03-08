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

bool ExecuteCommand(char **argv)
{
    
    int pfd[2]; // entree  et sortie du pipe
    int status; // savoir si le processus esst termine ou non

    // Test echec pipe
    if (pipe(pfd) == -1)
    {
        perror("Erreur creation pipe\n");
        return false;
    }

    // Pid pour le fils
    int pid;
    
    // Test si fils cree
    if ((pid = fork()) < 0)
    {
        perror("Erreur creation fork\n");
        return false;
    }

    // Fils
    if (pid == 0)
    {
        
       
        //close(pfd[0]);   // Ferme le cote de lecture inutilise
        dup2(1, 2);      // redirige stderr vers stdout
        dup2(pfd[1], 1); // Connecte l'entree avec stdout
        close(pfd[1]);
        execvp(argv[0],argv); // Exe la commande
        exit(errno); // Permet de quitter le fils correctement
    }
    // Pere
    else
    {   
        waitpid(pid,&status,0);
        int size = 1; // pour lire un caractere apres l'autre
        
        close(pfd[1]); // Ferme l'entree 
        char reading_buf[size]; // Buffer de lecture

        // Lecture tant qu'il y a des donnees
        while (read(pfd[0], reading_buf, size) > 0)
        {
          write(1, reading_buf, size); // Ecrit dans sdout ce qui est envoye par le fils
        }

        // Si tout s'est bien passe, return true
        if(WEXITSTATUS(status) == 0)
        {
            return true;
        }
        // Sinon false
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
    //display(test);
    //parcoursPrefixe(test);
    if(background == true){
        //TODO
    }else{
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

//TODO Attention : ls -a | grep git && echo ok | ls -l || echo nok
char* evaluateTree(Tree t) {
    
    char* tmp[MAX_NUMBER_OF_PARAMS];
    for(int i=0;i < MAX_NUMBER_OF_PARAMS;i++){
        tmp[i] = malloc(sizeof(MAX_NUMBER_OF_PARAMS));
        tmp[i] = "";
    }
    
    if(sizeTree(t) == 1)
    {
        parseStringBySpaces(root(t),tmp);
        Execute(tmp);
        return "";
    }

    if(strcmp(root(t),"&&") == true || strcmp(root(t),"||") == true)
    {
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
        char* filename = "/tmp/pipe.txt";
        //Pipe management        
        // Fonctionnement via File
        fflush(stdout); // Vide le buffer (ici sortie standard)
        int original_dup = dup(STDOUT);
        freopen(filename, "w", stdout);
        
        //Execute partie de gauche
        evaluateTree(left(t));
        
        //Reset
        fflush(stdout);
        dup2(original_dup,STDOUT);
        close(original_dup);
        
        // Partie de droite
        int original_dup2 = dup(STDIN);
        freopen(filename, "r", stdin); 
        evaluateTree(right(t));
        //Reset
        fflush(stdin);
        dup2(original_dup2,STDIN);
        close(original_dup2);

        remove(filename); 
    }
    else if  (root(t)[0] == '<')
        {
            if (strcmp(root(t),"<<") == true)
            {
                char chaine[255];
                 char* tmp2 = root(right(t));
                char* filename = "/tmp/tmp-miniShell.txt";
                FILE *p1;
                p1=fopen(filename,"w+");
                do{
                    printf("> ");
                    readerL(chaine,255);
                    fprintf(p1, "%s\n", chaine);
                    chaine[strcspn(chaine, "\n") ] = '\0';
                }while(strcmp(chaine,tmp2) != true);
                
                 
                fclose(p1);
                 strcat(root(left(t))," ");
                 strcat(root(left(t)),filename);
                 
                evaluateTree(left(t));

                
                remove(filename);
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
        return root(t);
    }
    return "";
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
