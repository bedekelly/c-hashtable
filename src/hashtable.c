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


unsigned int hash(char* key, int maxLength) {
    unsigned long hash = 5381;
    unsigned int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;

    return hash % maxLength;
}


void ht_set(Hashtable *hashtable, char* key, char* value) {
    int hashedKey = hash(key, hashtable->maxLength);
    LinkedList *list = hashtable->table[hashedKey];
    int itemsInBucketAlready = list->size;
    ll_set(list, key, value);
    hashtable->numItems += list->size - itemsInBucketAlready;

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
        hashtable->numItems = 0;
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


char* ht_get(Hashtable *hashtable, char* key) {
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


void ht_stats(Hashtable *hashtable) {
    int tableSize = hashtable->maxLength;
    int numItems = hashtable->numItems;
    printf("Number of items: %d\n", numItems);

    double loadFactor = (float) numItems / (float) tableSize;
    printf("Load factor: %.3f\n", loadFactor);

    double totalItems = 0;
    for (int i=0; i<hashtable->maxLength; i++) {
        totalItems += hashtable->table[i]->size;
    }

    char *totalItemsMatches = totalItems == numItems ? "yes" : "no";
    printf("Total number of items matches sum of list sizes: %s\n", totalItemsMatches);
    double averageLoad = (float) totalItems / (float) hashtable->maxLength;
    printf("Average load of a bucket: %.3f\n", averageLoad);
}

void ht_delete(Hashtable *hashtable, char* key) {
    int hashedKey = hash(key, hashtable->maxLength);
    LinkedList *list = hashtable->table[hashedKey];
    ll_delete(list, key);
}

void ht_destroy(Hashtable *hashtable) {
    // Destroy every linked list.
    for (int i=0; i<hashtable->maxLength; i++) {
        ll_destroy(hashtable->table[i]);
    }
    free(hashtable->table);
    free(hashtable);
}