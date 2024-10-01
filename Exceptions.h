#pragma once

#include <exception>
#include <string>

using namespace std;
class FileException : public exception{

protected:
    string massage;

public:
    FileException(const string &msg);
    virtual const char* what();

};

class RepositoryException : public exception
{
protected:
    string message;
public:
    RepositoryException();
    explicit RepositoryException(string &msg);
    ~RepositoryException() override = default;
    virtual const char* what();
};

class DuplicateEventException : public RepositoryException
{
    const char* what() override;
};

class deleteNonExisting : public  RepositoryException
{
    const char* what() override;
};