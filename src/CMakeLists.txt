project(HashTable C)

set(CMAKE_C_STANDARD 11)

add_executable(HashTable main.c hashtable.h linkedlist.h hashtable.c linkedlist.c)
