FROM ubuntu
RUN apt-get update && apt-get upgrade -y && apt-get install build-essential cmake valgrind -y
WORKDIR /var/tmp/hashtable/build
CMD cmake ../src/ && make && valgrind --leak-check=yes ./HashTable