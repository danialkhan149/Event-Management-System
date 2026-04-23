#include "Participant.h"
#include <iostream>
#include <string>
using namespace std;

Participant::Participant() {}

Participant::Participant(string n, string g, string c, string con, string em)
{
    name = n;
    gender = g;
    cnic = c;
    contact = con;
    email = em;
}

string Participant::getName() const
{
    return name;
}
string Participant::getGender() const
{
    return gender;
}
string Participant::getCnic() const
{
    return cnic;
}
string Participant::getContact() const
{
    return contact;
}
string Participant::getEmail() const
{
    return email;
}

void Participant::setName(const string &n)
{
    name = n;
}
void Participant::setGender(const string &g)
{
    gender = g;
}
void Participant::setCnic(const string &c)
{
    cnic = c;
}
void Participant::setContact(const string &con)
{
    contact = con;
}
void Participant::setEmail(const string &em)
{
    email = em;
}

void Participant::displayPersonalDetails() const
{
    cout << "Name: " << name << "\n";
    cout << "Gender: " << gender << "\n";
    cout << "CNIC: " << cnic << "\n";
    cout << "Contact: " << contact << "\n";
    cout << "Email: " << email << "\n";
}

bool Participant::isValid() const
{
    if (cnic.length() != 13)
    {
        cout << "X Error: CNIC must be 13 digits.\n";
        return false;
    }

    if (name.empty())
    {
        cout << "X Error: Name cannot be empty.\n";
        return false;
    }
    return true;
}

bool Participant::operator==(const Participant &other) const
{
    return this->cnic == other.cnic;
}

bool Participant::operator==(const string &searchCNIC) const
{
    return this->cnic == searchCNIC;
}

void Participant::updateInteractive()
{
    string temp;
    cout << "\n--- Updating Personal Info for " << name << " ---\n";
    cout << "New Name (Enter to skip): ";
    getline(cin, temp);
    if (!temp.empty())
    {
        name = temp;
    }
    cout << "New Contact (Enter to skip): ";
    getline(cin, temp);
    if (!temp.empty())
    {
        contact = temp;
    }

    cout << "New Email (Enter to skip): ";
    getline(cin, temp);
    if (!temp.empty())
    {
        email = temp;
    }
}