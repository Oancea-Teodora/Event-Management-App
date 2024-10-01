#pragma once
#include <string>

typedef struct
{
    int time;
    int date_day;
    int date_month;
}DateTimeStruct;

class Event {

private:
    std::string title, description, link;
    int numberOfPeople;
    DateTimeStruct datetime;

public:
    Event(): title(), description(), link(), datetime({0,0, 0}), numberOfPeople(0) {

    }

    Event(const std::string& title, const std::string& description, const std::string& link, DateTimeStruct datetime, int numberOfPeople);

    std::string getTitle() const;

    std::string getDescription() const;

    std::string getLink() const;

    DateTimeStruct getDatetime() const;

    int getNumberOfPeople() const;

    void setTitle(std::string newTitle);

    void setDescription(std::string newDescription);

    void setLink(std::string newLink);

    void setDatetime(DateTimeStruct newDatetime);

    void setNumberOfPeople(int newNumberOfPeople);

    friend std::istream& operator>>(std::istream& is, Event& s);
    friend std::ostream& operator<<(std::ostream& os, const Event& s);
};
