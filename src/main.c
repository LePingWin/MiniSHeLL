#include <stdio.h>
#include <stdlib.h>
#include "../include/builtin.h"
#include "../include/shell.h"


static void
cisshPipe(char **command1, char **command2)
{
    int fd[2];
    pid_t childPid;
    if (pipe(fd) != 0)
        error("failed to create pipe");

    if ((childPid = fork()) == -1)
        error("failed to fork");

    if (childPid == 0)
    {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execvp(command1[0], command1);
        error("failed to exec command 1");
    }
    else
    {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execvp(command2[0], command2);
        error("failed to exec command 2");
    }
}

int main(int argc, char* argv[])
{
    shellReader();
    
    //char *ls[] = { "ls", 0 };
    //char *sort[] = { "grep", "Mak", 0 };
    //cisshPipe(ls, sort);
    return EXIT_SUCCESS;
}



