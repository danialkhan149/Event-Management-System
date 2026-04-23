#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include "Registration.h"

class QueueNode
{
public:
    Registration data;
    QueueNode *next;

    QueueNode(Registration);
};

class LinkedQueue
{
private:
    QueueNode *front;
    QueueNode *rear;
    int count;

public:
    LinkedQueue();
    ~LinkedQueue();

    bool isEmpty() const;
    int size() const;

    void enqueue(Registration);

    Registration dequeue();

    void displayAll() const;
    bool removeByCNIC(string);

    void saveToFile(ofstream &);
};

#endif