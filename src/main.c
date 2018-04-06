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
            char *commands[MAX_COMMAND_LENGTH]; // Stocke le nombre de commande
            char* command; // Commande en cours d'evaluation
            char *argvcmd[MAX_COMMAND_LENGTH]; // Tableau des arguments de la commande

            for(int i=0;i < MAX_NUMBER_OF_CMD;i++){
                commands[i] = malloc(sizeof(char)* MAX_COMMAND_LENGTH);
                commands[i] = "";
            }
        
            int nbCommand = parseStringBySep(argv[2],commands,";");
            for(int i=0;i<nbCommand;i++)
            {
                command = commands[i];
                int size = parseStringBySpaces(command,argvcmd);
                processCommands(argvcmd,size);
            }
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



