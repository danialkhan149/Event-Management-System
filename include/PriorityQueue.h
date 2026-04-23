#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Registration.h"
#include <vector>

class PriorityQueue
{
private:
    vector<Registration> heap;

    int parent(int);
    int leftChild(int);
    int rightChild(int);

    void heapifyUp(int);
    void heapifyDown(int);

public:
    bool isEmpty() const;
    int size() const;

    void push(Registration);
    Registration pop();
    Registration top();

    void displayAll() const;
    void saveToFile(ofstream &);
};

#endif