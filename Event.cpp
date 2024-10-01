#include <string>
#include "Event.h"
#include "Utils.h"
#include <vector>
#include <iostream>

using namespace std;

Event::Event(const std::string& title, const std::string& description, const std::string& link, DateTimeStruct datetime, int numberOfPeople)
{
    this->title = title;
    this->description = description;
    this->link = link;
    this->datetime = datetime;
    this->numberOfPeople = numberOfPeople;
}

std::string Event::getTitle() const {
    return this->title;
}

std::string Event::getDescription() const {
    return this->description;
}

std::string Event::getLink() const {
    return this->link;
}

DateTimeStruct Event::getDatetime() const
{
    return this->datetime;
}

int Event::getNumberOfPeople() const
{
    return this->numberOfPeople;
}

void Event::setTitle(std::string newTitle)
{
    this->title = newTitle;
}

void Event::setDescription(std::string newDescription)
{
    this->description = newDescription;
}

void Event::setLink(std::string newLink)
{
    this->link = newLink;
}

void Event::setDatetime(DateTimeStruct newDatetime)
{
    this->datetime = newDatetime;
}

void Event::setNumberOfPeople(int newNumberOfPeople)
{
    this->numberOfPeople = newNumberOfPeople;
}

std::istream &operator>>(std::istream &is, Event &s) {
    string line;
    getline(is, line);

    vector<string> tokens = tokenize(line, ',');
    if (tokens.size() != 5)
        return is;

    s.title = tokens[0];
    s.description = tokens[1];
    s.link = tokens[2];

// get date
    vector<string> durationTokens = tokenize(tokens[3], ' ');

    s.datetime = DateTimeStruct { stoi(durationTokens[0]), stoi(durationTokens[1]),stoi(durationTokens[2]) };

    s.numberOfPeople = stoi(tokens[4]);

    return is;
}

ostream & operator<<(ostream & os, const Event & s)
{
    os << s.title << "," << s.description << "," << s.link << "," << s.datetime.time<<" "<<s.datetime.date_day<<" "<<s.datetime.date_month<<","<<s.numberOfPeople << "\n";
    return os;
}


