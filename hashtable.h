//
// Created by Bede Kelly on 2019-08-20.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "linkedlist.h"
#define DOUBLE_SIZE 5

typedef struct {
    int maxLength;
    int numItems;
    LinkedList **table;
} Hashtable;


Hashtable *ht_create();
void ht_set(Hashtable *, int key, int value);
int ht_get(Hashtable *, int key);
void ht_delete(Hashtable *hashtable, int key);
void ht_debug(Hashtable *hashtable);

#endif //HASHTABLE_HASHTABLE_H
