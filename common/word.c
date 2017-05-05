/*
 * word.c - header file for CS50 word module
 *
 * see word.h for more information.
 *
 * Savannah Liu, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "word.h"
#include "memory.h"

/**************** functions ****************/

/**************** NormalizeWord() ****************/
/* convert word to lowercase
* caller is responsible for freeing the string
* referenced http://stackoverflow.com/questions/12337570/tolower-function-problems
*/
char *
NormalizeWord(char *word)
{
  size_t length = strlen(word);
  char *result = count_malloc(sizeof(char *) * length + 1); // include room for newline
  for(int i = 0 ; i < length ; i++) {
    result[i]=tolower(word[i]);
  }
  result[length] = '\0';
  return result;
}
