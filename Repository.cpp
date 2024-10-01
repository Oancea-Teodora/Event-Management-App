#include "Repository.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Exceptions.h"

RepositoryAdmin::RepositoryAdmin(string filename, string filename2) : all_events(0), user_events(0){

    this->filename = filename;
    this->filename2 = filename2;
   // this->type = type;
    this->readFromFile();
}


void RepositoryAdmin::add2 (Event event)
{
    for(auto i: this->all_events)
    {
        if(i.getTitle() == event.getTitle())
            throw DuplicateEventException();

    }
    this->all_events.push_back(event);
    writeToFileAdmin();
}

void RepositoryAdmin::delete2 (string title)
{
   int sem=0;
   for(auto i: this->all_events)
   {
       if(i.getTitle() == title)
       {
           all_events.erase(all_events.begin()+getindex(title));
           sem = 1;
       }

   }
   if(sem == 0)
       throw deleteNonExisting();

   writeToFileAdmin();
}


void RepositoryAdmin::update2(int index,  Event &event)
{
    int sem=0;
    for(auto i: this->all_events)
    {
        if(i.getTitle() == event.getTitle())
        {
            sem = 1;
        }

    }
    if(sem == 0)
        throw deleteNonExisting();
    this->all_events[index] = event;
    writeToFileAdmin();
}

vector<Event> RepositoryAdmin::getelements()
{
    return all_events;
}

int RepositoryAdmin::getsize()
{
    return this->all_events.size();
}

int RepositoryAdmin::getindex(const std::string &title) {

    auto it = std::find_if(all_events.begin(), all_events.end(), [&title](Event event) {
        return event.getTitle() == title;
    });

    if (it != all_events.end()) {
        return distance(all_events.begin(), it);
    }
    return -1;
    /*
    int i;
    for(i=0;i<this->getsize();i++)
    {
        if (title == all_events[i].getTitle())
            return i;
    }
    return -1;*/
}


int RepositoryAdmin::getindexuser(const std::string &title) {

    auto it = std::find_if(user_events.begin(), user_events.end(), [&title](Event event) {
        return event.getTitle() == title;
    });

    if (it != user_events.end()) {
        return distance(user_events.begin(), it);
    }
    return -1;

}

Event RepositoryAdmin::getElement(const vector<Event> &arr, int index)
{
    return arr[index];
}

void RepositoryAdmin::add_user(Event event)
{

    int sem = 1;
    for(auto i:user_events)
    {
        if(i.getTitle()  == event.getTitle())
            sem = 0;
    }
    if (sem == 0)
        throw std::exception();
    else
    {

        event.setNumberOfPeople(event.getNumberOfPeople()+1);
      //  all_events.getElement(all_events, all_events.getindex(event.getTitle())).setNumberOfPeople(event.getNumberOfPeople()+1) ;
     //   Event elem2 = {event.getTitle(), event.getDescription(), event.getLink(),event.getDatetime(),event.getNumberOfPeople()+1};
      //  int index = getindex(event.getTitle());
      //  all_events.update1(index,elem2);
        this->user_events.push_back(event);


    }
}

void RepositoryAdmin::delete_user(std::string &title) {
    int index = getindex(title);
    if(index < 0 || index > this->getsize())
        throw deleteNonExisting();
    user_events.erase(user_events.begin()+index);

}

vector<Event> RepositoryAdmin::getelementsUser() {
    return user_events;
}

int RepositoryAdmin::getsizeUser() {
    return this->user_events.size();
}




void RepositoryAdmin::readFromFile() {

    ifstream file(this->filename);

    if (!file.is_open())
        throw FileException("The file could not be opened!");

    Event s;
    while (file >> s)
        this->all_events.push_back(s);

    file.close();
}

void RepositoryAdmin::writeToFileAdmin() {

    ofstream file(this->filename);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    for (auto s : this->all_events)
    {
        file << s;
    }

    file.close();
}

void RepositoryAdmin::writeToFile() {

    ofstream file(this->filename2);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    for (auto s : this->user_events)
    {
        file << s;
    }

    file.close();
}

void RepositoryAdmin::saveToFile() {
  //  this->user_events;
    this->writeToFile();

}

void RepositoryAdmin::clear_user() {


}
