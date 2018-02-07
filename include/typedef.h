#ifndef TYPEDEF_H
#define TYPEDEF_H

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