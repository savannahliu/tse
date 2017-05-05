/*
 * word.h - header file for CS50 word module
 *
 * Countains function that normalizes words
 *
 * This module is used when building index data structure
 *
 * Savannah Liu, April 2017
 */

#ifndef __word_H
#define __word_H

#include <stdio.h>
#include <stdbool.h>

/**************** functions ****************/

/* convert word to lowercase */
bool NormalizeWord(char **word);

#endif // __word_H
