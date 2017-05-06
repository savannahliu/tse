/*
 * pagedir.h - header file for CS50 pagedir module
 *
 * Contains all logic for saving pages to crawler output directory
 * and for loading pages from crawler output directory.
 *
 * This module is used by the crawler and the indexer.
 *
 * Savannah Liu, April 2017
 */

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include "webpage.h" // webpage_t

/**************** functions ****************/

/* Check if given directory was produced by the crawler. */
bool isCrawlerDirectory(char *dir);

/* Gives file, checks to see if readable */
FILE *pageloader(char *file);

/* Save pages into crawler output directory
 * Used in crawler
 */
void pagesaver(webpage_t *page, int id, char *pageDirectory);

#endif // __PAGEDIR_H
