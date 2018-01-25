#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <string.h>
#include<errno.h>
#include<getopt.h>
#include<fcntl.h>

typedef enum { true,false } bool;

#define STDOUT 1
#define STDERR 2

/**
 * Structure for Trees
 */
typedef struct node
{
    char* value;
    struct node* root;
    struct node** childs;
}node;


#endif