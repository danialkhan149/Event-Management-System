#include "LinkedQueue.h"
#include "iostream"
using namespace std;

QueueNode::QueueNode(Registration r)
{
    data = r;
    next = nullptr;
}

LinkedQueue::LinkedQueue()
{
    front = nullptr;
    rear = nullptr;
    count = 0;
}

LinkedQueue::~LinkedQueue()
{
    while (front != nullptr)
    {
        QueueNode *temp = front;
        front = front->next;
        delete temp;
    }
}

bool LinkedQueue::isEmpty() const
{
    return front == nullptr;
}

int LinkedQueue::size() const
{
    return count;
}

void LinkedQueue::enqueue(Registration r)
{
    QueueNode *newNode = new QueueNode(r);
    if (isEmpty())
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    count++;
}

Registration LinkedQueue::dequeue()
{
    if (isEmpty())
    {
        throw runtime_error("Cannot dequeue from empty queue!");
    }

    QueueNode *temp = front;
    Registration r = temp->data;

    front = front->next;
    if (front == nullptr)
    {
        rear = nullptr;
    }

    delete temp;
    count--;
    return r;
}

void LinkedQueue::displayAll() const
{
    if (isEmpty())
    {
        cout << "\nQueue is empty.\n";
        return;
    }

    cout << "\n\t\t<========== PENDING REGISTRATIONS ==========>\n";
    cout << left << setw(17) << "Name"
         << setw(15) << "CNIC"
         << setw(22) << "Event"
         << setw(12) << "Fee"
         << setw(12) << "Status";
    cout << "\n-------------------------------------------------------------------------\n";

    QueueNode *temp = front;
    while (temp != nullptr)
    {
        temp->data.displayTableRow();
        temp = temp->next;
    }
}

bool LinkedQueue::removeByCNIC(string cnic)
{
    if (isEmpty())
        return false;

    if (front->data.getParticipant() == cnic)
    {
        dequeue();
        return true;
    }

    QueueNode *current = front->next;
    QueueNode *previous = front;

    while (current != nullptr)
    {
        if (current->data.getParticipant() == cnic)
        {

            previous->next = current->next;

            if (current == rear)
            {
                rear = previous;
            }

            delete current;
            count--;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

void LinkedQueue::saveToFile(ofstream &outFile)
{
    QueueNode *temp = front;
    while (temp != nullptr)
    {
        outFile << temp->data;
        temp = temp->next;
    }
}
