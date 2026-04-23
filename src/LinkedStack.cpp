#include "LinkedStack.h"
#include "iostream"
using namespace std;

LinkedStack::LinkedStack()
{
    top = nullptr;
    count = 0;
}

LinkedStack::~LinkedStack()
{
    while (top != nullptr)
    {
        QueueNode *temp = top;
        top = top->next;
        delete temp;
    }
}

bool LinkedStack::isEmpty() const
{
    return top == nullptr;
}

int LinkedStack::size() const
{
    return count;
}

void LinkedStack::push(Registration r)
{
    QueueNode *newNode = new QueueNode(r);
    newNode->next = top;
    top = newNode;
    count++;
}

Registration LinkedStack::pop()
{
    if (isEmpty())
        return Registration();
    QueueNode *temp = top;
    Registration r = temp->data;
    top = top->next;
    delete temp;
    count--;
    return r;
}

bool LinkedStack::removeByCNIC(string cnic)
{
    if (isEmpty())
        return false;

    if (top->data.getParticipant().getCnic() == cnic)
    {
        pop();
        return true;
    }

    QueueNode *current = top;
    while (current->next != nullptr)
    {
        if (current->next->data.getParticipant().getCnic() == cnic)
        {
            QueueNode *temp = current->next;
            current->next = temp->next;
            delete temp;
            count--;
            return true;
        }
        current = current->next;
    }
    return false;
}

double LinkedStack::calculateTotalRevenue()
{
    double total = 0;
    QueueNode *temp = top;
    while (temp != nullptr)
    {
        total += temp->data.getAmountPaid();
        temp = temp->next;
    }
    return total;
}

void LinkedStack::displayAll() const
{
    if (isEmpty())
    {
        cout << "No verified registrations.\n";
        return;
    }
    cout << "\n\t<========== VERIFIED REGISTRATIONS (STACK LIFO) ==========>\n";
    cout << left << setw(20) << "Name" << setw(15) << "CNIC" << setw(20) << "Event" << setw(12) << "Fees" << setw(12) << "Status";
    cout << "\n---------------------------------------------------------------------------\n";
    QueueNode *temp = top;
    while (temp != nullptr)
    {
        temp->data.displayTableRow();
        temp = temp->next;
    }
}

void LinkedStack::saveToFile(ofstream &outFile)
{
    QueueNode *temp = top;
    while (temp != nullptr)
    {
        outFile << temp->data;
        temp = temp->next;
    }
}