#include <stdio.h>
#include <stdlib.h>
#include "../include/builtin.h"
#include "../include/shell.h"
#include "../include/parser.h"
#include <string.h>

#define USAGE_SYNTAX "[OPTIONS] -c \"COMMAND\""
#define USAGE_PARAMS "OPTIONS:\n\
  -i, --command  COMMAND  : command string between double quotes\n\
"

/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name)
{
  dprintf(1, "USAGE: %s %s\n\n%s\n", bin_name, USAGE_SYNTAX, USAGE_PARAMS);
}


int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        // Gestion du mode batch
        if(strcmp(argv[1],"-c") == true){
            char* cmd = calloc(sizeof(char),MAX_COMMAND_LENGTH);//CMD entree par user
            char** commands = calloc(sizeof(char*),MAX_COMMAND_LENGTH); //CMDs spliter par ;
            char** argvcmd = calloc(sizeof(char*),MAX_COMMAND_LENGTH); //Contient les cmds, args et operateurs spliter par espace

            for(int i=0;i < MAX_NUMBER_OF_CMD;i++){
                commands[i] = calloc(sizeof(char),MAX_COMMAND_LENGTH);
                argvcmd[i] = calloc(sizeof(char),MAX_COMMAND_LENGTH);
            }
        
            int nbCommand = parseStringBySep(argv[2],commands,";");
            for(int i=0;i<nbCommand;i++)
            {
                strcpy(cmd,commands[i]);
                int size = parseStringBySpaces(cmd,argvcmd);
                processCommands(argvcmd,size);
            }
            //Libere allocation
            free(cmd);
            for(int i=0;i < MAX_COMMAND_LENGTH;i++){
                free(argvcmd[i]);
                free(commands[i]);  
            }
            //Libere allocation
            free(commands);
            free(argvcmd); 
        }
        // Erreur lors du passage de l'argument
        else
        {
            print_usage(argv[0]);
        }
    }
    // Lancement standard du shell
    else
    {
        shellReader();
    }
    return 0;
}



