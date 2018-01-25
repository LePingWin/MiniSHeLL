#include"tools.h"



#define STDOUT 1
#define STDERR 2

#define MAX_PATH_LENGTH 4096


#define USAGE_SYNTAX "[OPTIONS] -i INPUT -o OUTPUT"
#define USAGE_PARAMS "OPTIONS:\n\
  -i, --input  INPUT_FILE  : input file\n\
  -o, --output OUTPUT_FILE : output file\n\
***\n\
  -v, --verbose : enable *verbose* mode\n\
  -h, --help    : display this help\n\
"

/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name)
{
  dprintf(1, "USAGE: %s %s\n\n%s\n", bin_name, USAGE_SYNTAX, USAGE_PARAMS);
}


/**
 * Procedure checks if variable must be free
 * (check: ptr != NULL)
 *
 * \param void* to_free pointer to an allocated mem
 * \see man 3 free
 * \return void
 */
void free_if_needed(void* to_free)
{
  if (to_free != NULL) free(to_free);  
}


/**
 *
 * \see man 3 strndup
 * \see man 3 perror
 * \return
 */
char* dup_optarg_str()
{
  char* str = NULL;

  if (optarg != NULL)
  {
    str = strndup(optarg, MAX_PATH_LENGTH);
    
    // Checking if ERRNO is set
    if (str == NULL) 
      perror(strerror(errno));
  }

  return str;
}
