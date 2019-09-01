#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"


LinkedList *ll_create() {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->first = NULL;
    list->size = 0;
    return list;
}


void ll_add(LinkedList *list, char* key, char* data) {

    LinkedListNode *nextItem = malloc(sizeof(LinkedListNode));

    // Key and data are both copied.
    char* keyCopy = strdup(key);
    char* dataCopy = strdup(data);

    nextItem->key = keyCopy;
    nextItem->data = dataCopy;
    nextItem->next = NULL;

    if (list->first) {
        LinkedListNode *this = list->first;
        while (this->next) {
            this = this->next;
        }
        this->next = nextItem;
    } else {
        list->first = nextItem;
    }

    list->size++;
}


void ll_set(LinkedList *list, char* key, char* data) {
    // Copy the new data regardless of where in the list it's inserted.
    char* dataCopy = strdup(data);

    // Check if we've got a list already present to append the data to.
    if (list->first) {
        LinkedListNode *this = list->first;

        // Loop through to find an instance of the current key
        do {
            if (strcmp(this->key, key) == 0) {
                this->data = dataCopy;
                return;
            }
            if (this->next) this = this->next;
        } while (this->next);

        // If we can't find the key, create a new node!
        LinkedListNode *nextItem = malloc(sizeof(LinkedListNode));
        char* keyCopy = strdup(key);
        nextItem->key = keyCopy;
        nextItem->data = dataCopy;
        nextItem->next = NULL;
        this->next = nextItem;
    } else {
        // We're creating a new first node of our linked list.
        LinkedListNode *nextItem = malloc(sizeof(LinkedListNode));
        char* keyCopy = strdup(key);
        nextItem->key = keyCopy;
        nextItem->data = dataCopy;
        nextItem->next = NULL;
        list->first = nextItem;
    }

    list->size++;
}


void ll_foreach(LinkedList *list, LinkedListIterator callback) {
    LinkedListNode *this = list->first;
    while (this) {
        callback(this);
        this = this->next;
    }
}


void ll_delete(LinkedList *list, char* key) {
    if (!list->first) return;
    list->size--;

    // Delete the first element of the linked list.
    if (strcmp(list->first->key, key) == 0) {
        LinkedListNode *newFirst;
        if (list->first->next) {
            newFirst = list->first->next;
        } else {
            newFirst = NULL;
        }
        free(list->first->data);
        free(list->first->key);
        free(list->first);
        list->first = newFirst;
        return;
    }

    // Delete an arbitrary element of the linked list.
    LinkedListNode *prev = list->first;
    LinkedListNode *this = list->first->next;
    while (this) {
        if (this->key == key) {
            prev->next = this->next;
            free(this->key);
            free(this->data);
            free(this);
            break;
        }
        prev = this;
        this = this->next;
    }
}


void ll_destroy(LinkedList *list) {
    LinkedListNode *this = list->first;
    LinkedListNode *next;
    while(this) {
        next = this->next;
        free(this->key);
        free(this->data);
        free(this);
        this = next;
    }
    free(list);
}


char* ll_get(LinkedList *list, char* key) {
    for (LinkedListNode *node = list->first; node != NULL; node=node->next) {
        if (strcmp(node->key, key) == 0) {
            return node->data;
        }
    }
    printf("Error in ll_get: key %s not found.\n", key);
    return NULL;
}
