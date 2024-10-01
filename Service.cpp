#include "Service.h"
#include <algorithm>
#include "Exceptions.h"

ServiceAdmin::ServiceAdmin(string filename) : repo("C:\\Users\\teodo\\Documents\\GitHub\\oop-a6-7-915-Oancea-Teodora\\input.txt", "test"){

}

void ServiceAdmin::generate() {

}

void ServiceAdmin::add3(Event &event)
{
    //this->repo.add2(event);
    repo.add2(event);
    Action *currentAction = new addAction(this->repo, event);
    this->undoStack.push_back(currentAction);
    this->redoStack.clear();
}

void ServiceAdmin::delete3(std::string title)
{
    Event deleted = repo.getElement(repo.getelements(), repo.getindex(title));
    repo.delete2(title);
    Action *currentAction = new deleteAction(this->repo, deleted);
    this->undoStack.push_back(currentAction);
    this->redoStack.clear();
}

void ServiceAdmin::update3(int index,  Event &event)
{
    Event old = repo.getElement(repo.getelements(), index);
    repo.update2(index, event);
    Action *currentAction = new updateAction(this->repo,old ,event);
    this->undoStack.push_back(currentAction);
    this->redoStack.clear();
}


vector<Event> ServiceAdmin::getelements()
{
    return repo.getelements();
}

int ServiceAdmin::getsize()
{
    return repo.getsize();
}

int ServiceAdmin::getindex(std::string title) {
    return repo.getindex(title);
}


Event ServiceAdmin::getElement(const vector<Event>& arr, int index) {
    return repo.getElement(arr, index);
}





void ServiceAdmin::add_user(Event event) {
    repo.add_user(event);


}

void ServiceAdmin::delete_user(std::string title) {
    repo.delete_user(title);

}

vector<Event> ServiceAdmin::filter_month(const std::string &month) {
    vector<Event> arr = repo.getelements();
    vector<Event> arr2(0);
     if(month.empty())
     {
         return repo.getelements();
     }
     else
     {
         int m = stoi(month);
         for(int i=0;i<arr.size();i++)
         {
             Event event = this->repo.getElement(arr,i);
             if(event.getDatetime().date_month == m)
             {
                 arr2.push_back(event);
             }
         }
         return arr2;
     }
}

vector<Event> ServiceAdmin::getelementsUser() {
    return repo.getelementsUser();
}

int ServiceAdmin::getsizeUser() {
    return repo.getsizeUser();
}

void ServiceAdmin::saveToFile() {

    repo.saveToFile();
}

void ServiceAdmin::openEvents(const string& type) {


}

void ServiceAdmin::addrepo(RepositoryAdmin *rep) {
    allrepos.push_back(rep);

}

vector<RepositoryAdmin *> ServiceAdmin::getrepos() {
    return allrepos;
}

void ServiceAdmin::undoLastAction(vector<Action *> &currentUndoStack, vector<Action *> &currentRedoStack) {
    if(currentUndoStack.empty())
        throw FileException("No more undo");
    Action* current = currentUndoStack.back();
    current->undo();
    currentRedoStack.push_back(current);
    currentUndoStack.pop_back();
}

void ServiceAdmin::redoLastAction(vector<Action *> &currentUndoStack, vector<Action *> &currentRedoStack) {
    if(currentRedoStack.empty())
        throw FileException("No more redo");
    Action* current = currentRedoStack.back();
    current->redo();
    currentUndoStack.push_back(current);
    currentRedoStack.pop_back();
}

void ServiceAdmin::undoAdmin() {
    this->undoLastAction(this->undoStack, this->redoStack);

}

void ServiceAdmin::redoAdmin() {
    this->redoLastAction(this->undoStack, this->redoStack);

}

 TableMode ServiceAdmin::getRepo() {
    return this->repo;
}




