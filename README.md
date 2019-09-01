# HashTable

A simple hashtable mapping strings to strings, written in C.

This implements table doubling to keep reads and writes at O(1). The rate
at which the table doubles is configurable by altering `DOUBLE_SIZE` in
[hashtable.h](./hashtable.h).

Keys and values are copied when added to the table, and these copies are freed when the value (or the whole table) is deleted.

The hash used here is "djb2", modified from [here](http://www.cse.yorku.ca/~oz/hash.html).