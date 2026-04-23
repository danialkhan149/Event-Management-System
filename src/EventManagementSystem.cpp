#include "EventManagementSystem.h"
#include "iostream"
using namespace std;

void EventManagementSystem::initializeSystem()
{

    network.setName(0, "Sports Module");
    network.setName(1, "Cricket");
    network.setName(2, "Football");
    network.setName(3, "Tech Module");
    network.setName(4, "Hackathon");
    network.setName(5, "Robotics");
    network.setName(6, "Cultural Module");
    network.setName(7, "Music");
    network.setName(8, "Drama");
    network.addEdge(0, 1);
    network.addEdge(0, 2);
    network.addEdge(3, 4);
    network.addEdge(3, 5);
    network.addEdge(6, 7);
    network.addEdge(6, 8);
}

EventManagementSystem::EventManagementSystem() : network(9)
{

    initializeSystem();

    loadAllData();
}

void EventManagementSystem::loadAllData()
{
    cout << "Loading system data...\n";

    try
    {
        ifstream eFile("events.txt");

        if (!eFile.is_open())
        {
            throw runtime_error("Could not open events.txt");
        }

        Event e;
        int eventCount = 0;
        while (eFile >> e)
        {
            eventTree.insert(e);
            eventCount++;
        }
        eFile.close();

        if (eventCount > 0)
        {
            cout << "Loaded " << eventCount << " events from file.\n";
        }
    }
    catch (const runtime_error &e)
    {
        cout << "! Warning: " << e.what() << ".Loading defaults...\n";
    }
    catch (const exception &e)
    {
        cout << "Error loading events: " << e.what() << ". Loading defaults...\n";
    }

    if (eventTree.isEmpty())
    {
        eventTree.insert(Event(101, "Cricket Match", "Sports", "2025-02-15", "Ground A", 50, 500));
        eventTree.insert(Event(201, "Hackathon", "Tech", "2025-03-01", "Lab 1", 30, 1000));
        eventTree.insert(Event(301, "Music Fest", "Cultural", "2025-03-10", "Auditorium", 100, 300));
        cout << "Default events loaded.\n";
    }

    try
    {
        ifstream pFile("pending.txt");

        if (!pFile.is_open())
        {
            cout << "No pending registrations file found (this is normal for first run).\n";
        }
        else
        {
            Registration r;
            int pendingCount = 0;
            while (pFile >> r)
            {
                if (r.getPriority() < 2)
                {
                    pendingQueue.enqueue(r);
                    userDirectory.insert(r.getParticipant().getCnic(), r);
                }
                else
                {
                    urgentQueue.push(r);
                    userDirectory.insert(r.getParticipant().getCnic(), r);
                }
                pendingCount++;
            }
            pFile.close();

            if (pendingCount > 0)
            {
                cout << "Loaded " << pendingCount << " pending registrations.\n";
            }
        }
    }
    catch (const exception &e)
    {
        cout << "Error loading pending registrations: " << e.what() << "\n";
    }

    try
    {
        ifstream vFile("verified.txt");

        if (!vFile.is_open())
        {
            cout << "No verified registrations file found (this is normal for first run).\n";
        }
        else
        {
            Registration r;
            int verifiedCount = 0;
            while (vFile >> r)
            {
                r.setVerified(true);
                verifiedStack.push(r);
                userDirectory.insert(r.getParticipant().getCnic(), r);
                verifiedCount++;
            }
            vFile.close();

            if (verifiedCount > 0)
            {
                cout << "Loaded " << verifiedCount << " verified registrations.\n";
            }
        }
    }
    catch (const exception &e)
    {
        cout << "Error loading verified registrations: " << e.what() << "\n";
    }

    cout << "System initialization complete.\n";
}

void EventManagementSystem::saveAllData()
{
    int successCount = 0;
    int totalFiles = 3;

    try
    {
        ofstream pFile("pending.txt");
        if (!pFile.is_open())
        {
            throw runtime_error("Could not open pending.txt for writing");
        }
        pendingQueue.saveToFile(pFile);
        pFile.close();

        if (pFile.fail())
        {
            throw runtime_error("Error writing to pending.txt");
        }
        successCount++;
    }
    catch (const exception &e)
    {
        cout << "X Error saving pending registrations: " << e.what() << "\n";
    }

    try
    {
        ofstream vFile("verified.txt");
        if (!vFile.is_open())
        {
            throw runtime_error("Could not open verified.txt for writing");
        }
        verifiedStack.saveToFile(vFile);
        vFile.close();

        if (vFile.fail())
        {
            throw runtime_error("Error writing to verified.txt");
        }
        successCount++;
    }
    catch (const exception &e)
    {
        cout << "X Error saving verified registrations: " << e.what() << "\n";
    }

    try
    {
        ofstream eFile("events.txt");
        if (!eFile.is_open())
        {
            throw runtime_error("Could not open events.txt for writing");
        }
        eventTree.saveToFile(eFile);
        eFile.close();

        if (eFile.fail())
        {
            throw runtime_error("Error writing to events.txt");
        }
        successCount++;
    }
    catch (const exception &e)
    {
        cout << "Error saving events: " << e.what() << "\n";
    }

    if (successCount == totalFiles)
    {
        cout << "All data saved successfully (" << successCount << "/" << totalFiles << " files).\n";
    }
    else
    {
        cout << "! Warning: Only " << successCount << "/" << totalFiles << " files saved successfully.\n";
    }
}

