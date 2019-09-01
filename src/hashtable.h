//
// Created by Bede Kelly on 2019-08-20.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "linkedlist.h"
#define DOUBLE_SIZE 1

typedef struct {
    int maxLength;
    int numItems;
    LinkedList **table;
} Hashtable;


Hashtable *ht_create();
void ht_set(Hashtable *, char* key, char* value);
char* ht_get(Hashtable *, char* key);
void ht_delete(Hashtable *hashtable, char* key);
void ht_destroy(Hashtable *hashtable);
void ht_debug(Hashtable *hashtable);
void ht_stats(Hashtable *hashtable);

#endif //HASHTABLE_HASHTABLE_H
