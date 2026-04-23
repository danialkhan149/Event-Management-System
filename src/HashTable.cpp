#include "HashTable.h"
#include "iostream"
using namespace std;

HashNode::HashNode(string k, Registration v)
{
    key = k;
    value = v;
    next = nullptr;
}

int HashTable::hashFunction(string key)
{
    long long sum = 0;
    for (char c : key)
    {
        if (isdigit(c))
        {
            sum += (c - '0');
        }
        else
        {
            sum += c;
        }
    }
    return sum % TABLE_SIZE;
}

HashTable::HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = nullptr;
}

HashTable::~HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *entry = table[i];
        while (entry != nullptr)
        {
            HashNode *prev = entry;
            entry = entry->next;
            delete prev;
        }
        table[i] = nullptr;
    }
}

void HashTable::insert(string key, Registration r)
{
    int index = hashFunction(key);
    HashNode *newNode = new HashNode(key, r);

    if (table[index] == nullptr)
    {
        table[index] = newNode;
    }
    else
    {

        newNode->next = table[index];
        table[index] = newNode;
    }
}

Registration *HashTable::search(string key)
{
    int index = hashFunction(key);
    HashNode *entry = table[index];

    while (entry != nullptr)
    {
        if (entry->key == key)
        {
            return &(entry->value);
        }
        entry = entry->next;
    }
    return nullptr;
}

void HashTable::remove(string key)
{
    int index = hashFunction(key);
    HashNode *entry = table[index];
    HashNode *prev = nullptr;

    while (entry != nullptr && entry->key != key)
    {
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr)
        return;

    if (prev == nullptr)
    {
        table[index] = entry->next;
    }
    else
    {
        prev->next = entry->next;
    }
    delete entry;
}

void HashTable::displayAll()
{
    bool isEmpty = true;
    cout << "\n\t<========== ALL REGISTERED PARTICIPANTS (HASH TABLE) ==========>\n";
    cout << left << setw(20) << "Name" << setw(15) << "CNIC"
         << setw(20) << "Event" << setw(15) << "Status\n";
    cout << string(90, '-') << "\n";

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *entry = table[i];
        while (entry != nullptr)
        {
            isEmpty = false;
            Registration r = entry->value;

            cout << left << setw(20) << r.getParticipant().getName()
                 << setw(15) << r.getParticipant().getCnic()
                 << setw(20) << r.getEventName()
                 << setw(15) << (r.isVerified() ? "Verified" : "Pending") << "\n";

            entry = entry->next;
        }
    }
    if (isEmpty)
        cout << "No participants found.\n";
}
