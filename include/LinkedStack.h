#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "LinkedQueue.h"

class LinkedStack
{
private:
    QueueNode *top;
    int count;

public:
    LinkedStack();
    ~LinkedStack();

    bool isEmpty() const;
    int size() const;

    void push(Registration);
    Registration pop();

    bool removeByCNIC(string);
    double calculateTotalRevenue();

    void displayAll() const;

    void saveToFile(ofstream &);
};

#endif