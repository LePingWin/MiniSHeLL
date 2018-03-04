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
            if(strcmp(parsed[i],"|") == true || strcmp(parsed[i],"&") == true){

                if(result[c] == NULL || strcmp(result[c],"") == true)
                {
                    result[c] = parsed[i];
                    //strcpy(result[c],parsed[i]);
                }
                else{
                    strcat(result[c], parsed[i]);
                }
            }else{
               // printf("%s\n",parsed[i]);
                result[++c] = parsed[i];
                c++;
            }
        }
        else if (reti == REG_NOMATCH) 
        {
            if(result[c] == NULL || strcmp(result[c],"") == true)
            {
                result[c] = parsed[i];
                //strcpy(result[c],parsed[i]);
            }
            else
            {
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

void addNodeStackTree(StackTree *stack, char* operator) {
    Tree tmpRight =popStackTree(stack);
    Tree tmpLeft = popStackTree(stack);
    Tree tmp = createTree(operator, tmpLeft, tmpRight);
    pushStackTree(stack,tmp);
}

Tree parseStringToStacks(char** parsed,int sizeParsed)
{
    Stack operators = newNode(NULL);
    StackTree operands = newNodeStackTree(NULL);
    pop(&operators);
    popStackTree(&operands);
    int i;
    for(i = 0; i <= sizeParsed;i++)
    {
        char* tmp = parsed[i];
        //strcpy(tmp,parsed[i]);
        if(strcmp(tmp,"||") == true || strcmp(tmp,"&&") == true)
        {
            push(&operators,tmp);
        }
        else if(strcmp(tmp,"(")== true)
        {
            push(&operators,tmp);
        }
        else if(strcmp(tmp,")")== true)
        {
            char * tmpStack;
            while(strcmp((tmpStack = pop(&operators)),"(")== true)
            {
                addNodeStackTree(&operands,tmpStack);
            }
            
        }
        else
        {
            pushStackTree(&operands,createTree(tmp,NULL,NULL));
        }
        //free(tmp);
    }

    while(empty(operators) == true)
    {
       addNodeStackTree(&operands,pop(&operators));
       
    }
    return peekStackTree(operands);
    
}


    


