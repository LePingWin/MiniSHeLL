#include <stdlib.h>
#include <stdio.h>
#include "../include/typedef.h"
#include <string.h>
#include <regex.h>    

const char* special_chars = "^[&|><]+";

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
    int reti;
    char msgbuf[100]; 

    /* Compile regular expression */
    reti = regcomp(&regex, special_chars, 0);
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
            strcat(result[c], parsed[i]);
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

    


