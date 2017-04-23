/*
 * set.c - CS50 'set' module
 *
 * based on bag.c by David Kotz, April 2016, 2017
 *
 * see set.h for more information.
 *
 * Savannah Liu, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"
#include "memory.h"



/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct setnode {
  const char *key;            // key
  void *item;		              // pointer to data for this item
  struct setnode *next;	      // link to next node
} setnode_t;

/**************** global types ****************/
typedef struct set {
  struct setnode *head;	      // head of the list of items in set
} set_t;


/**************** local functions ****************/
/* not visible outside this file */
static setnode_t *setnode_new(const char *key, void *item);


/*------------------------ function definitions ----------------------------*/


/**************** set_new() ****************/
/* Create a new (empty) set; return NULL if error. */
set_t *
set_new(void)
{
  set_t *set = count_malloc(sizeof(set_t));

  if (set == NULL) {
    return NULL; // error allocating set_new
  } else {
    // initialize contents of set structure
    set->head = NULL;
    return set;
  }

}


/**************** set_insert() ****************/
bool
set_insert(set_t *set, const char *key, void *item)
{
  if (set != NULL && item != NULL && key != NULL) {

    // code for copying a string:
    // http://stackoverflow.com/questions/18916432/malloc-a-string-array-c
    char *keycopy;
    keycopy = (char *)count_malloc(strlen(key)+1 * sizeof(const char));
    strcpy(keycopy, key);


    if (set_find(set, keycopy) != NULL){ // check if it already exists

        return false; // key already exists
    }

    // allocate a new node to be added to the list
    setnode_t *new = setnode_new(keycopy, item);

    if (new != NULL) {
      // add it to the head of the list
      new->next = set->head;
      set->head = new;

      return true;
    }
  }
  else { // set or the item is NULL
    return false;
  }

#ifdef MEMTEST
  count_report(stdout, "After set_insert");
#endif

  return 0;
}

/**************** setnode_new() ****************/
/* Helper function used in set_insert()
 * Allocate and initialize a setnode
 */
static setnode_t*
setnode_new(const char* key, void* item)
{
  setnode_t* node = count_malloc(sizeof(setnode_t));

  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;

  } else {
    node->key = key;
    node->item = item;
    node->next = NULL;

    return node;
  }
}

/**************** set_find() ****************/
void *
set_find(set_t *set, const char *key)
{
  if (set == NULL) {
    return NULL; // bad set
  } else if (set->head == NULL) {
    return NULL; // set is empty
  } else if (key == NULL){
    return NULL; // key is NULL
  } else {
    // find the specific key
    setnode_t *out = set->head; // take node out

    while (out != NULL){
      // if found key, return it
      // compare strings http://stackoverflow.com/questions/14232990/comparing-two-strings-in-c
      if (strcmp(out->key, key) == 0) { // strings are equal

        void *foundItem = out->item; // the item to return
        return foundItem;
      }

      // key was not found: check if next is null before going to next one
      if (out->next == NULL){
        return NULL; // reached last item - there is no next node
      }
      out = out->next;
    }
  }

  return 0;
}



/**************** set_print() ****************/
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item) )
{
  if (fp != NULL) {
    if (set != NULL) {
      fputc('{', fp);
      for (setnode_t *node = set->head; node != NULL; node = node->next) {
        // print this node
        if (itemprint != NULL) {  // print the node's item
          (*itemprint)(fp, node->key, node->item);
          fputc(',', fp);
        } else { // NULL itemprint
          fputc('{',fp);
          putc('}',fp);
        }
      }
      fputc('}', fp);
    } else { // NULL set
      fputs("(null)", fp);
    }
  }
}



/**************** set_iterate() ****************/
void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) )
{
  if (set != NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->key, node->item);
    }
  }
}


/**************** set_delete() ****************/
void set_delete(set_t *set, void (*itemdelete)(void *item) )
{
  if (set != NULL) {
    for (setnode_t *node = set->head; node != NULL; ) {
      if (itemdelete != NULL) {		    // if possible...
        (*itemdelete)(node->item);	  // delete node's item
        //node->key = NULL;             // delete key -- delete correctly?
      }

      setnode_t *next = node->next;	  // remember what comes next
      count_free((char*)node->key);   // need to cast to non-const http://stackoverflow.com/questions/2819535/unable-to-free-const-pointers-in-c
      count_free(node);			          // free the node
      node = next;			              // and move on to next
    }

    count_free(set);
  }

#ifdef MEMTEST
  count_report(stdout, "End of set_delete");
#endif
}
