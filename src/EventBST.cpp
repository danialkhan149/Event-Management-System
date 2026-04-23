#include "EventBST.h"
#include "iostream"
using namespace std;

BSTNode::BSTNode(Event e)
{
    data = e;
    left = nullptr;
    right = nullptr;
}

BSTNode *EventBST::insertRecursive(BSTNode *node, Event e)
{
    if (node == nullptr)
        return new BSTNode(e);
    if (e < node->data)
        node->left = insertRecursive(node->left, e);
    else if (e > node->data)
        node->right = insertRecursive(node->right, e);
    return node;
}

BSTNode *EventBST::searchRecursive(BSTNode *node, int id)
{
    if (node == nullptr || node->data == id)
        return node;
    if (id < node->data.getEventID())
        return searchRecursive(node->left, id);
    return searchRecursive(node->right, id);
}

BSTNode *EventBST::findMin(BSTNode *node)
{
    while (node->left != nullptr)
        node = node->left;
    return node;
}

BSTNode *EventBST::deleteRecursive(BSTNode *node, int id)
{
    if (node == nullptr)
        return node;

    if (id < node->data.getEventID())
    {
        node->left = deleteRecursive(node->left, id);
    }
    else if (id > node->data.getEventID())
    {
        node->right = deleteRecursive(node->right, id);
    }
    else
    {

        if (node->left == nullptr)
        {
            BSTNode *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            BSTNode *temp = node->left;
            delete node;
            return temp;
        }

        BSTNode *temp = findMin(node->right);
        node->data = temp->data;
        node->right = deleteRecursive(node->right, temp->data.getEventID());
    }
    return node;
}

void EventBST::inorderDisplay(BSTNode *node) const
{
    if (node != nullptr)
    {
        inorderDisplay(node->left);
        node->data.displayTableRow();
        inorderDisplay(node->right);
    }
}

void EventBST::saveRecursive(BSTNode *node, ofstream &outFile)
{
    if (node != nullptr)
    {
        saveRecursive(node->left, outFile);
        outFile << node->data;
        saveRecursive(node->right, outFile);
    }
}

void EventBST::deleteTree(BSTNode *node)
{
    if (node != nullptr)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

BSTNode *EventBST::searchByNameRecursive(BSTNode *node, string name)
{
    if (node == nullptr)
        return nullptr;

    if (node->data.getEventName() == name)
    {
        return node;
    }

    BSTNode *leftResult = searchByNameRecursive(node->left, name);
    if (leftResult != nullptr)
        return leftResult;

    return searchByNameRecursive(node->right, name);
}

EventBST::EventBST()
{
    root = nullptr;
}
EventBST::~EventBST()
{
    deleteTree(root);
}

void EventBST::insert(Event e)
{
    root = insertRecursive(root, e);
}

Event *EventBST::search(int id)
{
    BSTNode *result = searchRecursive(root, id);
    return result ? &(result->data) : nullptr;
}

void EventBST::remove(int id)
{
    root = deleteRecursive(root, id);
}

void EventBST::displayAll() const
{
    if (root == nullptr)
    {
        cout << "No events.\n";
        return;
    }
    cout << "\n\t\t<========== AVAILABLE EVENTS ==========>\n";
    cout << left << setw(8) << "ID" << setw(25) << "Name" << setw(15) << "Module" << setw(15) << "Reg Fee" << setw(15) << "Seats";
    cout << "\n---------------------------------------------------------------------" << "\n";
    inorderDisplay(root);
}

void EventBST::populateVector(BSTNode *node, vector<Event> &list)
{
    if (!node)
        return;
    populateVector(node->left, list);
    list.push_back(node->data);
    populateVector(node->right, list);
}

vector<Event> EventBST::getFlatList()
{
    vector<Event> list;
    populateVector(root, list);
    return list;
}

void EventBST::saveToFile(ofstream &outFile) { 
    saveRecursive(root, outFile); 
}

bool EventBST::isEmpty() { 
    return root == nullptr; 
}

Event *EventBST::searchByName(string name)
{
    BSTNode *result = searchByNameRecursive(root, name);
    return result ? &(result->data) : nullptr;
}