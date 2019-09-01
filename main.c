#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hashtable.h"


int main() {
    Hashtable *ht = ht_create();

    for (int i=0; i<10000000; i++) {
        char key[10];
        snprintf(key, 10, "%i", i);
        char val[10];
        snprintf(val, 10, "%i", i*2);
        ht_set(ht, key, val);
    }

    ht_stats(ht);

    for (int i=0; i<10000000; i++) {
        char key[10];
        snprintf(key, 10, "%i", i);
        char val[10];
        snprintf(val, 10, "%i", i*2);
        char *result = ht_get(ht, key);
        if (strcmp(result, val) != 0) {
            printf("%s != %s\n", result, val);
        }
        assert(strcmp(result, val) == 0);
    }

    printf("%s\n", ht_get(ht, "902351"));
}
