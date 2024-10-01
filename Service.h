#pragma once
#include "Repository.h"
#include "string"
#include "Action.h"
#include "TableMode.h"

class ServiceAdmin {

private:
    RepositoryAdmin repo;

    vector<RepositoryAdmin*> allrepos;

    vector<Action*> undoStack;
    vector<Action*> redoStack;

public:
    //ServiceAdmin();

    void undoLastAction(vector<Action*> &currentUndoStack, vector<Action*> &currentRedoStack);

    void redoLastAction(vector<Action*> &currentUndoStack, vector<Action*> &currentRedoStack);

    void undoAdmin();

    void redoAdmin();

    void addrepo(RepositoryAdmin *rep);

    vector<RepositoryAdmin*> getrepos();

    explicit ServiceAdmin(string filename);

    void add3(Event &event);

    void generate();

    void update3(int index, Event &event);

    vector<Event> getelements();

    int getsize();

    void delete3(std::string title);

    //int getindex(std::string &title);

    int getindex(std::string title);

 //   Event getElement();

    Event getElement(const vector<Event>& arr, int index);

    void add_user(Event event);

    vector<Event> getelementsUser();

    void delete_user(std::string title);

    int getsizeUser();

    vector<Event> filter_month(const std::string& month);

    void saveToFile();

    void openEvents(const string& type);

     TableMode getRepo();
};
