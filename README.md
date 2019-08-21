# HashTable

A simple hashtable mapping integers to integers, written in C.

This implements table doubling to keep reads and writes at O(1). The rate
at which the table doubles is configurable by altering `DOUBLE_SIZE` in
[hashtable.h](./hashtable.h).