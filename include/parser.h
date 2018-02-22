/**
 * \file parsr.h
 * \brief Gestion du Shell
 * \author Loïc B.
 *
 *  Gestion du Shell et de l'IHM
 *
 */
#ifndef _PARSER_H_
#define _PARSER_H_ 

#include "typedef.h"

/**
 * \fn void parseStringBySpaces(char* arg,char** parsed)
 * \brief Découpe la chaîne par caractère espace
 *
 * \return argc
 */
int parseStringBySpaces(char* arg,char** parsed);

/**
 * \fn int parseStringBySpecialChars(char** parsed,char** result,int size)
 * \brief Découpe la chaîne par caractère special
 *
 * \return argc
 */
int parseStringBySpecialChars(char** parsed,char** result,int size);

#endif
