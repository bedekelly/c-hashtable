//
// Created by Bede Kelly on 2019-08-20.
//

#ifndef HASHTABLE_LINKEDLIST_H
#define HASHTABLE_LINKEDLIST_H


typedef struct {
    int size;
    struct LinkedListNode *first;
} LinkedList;


typedef struct LinkedListNode {
    char* key;
    char* data;
    struct LinkedListNode *next;
} LinkedListNode;


void ll_add(LinkedList *, char* key, char* data);
void ll_delete(LinkedList *, char* key);
char* ll_get(LinkedList *, char* key);
void ll_set(LinkedList *list, char* key, char* data);

LinkedList *ll_create();
void ll_destroy(LinkedList *);

typedef void (*LinkedListIterator)(LinkedListNode*);
void ll_foreach(LinkedList*, LinkedListIterator);

#endif //HASHTABLE_LINKEDLIST_H
