#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "Participant.h"
#include <fstream>
#include <iomanip>
using namespace std;

class Registration
{
    Participant participant;
    string eventName;
    string trxID;
    string registrationDate;
    bool paymentStatus;
    short int priority;
    short int amountPaid;

public:
    Registration();
    Registration(Participant, string, string, string, bool, short, short);

    Participant &getParticipant();
    const Participant &getParticipant() const;
    string getEventName() const;
    string getTrxID() const;
    string getRegistrationDate() const;
    bool isVerified() const;
    short int getPriority() const;
    short int getAmountPaid() const;

    void setEventName(string);
    void setTrxID(string);
    void setVerified(bool);
    void setPriority(short);

    void displayTableRow() const;
    void displayDetails() const;

    bool operator==(const Registration &) const;
    bool operator==(const string &) const;

    friend ofstream &operator<<(ofstream &, const Registration &);
    friend ifstream &operator>>(ifstream &, Registration &);

    bool operator<(const Registration &) const;
    bool operator>(const Registration &) const;
};
#endif