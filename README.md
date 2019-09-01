# HashTable

A simple hashtable mapping strings to strings, written in C.

This implements table doubling to keep reads and writes at O(1). The rate
at which the table doubles is configurable by altering `DOUBLE_SIZE` in
[hashtable.h](./hashtable.h).

Keys and values are copied when added to the table, and these copies are freed when the value (or the whole table) is deleted.

The hash used here is "djb2", modified from [here](http://www.cse.yorku.ca/~oz/hash.html).

### Memory Leak Checking
As MacOS doesn't have a working build of Valgrind, this project includes a Dockerfile which builds the project on Ubuntu Linux and checks it for memory leaks.

(Because of this technique, the project is now leak-free!)

First, run `source build_dockerfile.sh` to build the dockerfile -- this may take some time as it needs to install CMake as well as Valgrind. Then, `source check_memory_leaks.sh` will test whether any memory leaks occur while running the `main` executable.

Note that the Dockerfile isn't built fresh every time you run `check_memory_leaks.sh` -- it mounts the current directory as a volume. Because of this, after the initial build of the Docker container, it's nearly as fast as running Valgrind natively!