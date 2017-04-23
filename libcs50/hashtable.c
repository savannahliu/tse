/*
 * hashtable.c - CS50 'hashtable' module
 *
 * based on bag.c by David Kotz, April 2016, 2017
 * makes use of set module
 * makes use of jhash.h (given as part of starter kit)
 *
 * see hashtable.h for more information.
 * Savannah Liu, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashtable.h"
#include "set.h"
#include "jhash.h"
#include "memory.h"


/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

/**************** global types ****************/
typedef struct hashtable {
  set_t **array;
  int num_slots;
} hashtable_t;

/**************** local functions ****************/
/* not visible outside this file */

/*------------------------ function definitions ----------------------------*/

/* Create a new (empty) hashtable; return NULL if error.
* allocating array of pointers http://www.cs.dartmouth.edu/~cs50/Labs/Lab3/array-allocate.html
*/
hashtable_t *
hashtable_new(const int num_slots)
{
  hashtable_t *ht = count_malloc(sizeof(hashtable_t));

  if (ht == NULL) { // error allocating
    return NULL;
  } else {// initialize contents of hashtable structure

    ht->num_slots = num_slots;

    set_t **array = count_calloc(num_slots, sizeof(set_t*));     // declare array


    for(int i = 0; i < num_slots; i++){ // for each slot in array, add a new empty set
      array[i] = set_new(); // point to the set
    }

    ht->array = array; // add the array to the hashtable
    return ht;
  }

}

/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool
hashtable_insert(hashtable_t *ht, const char *key, void *item)
{
  if (ht != NULL && item != NULL && key != NULL) {

    unsigned long index = JenkinsHash(key, ht->num_slots);

    // see if key already exists
    set_t **array = ht->array;
    set_t *set = array[index];

    // try to insert the item
    if (set_insert(set, key, item) == true){
      return true;
    } else { // it already exists
      return false;
    }

  } else { // a parameter is null
    return false;
  }
}

/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
void *
hashtable_find(hashtable_t *ht, const char *key)
{
  if (ht != NULL && key != NULL) {
  unsigned long index = JenkinsHash(key, ht->num_slots);
  set_t **array = ht->array;
  return set_find(array[index], key);

  } else {
    return NULL; // hashtable or key is null
  }
}

/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.
 */
void
hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item))
{
  if (ht != NULL && fp != NULL) {
    set_t **array = ht->array;
    for (int i=0; i < ht->num_slots; i++){
      set_print(array[i], fp, itemprint);
    }
    // loop through the array
      // set_print(set, fp, itemprint);
  } else if (ht == NULL){
    printf("null\n");
  }
}


/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void
hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) )
{
  if (ht != NULL && itemfunc != NULL) {
    set_t **array = ht->array;
    for (int i=0; i < ht->num_slots; i++){
      set_iterate(array[i], arg, itemfunc);
    }
  }
}

/* Delete the whole hashtable; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void
hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) )
{
  if (ht != NULL) {
    set_t **array = ht->array;
    for (int i=0; i < ht->num_slots; i++){
      set_delete(array[i], itemdelete);
    }

    count_free(ht->array); 
    count_free(ht);

  }
  #ifdef MEMTEST
    count_report(stdout, "End of ht_delete");
  #endif
}
