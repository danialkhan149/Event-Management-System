#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Registration.h"

class HashNode
{
public:
    string key;
    Registration value;
    HashNode *next;

    HashNode(string, Registration);
};

class HashTable
{
private:
    static const int TABLE_SIZE = 100;
    HashNode *table[TABLE_SIZE];

    int hashFunction(string);

public:
    HashTable();
    ~HashTable();

    void insert(string, Registration);
    Registration *search(string);

    void remove(string);
    void displayAll();
};

#endif