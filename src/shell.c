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


bool callCommands(char **argv)
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

bool executeCommand(char **argv)
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
        exit(1); // Permet de quitter le fils correctement
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

void printWorkingDirColored()
{
    printf("%s", KYEL);
    pwdCmd("");
    printf("$ %s", KNRM);
}


void shellReader()
{
    char* stopShell = "exit"; //CMD d'arret du shell
    bool flagContinue = true; // Flag pour le prompt du shell

    char* cmd ;//CMD entree par user
    char** commands = calloc(sizeof(char*),MAX_COMMAND_LENGTH); //CMDs spliter par ;
    char** argv = calloc(sizeof(char*),MAX_COMMAND_LENGTH); //Contient les cmds, args et operateurs spliter par espace

    //Prompt shell
    while (flagContinue == true){
        // Alloue memoire
        cmd = calloc(sizeof(char),MAX_COMMAND_LENGTH);
        for(int i=0;i < MAX_COMMAND_LENGTH;i++){
            commands[i] = calloc(sizeof(char),MAX_COMMAND_LENGTH);
            argv[i] = calloc(sizeof(char),MAX_COMMAND_LENGTH);
        }

        //Lecture entree utilisateur
        readInput(cmd, MAX_COMMAND_LENGTH);
        
        //Sortie shell
        if(strcmp(cmd, stopShell) == true){
            flagContinue = false;
            //Libere allocation
            free(cmd);
            for(int i=0;i < MAX_COMMAND_LENGTH;i++){
                free(argv[i]);
                free(commands[i]);  
            }
        }   
        //Sinon execute cmd
        else{
            //Split par paquet de commandes en prevision des multiples fork
            int nbCommand = parseStringBySep(cmd,commands,";");
            //Libere allocation
            free(cmd);
            
            //Evalue et lance l'execution des cmd
            for(int i=0;i<nbCommand;i++)
            {
                int size = parseStringBySpaces(commands[i],argv);
                for(int i=0;i < MAX_COMMAND_LENGTH;i++){
                    free(commands[i]);  
                }
                //printf("%s \n",argv[0]);
                processCommands(argv,size);
            }
        }    
    }
    //Libere allocation
    free(commands);
    free(argv);  
}

void processCommands(char** argv,int argc)
{
    Tree arbreCMD; //Arbre contenant les operateurs et cmd
    bool background = false; //Lancer la commande en arriere plan
    
    //Alloue memoire
    char** parsed = calloc(sizeof(char*),MAX_COMMAND_LENGTH); //Contient les CMDs + Args spliter par operateurs
    for(int i=0;i < MAX_COMMAND_LENGTH;i++){
        parsed[i] = calloc(sizeof(char),MAX_COMMAND_LENGTH);  
    }

    int sizeParsed = parseStringBySpecialChars(argv,parsed,argc);
    if(sizeParsed-1 >= 0 && strcmp(parsed[sizeParsed-1],"&") == true)
    {
        sizeParsed--;
        sizeParsed--;
        background = true;
    }
    
    if(sizeParsed % 2 != 0 && sizeParsed > 1) 
    {
        perror("Wrong Syntax\n");
        return;
    }

    arbreCMD = parseStringToStacks(parsed,sizeParsed);
    //display(arbreCMD);
    //parcoursPrefixe(test);
    //Arriere plan
    if(background == true)
    {
        // Pid pour le fils
        int pid;
        // Test si fils cree
        if ((pid = fork()) < 0)
            perror("Erreur creation fork\n");
        // Fils
        if (pid == 0)
            evaluateTree(arbreCMD);
    }
    else
        evaluateTree(arbreCMD);
    
    //Libere memoire
    for(int i=0;i < MAX_COMMAND_LENGTH;i++){
        free(parsed[i]);
    }
    free(parsed);
    free(arbreCMD);
}

bool execute(char** argv)
{
    bool ok;//True si cmd maison, false sinon --> (execvp)

    if((ok = callCommands(argv)) == false)
        return executeCommand(argv);
    return ok;
}

