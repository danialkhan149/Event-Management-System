#include "Registration.h"
#include <iostream>
using namespace std;

Registration::Registration()
{
    paymentStatus = false;
    priority = 0;
    amountPaid = 0;
}

Registration::Registration(Participant p, string eName, string tID, string date, bool status, short prio, short amt)
{
    participant = p;
    eventName = eName;
    trxID = tID;
    registrationDate = date;
    paymentStatus = status;
    priority = prio;
    amountPaid = amt;
}

Participant &Registration::getParticipant()
{
    return participant;
}
const Participant &Registration::getParticipant() const
{
    return participant;
}
string Registration::getEventName() const
{
    return eventName;
}
string Registration::getTrxID() const
{
    return trxID;
}
string Registration::getRegistrationDate() const
{
    return registrationDate;
}
bool Registration::isVerified() const
{
    return paymentStatus;
}
short int Registration::getPriority() const
{
    return priority;
}
short int Registration::getAmountPaid() const
{
    return amountPaid;
}

void Registration::setEventName(string e)
{
    eventName = e;
}
void Registration::setTrxID(string t)
{
    trxID = t;
}
void Registration::setVerified(bool v)
{
    paymentStatus = v;
}
void Registration::setPriority(short p)
{
    priority = p;
}

void Registration::displayTableRow() const
{
    cout << left << setw(17) << participant.getName()
         << setw(15) << participant.getCnic()
         << setw(22) << eventName
         << setw(12) << ("Rs." + to_string(amountPaid))
         << setw(12) << (paymentStatus ? "Verified" : "Pending") << "\n";
}

void Registration::displayDetails() const
{
    cout << "\n\t\t<========== REGISTRATION DETAILS ==========>\n";
    participant.displayPersonalDetails();
    cout << "Event: " << eventName << "\n";
    cout << "Amount Paid: Rs. " << amountPaid << "\n";
    cout << "Transaction ID: " << trxID << "\n";
    cout << "Date: " << registrationDate << "\n";
    cout << "Status: " << (paymentStatus ? "Verified" : "Pending") << "\n";

    if (priority > 1)
        cout << "Priority: VIP (Level " << priority << ")\n";
}

bool Registration::operator==(const Registration &other) const
{
    return this->participant == other.participant;
}
bool Registration::operator==(const string &cnic) const
{
    return this->participant == cnic;
}

ofstream &operator<<(ofstream &os, const Registration &r)
{
    os << r.participant.getName() << "|" << r.participant.getGender() << "|"
       << r.participant.getCnic() << "|" << r.participant.getContact() << "|"
       << r.participant.getEmail() << "|";

    os << r.eventName << "|" << r.trxID << "|" << r.amountPaid << "|"
       << r.registrationDate << "|" << r.priority << "|"
       << (r.paymentStatus ? "True" : "False") << "\n";
    return os;
}

ifstream &operator>>(ifstream &is, Registration &r)
{
    string line;
    if (getline(is, line) && !line.empty())
    {
        size_t pos = 0;
        string token;
        int idx = 0;

        string n, g, c, con, em;

        while ((pos = line.find('|')) != string::npos)
        {
            token = line.substr(0, pos);
            switch (idx++)
            {
            case 0:
                n = token;
                break;
            case 1:
                g = token;
                break;
            case 2:
                c = token;
                break;
            case 3:
                con = token;
                break;
            case 4:
                em = token;
                break;
            case 5:
                r.eventName = token;
                break;
            case 6:
                r.trxID = token;
                break;
            case 7:
                try
                {
                    r.amountPaid = (token.empty() ? 0 : stoi(token));
                }
                catch (const invalid_argument &e)
                {
                    r.amountPaid = 0;
                }
                catch (const out_of_range &e)
                {
                    r.amountPaid = 0;
                }
                break;
            case 8:
                r.registrationDate = token;
                break;
            case 9:
                try
                {
                    r.priority = (token.empty() ? 0 : stoi(token));
                }
                catch (const invalid_argument &e)
                {
                    r.priority = 0;
                }
                catch (const out_of_range &e)
                {
                    r.priority = 0;
                }
                break;
            }
            line.erase(0, pos + 1);
        }
        r.paymentStatus = (line == "True");
        r.participant = Participant(n, g, c, con, em);
    }
    return is;
}

bool Registration::operator<(const Registration &other) const
{
    return this->priority < other.priority;
}

bool Registration::operator>(const Registration &other) const
{
    return this->priority > other.priority;
}