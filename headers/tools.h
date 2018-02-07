#define _XOPEN_SOURCE 700
#ifndef _TOOLS_H_ /* L'écriture ici présente n'est pas universelle */
#define _TOOLS_H_ /* Edit suite aux corrections des posts suivants -> */

/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name);


/**
 * Procedure checks if variable must be free
 * (check: ptr != NULL)
 *
 * \param void* to_free pointer to an allocated mem
 * \see man 3 free
 * \return void
 */
void free_if_needed(void* to_free);


/**
 *
 * \see man 3 strndup
 * \see man 3 perror
 * \return
 */
char* dup_optarg_str();

#endif