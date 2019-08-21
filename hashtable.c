#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"


Hashtable *ht_create_with_size(int maxLength);

Hashtable *ht_create() {
    return ht_create_with_size(2);
}

Hashtable *ht_create_with_size(int maxLength) {
    Hashtable *ht = malloc(sizeof(Hashtable));
    ht->maxLength = maxLength;
    ht->table = malloc(sizeof(LinkedList *) * ht->maxLength);
    ht->numItems = 0;

    for (int i=0; i<ht->maxLength; i++) {
        ht->table[i] = ll_create();
    }

    return ht;
}


int hash(key, maxLength) {
    return key % maxLength;
}


void ht_set(Hashtable *hashtable, int key, int value) {
    int hashedKey = hash(key, hashtable->maxLength);
    LinkedList *list = hashtable->table[hashedKey];
    ll_set(list, key, value);
    hashtable->numItems++;

    // If we've reached the threshold of doubling our table size:
    if (hashtable->numItems > DOUBLE_SIZE * hashtable->maxLength) {
        int oldLength = hashtable->maxLength;
        int newLength = hashtable->maxLength * 2;

        // Create an array of linked lists double the size of the last one.
        LinkedList **oldTable = hashtable->table;
        LinkedList **newTable = malloc(sizeof(LinkedList *) * newLength);
        for (int i=0; i<newLength; i++) {
            newTable[i] = ll_create();
        }

        // Set the hashtable's values to the new table and size.
        hashtable->table = newTable;
        hashtable->maxLength = newLength;

        // Rehash all linked list items
        for (int i=0; i<oldLength; i++) {
            LinkedList *chain = oldTable[i];

            // For each item in chain, rehash and add to linkedLists.
            for (LinkedListNode *this=chain->first; this != NULL; this=this->next) {
                ht_set(hashtable, this->key, this->data);
            }
        }

        // Destroy each old linked list.
        for (int i=0; i<oldLength; i++) {
            ll_destroy(oldTable[i]);
        }

        // Destroy the old table.
        free(oldTable);
    }
}


int ht_get(Hashtable *hashtable, int key) {
    int hashedKey = hash(key, hashtable->maxLength);
    LinkedList *list = hashtable->table[hashedKey];
    return ll_get(list, key);
}


void ht_debug(Hashtable *hashtable) {
    printf("[%d/%d] ", hashtable->numItems, hashtable->maxLength);
    for (int i=0; i<hashtable->maxLength; i++) {
        printf("%d; ", hashtable->table[i]->size);
    }
    printf("\n");
}


void ht_delete(Hashtable *hashtable, int key) {
    int hashedKey = hash(key, hashtable->maxLength);
    LinkedList *list = hashtable->table[hashedKey];
    ll_delete(list, key);
}