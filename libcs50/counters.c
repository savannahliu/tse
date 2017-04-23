/*
 * counters.c - CS50 'counters' module
 *
 * based on bag.c by David Kotz, April 2016, 2017
 *
 * see counters.h for more information.
 *
 * Savannah Liu, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "counters.h"
#include "memory.h"


/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct countersnode {
  int key;            // key
  int counter;		            // pointer to data for this item
  struct countersnode *next;	// link to next node
} countersnode_t;

/**************** global types ****************/
typedef struct counters {
  struct countersnode *head;	      // head of the list of items in counters
} counters_t;


/**************** local functions ****************/
/* not visible outside this file */
static countersnode_t *countersnode_new(int key);


/*------------------------ function definitions ----------------------------*/


/**************** counters_new() ****************/
/* Create a new (empty) counter structure; return NULL if error. */
counters_t *
counters_new(void)
{
  counters_t *counters = count_malloc(sizeof(counters_t));

  if (counters == NULL) {
    return NULL; // error allocating counters_new
  } else {
    // initialize contents of counters structure
    counters->head = NULL;
    return counters;
  }
}


/**************** counters_add() ****************/
/* Increment the counter indicated by key; key must be >= 0.
 * If the key does not yet exist, create a counter for it and initialize to 1.
 * Ignore if ctrs is NULL or key is negative.
 */
void
counters_add(counters_t *ctrs, const int key)
{
  if (ctrs != NULL && key >=0) {

    // check if it already exists
    for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
      if (node->key == key){
        node->counter++;  // already exists: increment counter
        return;
      }
    }

    // it doesn't exist, so create a counter for it
    // allocate a new node to be added to the list
    countersnode_t *new = countersnode_new(key);
    if (new != NULL) {
      // add it to the head of the list
      new->next = ctrs->head;
      ctrs->head = new;
      return;
    }
  } else { // ctrs or key is NULL, or key is <0
    return;
  }

#ifdef MEMTEST
  count_report(stdout, "After counters_add");
#endif
}


/**************** countersnode_new() ****************/
/* Helper function
 * Allocates and initializes a counter node
 */
 countersnode_t *
 countersnode_new(int key){
   countersnode_t *node = count_malloc(sizeof(countersnode_t));
   if (node == NULL) {
     return NULL; // error allocating
  } else { // initialize contents of node
      node->key = key;
      node->counter = 1;
    return node;
  }
 }


/**************** counters_get() ****************/
/* Return current value of counter associated with the given key;
 * return 0 if ctrs is NULL or if key is not found.
 */
int
counters_get(counters_t *ctrs, const int key)
{
  if (ctrs == NULL || ctrs->head == NULL || key < 0){
    return 0; // counter set is null or empty, or key is negative
  } else {
    // find the key
    countersnode_t *out = ctrs->head; // take out node

    while (out != NULL){
      // if found key, return its counter
      if (out->key == key){
        return out->counter; // return the counter
      }

      // key was not found: check if next is null before going to next one
      if (out->next == NULL){
        return 0; // reached last item - there is no next node
      }
      out = out->next;
    }
  }
  return 0;
}


/**************** counters_set() ****************/
/* Set the current value of counter associated with the given key;
 * ignore if ctrs is NULL or if key is negative.
 */
void
counters_set(counters_t *ctrs, const int key, int count)
{
  if (ctrs != NULL && key > 0){
    // find the node
    for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
      if (node->key == key){
        node->counter = count;;  // already exists: increment counter
        return;
      }
    }
  }
}


/**************** counters_print() ****************/
/* Print all counters; provide the output file.
 * Ignore if NULL fp. Print (null) if NULL ctrs.
 */
void
counters_print(counters_t *ctrs, FILE *fp)
{
  if (fp != NULL) {
    if (ctrs != NULL) {
      fputc('{', fp);
      for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
        // print this node's counter
          fprintf(fp, "key: %d count: %d, " , node-> key, node->counter);
      }
      fputc('}', fp);

    } else { // NULL counter set
      fputs("(null)", fp);
    }
  }
}

/**************** counters_iterate() ****************/
/* Iterate over all counters in the set (in undefined order):
 * call itemfunc for each item, with (arg, key, count).
 * If ctrs==NULL or itemfunc==NULL, do nothing.
 */
void
counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, int count))
{
  if (ctrs != NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->key, node->counter);
    }
  }
}


/**************** counters_delete() ****************/
/* Delete the whole counters. ignore NULL ctrs. */
void
counters_delete(counters_t *ctrs)
{
  if (ctrs != NULL) {
    for (countersnode_t *node = ctrs->head; node != NULL; ) {
      countersnode_t *next = node->next;	  // remember what comes next
      count_free(node);			          // free the node
      node = next;			              // and move on to next
    }
    count_free(ctrs);
  }

#ifdef MEMTEST
  count_report(stdout, "End of counters_delete");
#endif
}
