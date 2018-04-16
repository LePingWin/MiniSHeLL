#include "../include/builtin.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/typedef.h"
#include <unistd.h>
#include <sys/wait.h>

char cwd[1024];
const int NBFunc = 3;

void cdCmd(char** arg)
{
    if(chdir(arg[1]) == true)
        pwdCmd();
    else
        perror("This directory doesn't exists");
}

void pwdCmd()
{
   if (getcwd(cwd, sizeof(cwd)) != NULL)
       printf("%s",cwd);
   else
       perror("Can't print working directory");
}

void echoCmd(char** argv)
{
    printf("%s",argv[1]);
}


