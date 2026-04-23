#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <string>
using namespace std;

class Participant
{
    string name;
    string gender;
    string cnic;
    string contact;
    string email;

public:
    Participant();

    Participant(string, string, string, string, string);

    string getName() const;
    string getGender() const;
    string getCnic() const;
    string getContact() const;
    string getEmail() const;

    void setName(const string &);
    void setGender(const string &);
    void setCnic(const string &);
    void setContact(const string &);
    void setEmail(const string &);

    void displayPersonalDetails() const;
    bool isValid() const;

    bool operator==(const Participant &) const;
    bool operator==(const string &) const;

    void updateInteractive();
};
#endif