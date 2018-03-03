#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <regex.h>    
#include "../include/typedef.h"
#include "../include/stack.h"
#include "../include/stackTree.h"
#include "../include/tree.h"

const char* SPECIAL_CHARS = "(^[&|><]+)";

int parseStringBySpaces(char* arg,char** parsed)
{
    int i;
    for(i=0; i < MAX_NUMBER_OF_PARAMS; i++) {
        parsed[i] = strsep(&arg, " ");
        if(parsed[i] == NULL) break;
    }
    return i;
}

int parseStringBySpecialChars(char** parsed,char** result,int size){
    int c = 0;
    regex_t regex;
    char msgbuf[100]; 
    /* Compile regular expression */
    int reti = regcomp(&regex, SPECIAL_CHARS, REG_EXTENDED);
    if (reti) {
        perror("Could not compile regex\n");
    }
    for(int i = 0; i < size; i++) {
        /* Execute regular expression */
        reti = regexec(&regex,parsed[i], 0, NULL, 0);
        if (!reti) 
        {
            result[++c] = parsed[i];
            c++;
        }
        else if (reti == REG_NOMATCH) 
        {
            if(result[c] == NULL)
            {
                strcpy(result[c],parsed[i]);
            }
            else{
                strcat(result[c], parsed[i]);
            }
        }
        else 
        {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            perror(msgbuf);
        }
    }
     /* Free memory allocated to the pattern buffer by regcomp() */
    regfree(&regex);

    return c;
}

void addNodeStackTree(StackTree stack, char* operator) {
    Tree tmpRight;
    Tree tmpLeft;
    popStackTree(stack,&tmpRight);
    popStackTree(stack,&tmpLeft);
    pushStackTree(stack,createTree(operator, tmpLeft, tmpRight));
}

Tree parseStringToStacks(char** parsed,int sizeParsed)
{
    Stack operators = NULL;
    StackTree operands = NULL;
    init(operators);
    initStackTree(operands);
    char* tmpStack = "";
    int i;
    for(i = 0; i < sizeParsed;i++)
    {
        char* tmp = parsed[i];
        if(strcmp(tmp,"||") || strcmp(tmp,"&&"))
        {
            operators = push(operators,tmp);
        }
        else if(strcmp(tmp,"("))
        {
            operators = push(operators,tmp);
        }
        else if(strcmp(tmp,")"))
        {

            while(strcmp(tmpStack,"("))
            {
                operators = pop(operators,&tmpStack);
                addNodeStackTree(operands,tmpStack);
            }
            
        }
        else
        {
            operands = pushStackTree(operands,createTree(tmp,NULL,NULL));
        }

    }


    while(empty(operators) == false)
    {
       operators = pop(operators,&tmpStack);
       addNodeStackTree(operands,tmpStack);
    }

    Tree result;
    popStackTree(operands,&result);

    free(operators);
    free(operands);
    return result; 
}


    