bool loopPipe(char ***cmd) 
{
    int   p[2]; //In OUT pipe
    pid_t pid; //pid fils
    int   fd_in = STDIN; //In pipe pour partager les infos entre cmd
    int status = true; // savoir si le processus esst termine ou non
    
    //Execution pour cmd dans un processus fils
    while (*cmd != NULL)
    {
        pipe(p);
        if ((pid = fork()) == -1)
        {
            perror("Erreur creation fork\n");
            exit(1);
        }
        //Fils
        else if (pid == 0)
        {
            dup2(fd_in, STDIN); //change l'entree vers stdin
            if (*(cmd + 1) != NULL)
                dup2(p[1], 1);
            close(p[0]);

        //execvp((*cmd)[0], *cmd);
            status = execute(*cmd);
            exit(status);
        }
        //Pere
        else
        {
            //wait(NULL);
            waitpid(pid,&status,0);
            close(p[1]);
            fd_in = p[0]; //sauvegarde entree pipe pour la prochaine cmd
            cmd++;
            // Si tout s'est bien passe, return true
            if(WEXITSTATUS(status) == 0)
            {
                status = true;
            }
            else
            {
                status = false;
            }
            
        }
    }
    return status;
}
bool executePipe(char** tmp, int nbCMDs)
{
    int status = true;
    //Alloue memoire 
    char ***cmd = calloc(sizeof(char**),MAX_NUMBER_OF_PARAMS); //Tableau contenant les cmds contenant les args 
    for(int i = 0; i < MAX_NUMBER_OF_PARAMS; i++){
        cmd[i] = calloc(sizeof(char*),MAX_NUMBER_OF_PARAMS); 
        for(int j = 0 ; j < MAX_NUMBER_OF_PARAMS ; j++){
            cmd[i][j] = calloc(sizeof(char),MAX_COMMAND_LENGTH);
        }
    }

    for(int i = 0; i < nbCMDs ; i++){
        char** cmdsParsed = calloc(sizeof(char*),MAX_NUMBER_OF_PARAMS);
        for(int j = 0; j < MAX_NUMBER_OF_PARAMS; j++){
            cmdsParsed[j] = calloc(sizeof(char),MAX_COMMAND_LENGTH);
        }

        int nbstr = parseStringBySpaces(tmp[i],cmdsParsed);

        for(int j = 0 ; j < MAX_NUMBER_OF_PARAMS ; j++){
            if(j<nbstr){
                strcpy(cmd[i][j],cmdsParsed[j]);
            }else{
                free(cmd[i][j]);
            }
        }

        for(int j = 0 ; j < MAX_NUMBER_OF_PARAMS ; j++){        
            free(cmdsParsed[j]);
        }
        free(cmdsParsed);

        cmd[i][nbstr] = 0; // End of cmd
    }
    //Désalloue le reste de la case contenant la fin des commandes.
    for(int j=0 ; j < MAX_NUMBER_OF_PARAMS ; j++){
        free(cmd[nbCMDs][j]);
    }
    free(cmd[nbCMDs]);
    //Fin du tableau de cmd
    cmd[nbCMDs] = 0; 
            
    status = loopPipe(cmd);
    
    //Libere memoire
    for(int i = 0; i < MAX_NUMBER_OF_PARAMS; i++){
        //@ valide
        if(cmd[i] != 0){
            for(int j = 0; j < MAX_NUMBER_OF_PARAMS;j++){
                if(cmd[i][j] ==0)
                    break;
                free(cmd[i][j]);
            }
            free(cmd[i]);
        } 
    }
    free(cmd);

    return status;
}


