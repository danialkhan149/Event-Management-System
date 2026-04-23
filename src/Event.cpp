#include "Event.h"
#include "iostream"
using namespace std;

Event::Event()
{
    eventID = 0;
    registrationCount = 0;
    maxCapacity = 0;
    registrationFee = 0.0;
}

Event::Event(int id, string name, string module, string d, string v, int cap, int fee)
{
    eventID = id;
    eventName = name;
    moduleName = module;
    date = d;
    venue = v;
    maxCapacity = cap;
    registrationFee = fee;
    registrationCount = 0;
}

int Event::getEventID() const
{
    return eventID;
}
string Event::getEventName() const
{
    return eventName;
}
string Event::getModuleName() const
{
    return moduleName;
}
string Event::getDate() const
{
    return date;
}
string Event::getVenue() const
{
    return venue;
}
int Event::getRegistrationCount() const
{
    return registrationCount;
}
int Event::getMaxCapacity() const
{
    return maxCapacity;
}
double Event::getRegistrationFee() const
{
    return registrationFee;
}

void Event::setEventID(int id)
{
    eventID = id;
}
void Event::setEventName(const string &name)
{
    eventName = name;
}
void Event::setModuleName(const string &mod)
{
    moduleName = mod;
}
void Event::setDate(const string &d)
{
    date = d;
}
void Event::setVenue(const string &v)
{
    venue = v;
}
void Event::setMaxCapacity(int cap)
{
    maxCapacity = cap;
}
void Event::setRegistrationFee(double fee)
{
    registrationFee = fee;
}

void Event::incrementCount()
{
    if (registrationCount < maxCapacity)
        registrationCount++;
}

void Event::decrementCount()
{
    if (registrationCount > 0)
        registrationCount--;
}

void Event::displayTableRow() const
{
    cout << left << setw(8) << eventID
         << setw(25) << eventName
         << setw(15) << moduleName
         << setw(15) << registrationFee
         << setw(15) << (to_string(registrationCount) + "/" + to_string(maxCapacity)) << "\n";
}

void Event::displayDetails() const
{
    cout << "\n\t\t<========== EVENT DETAILS ==========>\n";
    cout << "ID: " << eventID << "\n";
    cout << "Name:" << eventName << "\n";
    cout << "Module: " << moduleName << "\n";
    cout << "Date: " << date << "\n";
    cout << "Venue: " << venue << "\n";
    cout << "Fee: Rs. " << registrationFee << "\n";
    cout << "Capacity: " << registrationCount << "/" << maxCapacity << "\n";
    cout << "Availability: " << (maxCapacity - registrationCount) << " seats left\n";
}

bool Event::operator==(const Event &other) const
{
    return this->eventID == other.eventID;
}

bool Event::operator==(int id) const
{
    return this->eventID == id;
}

bool Event::operator<(const Event &other) const
{
    return this->eventID < other.eventID;
}

bool Event::operator>(const Event &other) const
{
    return this->eventID > other.eventID;
}

ofstream &operator<<(ofstream &os, const Event &e)
{
    os << e.eventID << "|" << e.eventName << "|" << e.moduleName << "|"
       << e.date << "|" << e.venue << "|" << e.maxCapacity << "|"
       << e.registrationFee << "|" << e.registrationCount << "\n";
    return os;
}

ifstream &operator>>(ifstream &is, Event &e)
{
    string line;
    if (getline(is, line) && !line.empty())
    {
        size_t pos = 0;
        string token;
        int idx = 0;
        while ((pos = line.find('|')) != string::npos)
        {
            token = line.substr(0, pos);
            switch (idx++)
            {
            case 0:
                try
                {
                    e.eventID = (token.empty() ? 0 : stoi(token));
                }
                catch (const invalid_argument &ex)
                {
                    e.eventID = 0;
                }
                catch (const out_of_range &ex)
                {
                    e.eventID = 0;
                }
                break;
            case 1:
                e.eventName = token;
                break;
            case 2:
                e.moduleName = token;
                break;
            case 3:
                e.date = token;
                break;
            case 4:
                e.venue = token;
                break;
            case 5:
                try
                {
                    e.maxCapacity = (token.empty() ? 0 : stoi(token));
                }
                catch (const invalid_argument &ex)
                {
                    e.maxCapacity = 0;
                }
                catch (const out_of_range &ex)
                {
                    e.maxCapacity = 0;
                }
                break;
            case 6:
                try
                {
                    e.registrationFee = (token.empty() ? 0.0 : stod(token));
                }
                catch (const invalid_argument &ex)
                {
                    e.registrationFee = 0.0;
                }
                catch (const out_of_range &ex)
                {
                    e.registrationFee = 0.0;
                }
                break;
            }
            line.erase(0, pos + 1);
        }
        try
        {
            e.registrationCount = (line.empty() ? 0 : stoi(line));
        }
        catch (const invalid_argument &ex)
        {
            e.registrationCount = 0;
        }
        catch (const out_of_range &ex)
        {
            e.registrationCount = 0;
        }
    }
    return is;
}