#pragma once
#include <vector>
#include "Event.h"


using namespace std;

class RepositoryAdmin {

protected:
    vector<Event> all_events;
    vector<Event> user_events;

    string filename;
    string filename2;
   // string type;

    void readFromFile();
    virtual void writeToFile();
    void writeToFileAdmin();

public:

    RepositoryAdmin(string filename, string filename2);

   // int getindex(const std::string &title);

    void add2(Event event);

    void delete2(string title);

    void update2(int index, Event &event);

    vector<Event> getelements();

    //int getindex(Event title);

    int getsize();

    Event getElement(const vector<Event> &arr, int index);

    void add_user(Event event);

    void delete_user(std::string &title);

    vector<Event> getelementsUser();

    int getsizeUser();

    int getindex(const string &title);

    void saveToFile();

    void clear_user();

    int getindexuser(const string &title);
};
