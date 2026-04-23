#ifndef EMS_H
#define EMS_H

#include "LinkedQueue.h"
#include "PriorityQueue.h"
#include "LinkedStack.h"
#include "EventBST.h"
#include "HashTable.h"
#include "Graph.h"

class EventManagementSystem
{
private:
    LinkedQueue pendingQueue;
    PriorityQueue urgentQueue;
    LinkedStack verifiedStack;
    EventBST eventTree;
    HashTable userDirectory;
    Graph network;

    void initializeSystem();

public:
    EventManagementSystem();
    void loadAllData();
    void saveAllData();

    void generateReport();
    void deleteEvent();
    void createEvent();
    void updateEvent();

    void registerUser(bool);
    void deleteParticipant();
    void updateParticipant();

    void adminPanel();
    void graphMenu();

    void run();
};

#endif