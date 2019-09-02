# HashTable

A simple hashtable mapping strings to strings, written in C.

This hashtable uses separate chaining to handle hash collisions, meaning each 'bucket' is a linked list.
The linked list implementation here acts as an associative array, exposing
"get" and "set" operations.

Table Doubling keeps the load factor below 1.  The upper bound at which the table doubles is configurable by altering `DOUBLE_SIZE` in
[hashtable.h](./src/hashtable.h).

Keys and values are copied when added to the table, so altering a key *or value* after inserting into the hashtable has no effect on the table contents.
These copies are freed when the key (or the whole table) is deleted.

The hash used here is "djb2", modified from [here](http://www.cse.yorku.ca/~oz/hash.html).

### Amortized Complexity Profiling
The amortized complexity of this data structure is explored in [this Jupyter Notebook](./analysis/Hashtable%20Analysis.html). The short answer that it's O(1) for inserts, reads and deletes -- just how it's meant to be!

### Memory Leak Checking
As MacOS doesn't have a working build of Valgrind, this project includes a Dockerfile which builds the project on Ubuntu Linux and checks it for memory leaks.

(Because of this technique, the project is now leak-free!)

First, run `source build_dockerfile.sh` to build the dockerfile -- this may take some time as it needs to install CMake as well as Valgrind. Then, `source check_memory_leaks.sh` will test whether any memory leaks occur while running the `main` executable.

Note that the Dockerfile isn't built fresh every time you run `check_memory_leaks.sh` -- it mounts the current directory as a volume. Because of this, after the initial build of the Docker container, it's nearly as fast as running Valgrind natively!