//DONE : ls -a | grep git && echo ok | ls -l || echo nok
bool evaluateTree(Tree t) {
    int status = true; //Statut de l'execution de la cmd
    
    //Une seule " "cmd + args ou un groupe de cmds + args pipées
    if(isLeaf(t) == true)
    {
        //Alloue memoire
        char** CMDsByPipe = calloc(sizeof(char*),MAX_NUMBER_OF_PARAMS); // contient cdms + args splites
        for(int i=0;i < MAX_NUMBER_OF_PARAMS;i++){
            CMDsByPipe[i] = calloc(sizeof(char),MAX_NUMBER_OF_PARAMS);
            
        }
        // Execution des cmds pipee
        int nb = parseStringBySep(root(t),CMDsByPipe,"|");
        if(nb > 1 ){
            status = executePipe(CMDsByPipe, nb);
        }
        //Une cmd + args
        else
        {
            //Alloue memoire
            char** CMDsBySpaces = calloc(sizeof(char*),MAX_NUMBER_OF_PARAMS); // contient cdms + args splites
            for(int i=0;i < MAX_NUMBER_OF_PARAMS;i++){
                CMDsBySpaces[i] = calloc(sizeof(char),MAX_NUMBER_OF_PARAMS);
            }

            parseStringBySpaces(root(t),CMDsBySpaces);

            status = execute(CMDsBySpaces);
             //Libere memoire
            for(int i=0;i < MAX_NUMBER_OF_PARAMS;i++){
                free(CMDsBySpaces[i]);
            }
            free(CMDsBySpaces);
        }
        //Libere memoire
        for(int i=0;i < MAX_NUMBER_OF_PARAMS;i++){
            free(CMDsByPipe[i]);
        }
        free(CMDsByPipe);
        return status;
        
    }
    // Traitement operateur && et ||
    if(strcmp(root(t),"&&") == true || strcmp(root(t),"||") == true)
    {
        bool status = evaluateTree(left(t));
        if(status == true && strcmp(root(t),"&&") == true)
        {          
            return evaluateTree(right(t));
        }
        else if(status == false && strcmp(root(t),"||") == true)
        {
            return evaluateTree(right(t));
        }
        //Case root(t) == && et status == false donc Switch jusqu'au prochain operateur != && s'il existe
        //Case root(t) == || et status == true donc Switch jusqu'au prochain operateur != || s'il existe
        else
        {
            bool flagOtherOperator = false;
            Tree Ttmp = t;
            while(flagOtherOperator == false && sizeTree(right(Ttmp)) > 1)
            {
                Ttmp = right(Ttmp);
                if((strcmp(root(Ttmp),"&&") != true && status == false) || (strcmp(root(Ttmp),"||") != true && status == true))
                {
                    flagOtherOperator = true;
                } 
            }
            if(flagOtherOperator == true)
                return evaluateTree(right(Ttmp));
            return true;
        }
    }
    else if  (root(t)[0] == '<')
    {
        if (strcmp(root(t),"<<") == true)
        {
            char chaine[255];
            char* filename = "/tmp/tmp-miniShell.txt";
            FILE *p1;
            p1=fopen(filename,"w+");
            do{
                printf("> ");
                readerL(chaine,255);
                fprintf(p1, "%s\n", chaine);
                chaine[strcspn(chaine, "\n") ] = '\0';
            }while(strcmp(chaine,root(right(t))) != true);
                
            fclose(p1);
            strcat(root(left(t))," ");
            strcat(root(left(t)),filename);
                
            status = evaluateTree(left(t));

            remove(filename);
        }
        else
        {
            int original_dup = dup(STDIN);
            freopen(root(right(t)), "r", stdin); 
            //Execute
            status = evaluateTree(left(t));
            //Reset
            fflush(stdin);
            dup2(original_dup,STDIN);
            close(original_dup); 
        }
        return status;

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
        status = evaluateTree(left(t));
        //Reset
        fflush(stdout);
        dup2(original_dup,STDOUT);
        close(original_dup);
        return status;
    }
    /*else
    {
        return root(t);
    }*/
    return status;
}

void readInput(char *command, int size)
{
    printWorkingDirColored();
    readerL(command, size);
    historize(command);
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
