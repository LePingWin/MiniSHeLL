#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <string.h>
#include<string.h>
#include<errno.h>
#include<getopt.h>
#include<fcntl.h>

/**
 * Binary options declaration
 * (must end with {0,0,0,0})
 *
 * \see man 3 getopt_long or getopt
 * \see struct option definition
 */
static struct option binary_opts[] = 
{
  { "help",    no_argument,       0, 'h' },
  { "verbose", no_argument,       0, 'v' },
  { "input",   required_argument, 0, 'i' },
  { "output",  required_argument, 0, 'o' },
  { 0,         0,                 0,  0  } 
};

/**
 * Binary options string
 * (linked to optionn declaration)
 *
 * \see man 3 getopt_long or getopt
 */ 
const char* binary_optstr = "hvi:o:";


typedef struct node
{
    char* value;
    struct node* pere;
    struct node** fils;
}node;


#endif