#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class Event
{
    int eventID;
    string eventName;
    string moduleName;
    string date;
    string venue;
    int registrationCount;
    int maxCapacity;
    double registrationFee;

public:
    Event();
    Event(int, string, string, string, string, int, int);

    int getEventID() const;
    string getEventName() const;
    string getModuleName() const;
    string getDate() const;
    string getVenue() const;
    int getRegistrationCount() const;
    int getMaxCapacity() const;
    double getRegistrationFee() const;

    void setEventID(int);
    void setEventName(const string &);
    void setModuleName(const string &);
    void setDate(const string &);
    void setVenue(const string &);
    void setMaxCapacity(int);
    void setRegistrationFee(double);

    void incrementCount();
    void decrementCount();

    void displayTableRow() const;
    void displayDetails() const;

    bool operator==(const Event &) const;
    bool operator==(int) const;
    bool operator<(const Event &) const;
    bool operator>(const Event &) const;

    friend ofstream &operator<<(ofstream &, const Event &);
    friend ifstream &operator>>(ifstream &, Event &);
};

#endif