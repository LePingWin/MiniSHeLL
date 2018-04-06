#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <regex.h>    
#include "../include/typedef.h"
#include "../include/stack.h"
#include "../include/stackTree.h"
#include "../include/tree.h"

const char* SPECIAL_CHARS = "([&><]+)|(\\|{2,})";

int parseStringBySep(char* arg,char** parsed,char* sep)
{
    int i =0; //nb d'elements
    char* token = strtok(arg, sep);
    // Continue tant que le sperateur est present
    while (token != NULL && i < MAX_NUMBER_OF_PARAMS)
    {
        strcpy(parsed[i],token);
        token = strtok(NULL, sep);
        i++;
    }
    //Insere charactere de fin de commande, 
    //Il faut d'abord libere la memoire
    free(parsed[i]);
    parsed[i] = NULL;
    return i;
}

void removeAllChars(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

int parseStringBySpaces(char* arg,char** parsed)
{
    return parseStringBySep(arg,parsed," ");
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
        //Execute expression reguliere 
        reti = regexec(&regex,parsed[i], 0, NULL, 0);
        if (!reti) 
        {
            strcpy(result[++c],parsed[i]);
            c++;
        }
        else if (reti == REG_NOMATCH) 
        {
            if(result[c] == NULL || strcmp(result[c],"") == true)
            {
                strcpy(result[c],parsed[i]);
            }
            else
            {
                //Garde espace pendant le parsing
                strcat(result[c], " ");
                strcat(result[c], parsed[i]);
            }
        }
        else 
        {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            perror(msgbuf);
        }
    }
    // Libere memoire allouee au pattern par regcomp()
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
        if(strcmp(tmp,"||") == true || strcmp(tmp,"&&") == true || tmp[0] == '>' || tmp[0] == '<')
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
    }

    while(empty(operators) == true)
    {
       addNodeStackTree(&operands,pop(&operators));
       
    }
    return peekStackTree(operands);
    
}


    


