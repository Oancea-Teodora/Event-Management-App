#pragma once
#include "Repository.h"

class Action {

public:
   // Action();
    virtual void undo() = 0;
    virtual void redo() = 0;
};


class addAction : public Action
{
private:

    RepositoryAdmin& repo;
    Event addedEvent;

public:

    void undo() override;
    void redo() override;
    addAction(RepositoryAdmin& admin, Event event);

};


class deleteAction : public Action
{
private:
    //class RepositoryAdmin;
    RepositoryAdmin& repo;
    Event deletedEvent;

public:
    deleteAction(RepositoryAdmin& repo, Event deletedEvent);
    void undo() override;
    void redo() override;
};


class updateAction : public Action
{
private:
    //class RepositoryAdmin;
    RepositoryAdmin& repo;
    Event oldEvent;
    Event newEvent;

public:
    updateAction(RepositoryAdmin& repo, Event oldEvent, Event newEvent);
    void undo() override;
    void redo() override;
};