void EventManagementSystem::generateReport()
{
    cout << "\n\t\t<========== SYSTEM ANALYTICS ==========>\n";
    cout << "1. Pending Queue Size: " << pendingQueue.size() << "\n";
    cout << "2. VIP Queue Size:     " << urgentQueue.size() << "\n";
    cout << "3. Verified Users:     " << verifiedStack.size() << "\n";
    cout << "4. Total Revenue:      Rs." << verifiedStack.calculateTotalRevenue() << "\n";

    vector<Event> allEvents = eventTree.getFlatList();
    if (!allEvents.empty())
    {
        Event best = allEvents[0];
        for (const auto &e : allEvents)
        {
            if (e.getRegistrationCount() > best.getRegistrationCount())
                best = e;
        }
        cout << "5. Most Popular:       " << best.getEventName()
             << " (" << best.getRegistrationCount() << " users)\n";
    }
}

void EventManagementSystem::deleteParticipant()
{
    string cnic;
    cout << "Enter CNIC to delete: ";
    cin >> cnic;
    cin.ignore();

    bool removedPending = pendingQueue.removeByCNIC(cnic);
    bool removedStack = verifiedStack.removeByCNIC(cnic);

    userDirectory.remove(cnic);

    if (removedPending || removedStack)
        cout << "Participant deleted.\n";
    else
        cout << "Participant not found in queues.\n";
}

void EventManagementSystem::deleteEvent()
{
    int id;
    cout << "Enter Event ID to delete: ";
    cin >> id;
    Event *e = eventTree.search(id);
    if (e == nullptr)
    {
        cout << "Event not found.\n";
        return;
    }

    if (e->getRegistrationCount() > 0)
    {
        cout << "! Warning: Event has " << e->getRegistrationCount() << " users. Delete anyway? (1-Yes, 0-No): ";
        int choice;
        cin >> choice;
        cin.ignore();
        if (choice != 1)
            return;
    }

    eventTree.remove(id);
    cout << "Event deleted.\n";
}

