#include "../headers/builtin.h"
#include <stdlib.h>
#include <stdio.h>
#include "../headers/typedef.h"
#include <unistd.h>

void cdCmd(char* arg)
{
    if(chdir(arg) == true)
        pwdCmd();
    else
        perror("This directory doesn't exists");
}

void pwdCmd()
{
   char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL)
       dprintf(STDOUT,"%s\n", cwd);
   else
       perror("Can't print working directory ");
}

void exitCmd()
{
    exit(EXIT_SUCCESS);
}

void echoCmd(char* arg)
{
    dprintf(STDOUT,"%s\n",arg);
}