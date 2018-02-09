#include "../include/builtin.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/typedef.h"
#include <unistd.h>

char cwd[1024];

char* cdCmd(char* arg)
{
    if(chdir(arg) == true)
        return pwdCmd();
    else
        return "This directory doesn't exists";
}

char* pwdCmd()
{
   if (getcwd(cwd, sizeof(cwd)) != NULL)
       return cwd;
   else
       return "Can't print working directory ";
}

void exitCmd()
{
    exit(EXIT_SUCCESS);
}

char* echoCmd(char* arg)
{
    return arg;
}