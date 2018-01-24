#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <string.h>

typedef struct node
{
    char* value;
    struct node* pere;
    struct node** fils;
}node;


#endif