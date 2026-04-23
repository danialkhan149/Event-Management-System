#ifndef EVENTBST_H
#define EVENTBST_H

#include "Event.h"
#include <vector>

class BSTNode
{
public:
    Event data;
    BSTNode *left;
    BSTNode *right;

    BSTNode(Event);
};

class EventBST
{
private:
    BSTNode *root;

    BSTNode *insertRecursive(BSTNode *, Event);
    BSTNode *searchRecursive(BSTNode *, int);

    BSTNode *findMin(BSTNode *);

    BSTNode *deleteRecursive(BSTNode *, int);
    void inorderDisplay(BSTNode *) const;

    void saveRecursive(BSTNode *, ofstream &);

    void deleteTree(BSTNode *);
    BSTNode *searchByNameRecursive(BSTNode *, string);

public:
    EventBST();
    ~EventBST();

    void insert(Event);

    Event *search(int);
    void remove(int);

    void displayAll() const;
    void populateVector(BSTNode *, vector<Event> &);
    vector<Event> getFlatList();

    void saveToFile(ofstream &);

    bool isEmpty();

    Event *searchByName(string);
};

#endif