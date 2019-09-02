#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "hashtable.h"


double getTime() {
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    double currentTime = time.tv_sec * 1000 + time.tv_nsec / 1000000;
    return currentTime;
}


int main() {
    for (int i=10; i<30; i++) {
        int numEntries = 2 << i;
        printf("With %d entries:\n", numEntries);
        Hashtable *ht = ht_create();

        double start = getTime();
        for (int j=0; j<numEntries; j++) {
            char key[10];
            snprintf(key, 10, "%i", i);
            char val[10];
            snprintf(val, 10, "%i", i*2);
            ht_set(ht, key, val);
        }
        printf("Insert: %.5f\n", getTime() - start);

        start = getTime();
        for (int j=0; j<numEntries; j++) {
            char key[10];
            snprintf(key, 10, "%i", i);
            char *val = ht_get(ht, key);
        }
        printf("Retrieve: %.5f\n", getTime() - start);

        start = getTime();
        for (int j=0; j<numEntries; j++) {
            char key[10];
            snprintf(key, 10, "%i", i);
            ht_delete(ht, key);
        }
        printf("Delete: %.5f\n", getTime() - start);
        ht_destroy(ht);
    }
}
