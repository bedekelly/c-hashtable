#include <stdio.h>
#include "linkedlist.h"
#include "hashtable.h"


void printNode(LinkedListNode *node) {
    printf("%d: %d\n", node->key, node->data);
}


int main() {
    Hashtable *ht = ht_create();
    for (int i=0; i<10000; i++) {
        ht_set(ht, i, i*10);
    }

    printf("%d\n", ht_get(ht, 2));
    ht_delete(ht, 2);
    printf("%d\n", ht_get(ht, 2));
}
