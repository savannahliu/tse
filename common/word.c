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

/**************** functions ****************/

/**************** NormalizeWord() ****************/
/* convert word to lowercase */
//referenced http://stackoverflow.com/questions/23618316/undefined-reference-to-strlwr
//referenced http://stackoverflow.com/questions/2661766/c-convert-a-mixed-case-string-to-all-lower-case?noredirect=1&lq=1
char *
NormalizeWord(char *word)
{
  while (*word) {
    *word = tolower(*word);
    word++;
  }
  return word;
}
