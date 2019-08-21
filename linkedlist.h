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
    int key;
    int data;
    struct LinkedListNode *next;
} LinkedListNode;

void ll_add(LinkedList *, int key, int data);
void ll_delete(LinkedList *, int key);
int ll_get(LinkedList *, int key);
void ll_set(LinkedList *list, int key, int data);

LinkedList *ll_create();
void ll_destroy(LinkedList *);

typedef void (*LinkedListIterator)(LinkedListNode*);
void ll_foreach(LinkedList*, LinkedListIterator);

#endif //HASHTABLE_LINKEDLIST_H
