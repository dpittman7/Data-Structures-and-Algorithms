#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <utility>
#include <string>
#include <fstream>
#include <string>
#include <iostream>

// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 101;

namespace cop4530 {

    template<typename K, typename V>
    class HashTable {

    public:

        HashTable(size_t size = default_capacity); // default zero parameter constructor
        ~HashTable();  // destructor


        bool contains(const K &k); //check if key k is in the hash table.
        bool match(const std::pair<K, V> &kv); //check if key-value pair is in the hash table.
        bool insert(const std::pair<K, V> &kv); //add keyvalue pair into hash. //took off const
        //dont add if already present.
        //update if key is present.

        bool insert(const std::pair<K, V> &&kv); //move version of insert
        bool remove(const K &k); //delete key
        void clear(); // delete all elements in the hashtable
        bool load(const char *filename); //load contents of file into hashtable.
        void dump(); // display all entries in hashtable. Seperate each same instance with ;
        bool write_to_file(const char *filename); //write all elements into file.
        size_t getSize();


    private:
        // private helper functions
        void makeEmpty(); //delete all elements in hashtable.
        void rehash(); //Rehash function. Called when number of elements
        //is greater than the size of vector.
        size_t myhash(const K &k); //return the index of the vector entry where k should be stored.
        unsigned long prime_below(unsigned long); //
        void setPrimes(std::vector<unsigned long> &);

        //private data members
        std::vector<std::list<std::pair<K, V> > > hashtable;
        int hashsize;
        int totalelements;
        // The hashtable will be a vector of list objects that will
        //store a series of paired Key, Value Pairs of type K,V.

    };

}
#include "hashtable.hpp"


// end of namespace 4530
 
#endif
