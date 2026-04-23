#include "PriorityQueue.h"
#include "iostream"
using namespace std;

int PriorityQueue::parent(int i)
{
    return (i - 1) / 2;
}
int PriorityQueue::leftChild(int i)
{
    return (2 * i) + 1;
}
int PriorityQueue::rightChild(int i)
{
    return (2 * i) + 2;
}

void PriorityQueue::heapifyUp(int index)
{
    while (index > 0 && heap[index] > heap[parent(index)])
    {
        swap(heap[index], heap[parent(index)]);
        index = parent(index);
    }
}

void PriorityQueue::heapifyDown(int index)
{
    int maxIndex = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < heap.size() && heap[left] > heap[maxIndex])
    {
        maxIndex = left;
    }

    if (right < heap.size() && heap[right] > heap[maxIndex])
    {
        maxIndex = right;
    }

    if (index != maxIndex)
    {
        swap(heap[index], heap[maxIndex]);
        heapifyDown(maxIndex);
    }
}

bool PriorityQueue::isEmpty() const
{
    return heap.empty();
}
int PriorityQueue::size() const
{
    return heap.size();
}

void PriorityQueue::push(Registration r)
{
    heap.push_back(r);
    heapifyUp(heap.size() - 1);
}

Registration PriorityQueue::pop()
{
    if (isEmpty())
        return Registration();

    Registration root = heap[0];
    Registration last = heap.back();
    heap.pop_back();

    if (!isEmpty())
    {
        heap[0] = last;
        heapifyDown(0);
    }
    return root;
}

Registration PriorityQueue::top()
{
    if (isEmpty())
        return Registration();
    return heap[0];
}

void PriorityQueue::displayAll() const
{
    if (isEmpty())
    {
        cout << "\nPriority Queue is empty.\n";
        return;
    }

    cout << "\n\t\t<========== VERIFIED REGISTRATIONS (VIPs) ==========>\n";
    cout << left << setw(20) << "Name" << setw(15) << "CNIC"
         << setw(25) << "Event" << setw(14) << "Priority" << setw(9) << "Fees" << setw(10) << "Status";
    cout << "\n------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < heap.size(); i++)
    {
        cout << left << setw(20) << heap[i].getParticipant().getName()
             << setw(15) << heap[i].getParticipant().getCnic()
             << setw(25) << heap[i].getEventName()
             << setw(14) << ("Level " + to_string(heap[i].getPriority()))
             << setw(9) << heap[i].getAmountPaid()
             << setw(7) << (heap[i].isVerified() ? "Verified" : "Pending") << "\n";
    }
}

void PriorityQueue::saveToFile(ofstream &outFile)
{
    for (int i = 0; i < heap.size(); i++)
    {
        outFile << heap[i];
    }
}