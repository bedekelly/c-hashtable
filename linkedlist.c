#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"


LinkedList *ll_create() {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->first = NULL;
    list->size = 0;
    return list;
}

void ll_add(LinkedList *list, int key, int data) {

    LinkedListNode *nextItem = malloc(sizeof(LinkedListNode));
    nextItem->key = key;
    nextItem->data = data;
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

void ll_set(LinkedList *list, int key, int data) {
    if (list->first) {
        LinkedListNode *this = list->first;
        do {
            if (this->key == key) {
                this->data = data;
                return;
            }
            if (this->next) this = this->next;
        } while (this->next);

        LinkedListNode *nextItem = malloc(sizeof(LinkedListNode));
        nextItem->key = key;
        nextItem->data = data;
        nextItem->next = NULL;
        this->next = nextItem;
    } else {
        LinkedListNode *nextItem = malloc(sizeof(LinkedListNode));
        nextItem->key = key;
        nextItem->data = data;
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

void ll_delete(LinkedList *list, int key) {
    if (!list->first) return;
    list->size--;

    // Delete the first element of the linked list.
    if (list->first->key == key) {
        LinkedListNode *newFirst;
        if (list->first->next) {
            newFirst = list->first->next;
        } else {
            newFirst = NULL;
        }
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
        free(this);
        this = next;
    }
    free(list);
}

int ll_get(LinkedList *list, int key) {
    for (LinkedListNode *node = list->first; node != NULL; node=node->next) {
        printf("LinkedList Check\n");
        if (node->key == key) {
            return node->data;
        }
    }
    printf("Error in ll_get: key %d not found.\n", key);
    return -1;
}
