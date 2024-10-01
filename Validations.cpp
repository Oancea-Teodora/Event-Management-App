
#include "Exceptions.h"
#include "Validations.h"

void Validations::month(int month) {

    if(month<1 || month>12)
        throw RepositoryException((string &) "This not a valid month!");
}

void Validations::day(int day) {
    if(day < 1 || day > 31)
        throw RepositoryException((string &) "This not a valid day!");


}

void Validations::hour(int hour) {
    if(hour < 1 || hour > 24)
        throw RepositoryException((string &) "This not a valid hour!");
}

void Validations::people(int people) {
    if(people<0)
        throw RepositoryException((string &) "This not a valid number of people!");
}

void Validations::empty(const string& str) {
    if(str == "")
        throw RepositoryException((string &) "This is an empty string!");



}