void EventManagementSystem::registerUser(bool isVIP)
{
    cout << "\n\t\t<========== " << (isVIP ? "VIP " : "") << "REGISTRATION ==========>\n";
    string n, g, c, cc, em;
    cout << "Enter Name: ";
    getline(cin, n);
    cout << "Enter Gender (M/F): ";
    getline(cin, g);
    cout << "Enter CNIC: ";
    getline(cin, c);

    if (userDirectory.search(c) != nullptr)
    {
        cout << "X Error: CNIC already exists!\n";
        return;
    }

    cout << "Enter Contact: ";
    getline(cin, cc);
    cout << "Enter Email: ";
    getline(cin, em);

    Participant p(n, g, c, cc, em);

    if (!p.isValid())
    {
        cout << "Invalid participant data. Registration cancelled.\n";
        return;
    }

    eventTree.displayAll();
    int eventID;
    cout << "\nEnter Event ID: ";

    try
    {
        if (!(cin >> eventID))
        {
            throw invalid_argument("Invalid input! Event ID must be a number.");
        }
        cin.ignore();
    }
    catch (const invalid_argument &e)
    {
        cout << "X " << e.what() << "\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    Event *e = eventTree.search(eventID);
    if (e == nullptr)
    {
        cout << "Invalid Event ID.\n";
        return;
    }
    if (e->getRegistrationCount() >= e->getMaxCapacity())
    {
        cout << "Event Full!\n";
        return;
    }

    string trxID;
    cout << "Fee: Rs." << e->getRegistrationFee() << ". Enter Trx ID: ";
    cin >> trxID;

    int priority = 1;
    if (isVIP)
    {
        cout << "Priority (2-10): ";
        try
        {
            if (!(cin >> priority))
            {
                throw invalid_argument("Invalid input! Priority must be a number.");
            }
            cin.ignore();
        }
        catch (const invalid_argument &e)
        {
            cout << "X " << e.what() << "\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
    }
    cin.ignore();

    Registration reg(p, e->getEventName(), trxID, "2025-01-01", false, (isVIP ? priority : 1), e->getRegistrationFee());
    if (isVIP)
        urgentQueue.push(reg);
    else
        pendingQueue.enqueue(reg);

    userDirectory.insert(p.getCnic(), reg);

    cout << "Registration Successful (Pending Verification).\n";
}

void EventManagementSystem::updateParticipant()
{
    string cnic;
    cout << "Enter CNIC to update: ";
    cin >> cnic;
    cin.ignore();

    Registration *r = userDirectory.search(cnic);
    if (r == nullptr)
    {
        cout << "User not found.\n";
        return;
    }

    r->getParticipant().updateInteractive();

    char changeStatus;
    cout << "Current Status: " << (r->isVerified() ? "Verified" : "Pending") << "\n";
    cout << "Change Status? (y/n): ";
    cin >> changeStatus;
    cin.ignore();
    if (changeStatus == 'y' || changeStatus == 'Y')
    {
        r->setVerified(!r->isVerified());
        cout << "Status updated.\n";
    }
    cout << "Participant details updated.\n";
}

void EventManagementSystem::createEvent()
{
    cout << "\n<=== CREATE NEW EVENT ===>\n";
    string n, m, d, v;
    int id, cap, fee;

    cout << "ID: ";
    cin >> id;
    cin.ignore();

    if (eventTree.search(id) != nullptr)
    {
        cout << "X Error: ID already exists.\n";
        return;
    }

    cout << "Name: ";
    getline(cin, n);
    cout << "Module: ";
    getline(cin, m);
    cout << "Date: ";
    getline(cin, d);
    cout << "Venue: ";
    getline(cin, v);
    cout << "Capacity: ";
    cin >> cap;
    cout << "Fee: ";
    cin >> fee;
    cin.ignore();
    Event e(id, n, m, d, v, cap, fee);

    eventTree.insert(e);
    cout << "Event Created.\n";
}

void EventManagementSystem::updateEvent()
{
    int id;
    cout << "Enter Event ID to update: ";
    cin >> id;
    Event *e = eventTree.search(id);

    if (e == nullptr)
    {
        cout << "Not found.\n";
        return;
    }

    cin.ignore();
    string temp;
    cout << "Update Name [" << e->getEventName() << "] (Enter to skip): ";
    getline(cin, temp);
    if (!temp.empty())
        e->setEventName(temp);

    cout << "Update Date [" << e->getDate() << "] (Enter to skip): ";
    getline(cin, temp);
    if (!temp.empty())
        e->setDate(temp);

    cout << "Update Fee [" << e->getRegistrationFee() << "] (Enter -1 to skip): ";
    double fee;

    try
    {
        if (!(cin >> fee))
        {
            throw invalid_argument("Invalid input! fee must be a number.");
        }
        cin.ignore();
    }
    catch (const invalid_argument &e)
    {
        cout << "X " << e.what() << "\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (fee != -1)
        e->setRegistrationFee(fee);

    cout << "Event Updated.\n";
}

void EventManagementSystem::adminPanel()
{
    int choice;
    do
    {
        cout << "\n\t<========== ADMIN PANEL ==========>\n";
        cout << "1. View Queues (Pending/VIP/Verified)\n";
        cout << "2. Verify User (Next Pending)\n";
        cout << "3. Verify User (Next VIP)\n";
        cout << "4. UNDO Last Verification\n";
        cout << "5. Search & View Participant\n";
        cout << "6. Update Participant Details\n";
        cout << "7. Delete Participant\n";
        cout << "8. Create New Event\n";
        cout << "9. Update Event Details\n";
        cout << "10. Delete Event\n";
        cout << "11. Analytics Report\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "\n[1] Pending:\n";
            pendingQueue.displayAll();
            cout << "\n[2] VIP:\n";
            urgentQueue.displayAll();
            cout << "\n[3] Verified:\n";
            verifiedStack.displayAll();
            break;
        case 2:
        {
            try
            {
                if (pendingQueue.isEmpty())
                {
                    cout << "\nNo pending registrations to verify.\n";
                    break;
                }

                Registration r = pendingQueue.dequeue();
                r.setVerified(true);

                Event *e = eventTree.searchByName(r.getEventName());
                if (e != nullptr)
                {
                    e->incrementCount();
                }

                verifiedStack.push(r);

                userDirectory.remove(r.getParticipant().getCnic());
                userDirectory.insert(r.getParticipant().getCnic(), r);

                cout << "\nRegistration verified for: " << r.getParticipant().getName() << "\n";
                break;
            }
            catch (const runtime_error &e)
            {
                cout << "Error during verification: " << e.what() << "\n";
            }
            break;
        }

        case 3:
        {
            if (urgentQueue.isEmpty())
            {
                cout << "\nNo VIP registrations to verify.\n";
                break;
            }

            Registration r = urgentQueue.pop();
            r.setVerified(true);

            Event *e = eventTree.searchByName(r.getEventName());
            if (e != nullptr)
            {
                e->incrementCount();
            }

            verifiedStack.push(r);

            userDirectory.remove(r.getParticipant().getCnic());
            userDirectory.insert(r.getParticipant().getCnic(), r);

            cout << "\nVIP registration verified for: " << r.getParticipant().getName()
                 << " (Priority: " << r.getPriority() << ")\n";
            break;
        }
        case 4:
        {
            if (verifiedStack.isEmpty())
            {
                cout << "\nNo verification to undo.\n";
                break;
            }

            Registration r = verifiedStack.pop();
            r.setVerified(false);

            Event *e = eventTree.searchByName(r.getEventName());
            if (e != nullptr)
            {
                e->decrementCount();
            }

            urgentQueue.push(r);

            userDirectory.remove(r.getParticipant().getCnic());
            userDirectory.insert(r.getParticipant().getCnic(), r);

            cout << "\nLast verification undone for: " << r.getParticipant().getName() << "\n";
            break;
        }
        case 5:
        {
            string cnic;
            cout << "Enter CNIC: ";
            cin >> cnic;
            cin.ignore();
            Registration *r = userDirectory.search(cnic);
            if (r)
                r->displayDetails();
            else
                cout << "Not Found.\n";
            break;
        }
        case 6:
            updateParticipant();
            break;
        case 7:
            deleteParticipant();
            break;
        case 8:
            createEvent();
            break;
        case 9:
            updateEvent();
            break;
        case 10:
            deleteEvent();
            break;
        case 11:
            generateReport();
            break;
        }
    } while (choice != 0);
}

void EventManagementSystem::graphMenu()
{
    int choice;
    do
    {
        cout << "\n======================================\n";
        cout << "||     MODULE-EVENT NETWORK         ||\n";
        cout << "=======================================\n";
        cout << "1. Display Module-Event Graph\n";
        cout << "2. BFS Traversal\n";
        cout << "3. DFS Traversal\n";
        cout << "4. Back to Main Menu\n";
        cout << "\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            network.displayGraph();
            break;
        case 2:
        {
            cout << "\nSelect starting node:\n";
            cout << "0-Sports, 3-Tech, 6-Cultural: ";
            int start;
            cin >> start;
            cin.ignore();
            if (start == 0 || start == 3 || start == 6)
                network.bfs(start);
            else
                cout << "Invalid choice!\n";
            break;
        }
        case 3:
        {
            cout << "\nSelect starting node:\n";
            cout << "0-Sports, 3-Tech, 6-Cultural: ";
            int start;
            cin >> start;
            cin.ignore();
            if (start == 0 || start == 3 || start == 6)
                network.dfs(start);
            else
                cout << "Invalid choice!\n";
            break;
        }
        case 4:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);
}

void EventManagementSystem::run()
{
    int choice;
    do
    {
        cout << "\n==================================================\n";
        cout << "||   EVENT MANAGEMENT SYSTEM (FULL PRO VERSION) ||\n";
        cout << "==================================================\n";
        cout << "1. Register Participant\n";
        cout << "2. Register VIP\n";
        cout << "3. View Events\n";
        cout << "4. Search Event\n";
        cout << "5. Visual Network (Graph)\n";
        cout << "6. Admin Panel\n";
        cout << "7. Save & Exit\n";
        cout << "Choice: ";
        cin >> choice;

        cin.ignore();
        switch (choice)
        {
        case 1:
            registerUser(false);
            break;
        case 2:
            registerUser(true);
            break;
        case 3:
            eventTree.displayAll();
            break;
        case 4:
        {
            int id;
            cout << "Enter ID: ";
            cin >> id;
            cin.ignore();
            Event *e = eventTree.search(id);
            if (e)
                e->displayDetails();
            else
                cout << "Not Found.\n";
            break;
        }
        case 5:
            graphMenu();
            break;
        case 6:
            adminPanel();
            break;
        case 7:
            saveAllData();
            break;
        default:
            cout << "Invalid.\n";
        }
    } while (choice != 7);
}