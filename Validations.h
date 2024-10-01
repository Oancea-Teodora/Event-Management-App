#pragma once

#include <string>

using namespace std;

class Validations {

public:
    void month(int month);
    void day(int day);
    void hour(int hour);
    void people(int people);
    void empty(const string& str);

};

