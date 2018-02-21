#include "../include/builtin.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/typedef.h"
#include <unistd.h>
#include <sys/wait.h>

char cwd[1024];
const int NBFunc = 3;

void cdCmd(char* arg)
{
    if(chdir(arg) == true)
        pwdCmd(arg);
    else
        printf("This directory doesn't exists\n");
}

void pwdCmd(char* arg)
{
   if (getcwd(cwd, sizeof(cwd)) != NULL)
       printf("%s",cwd);
   else
       printf("Can't print working directory\n");
}

void exitCmd(char* arg)
{
    exit(EXIT_SUCCESS);
}

void echoCmd(char* arg)
{
    printf("%s\n",arg);
}

void execOutsideFunction(char* arg)
{
    system(arg);
}

