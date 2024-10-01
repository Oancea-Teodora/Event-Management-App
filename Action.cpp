#include "Action.h"



void addAction::undo() {
    this->repo.delete2(addedEvent.getTitle());
}


void addAction::redo() {
    this->repo.add2(addedEvent);

}

addAction::addAction(RepositoryAdmin& admin, Event event) : repo{admin}{
 //   this->repo = admin;
    this->addedEvent = event;

}


deleteAction::deleteAction(RepositoryAdmin& repo, Event deletedEvent) : repo{repo}{
    this->deletedEvent = deletedEvent;
}

void deleteAction::undo() {
    this->repo.add2(deletedEvent);

}

void deleteAction::redo() {
    this->repo.delete2(deletedEvent.getTitle());
}

updateAction::updateAction(RepositoryAdmin& repo, Event oldEvent, Event newEvent) : repo{repo}{
    this->oldEvent = oldEvent;
    this->newEvent = newEvent;

}

void updateAction::undo() {
    int index = this->repo.getindex(newEvent.getTitle());
    this->repo.update2(index, oldEvent);
}

void updateAction::redo() {
    int index = this->repo.getindex(oldEvent.getTitle());
    this->repo.update2(index, newEvent);
}

