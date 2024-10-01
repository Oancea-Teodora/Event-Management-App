
#include "Exceptions.h"

FileException::FileException(const string &msg) {
    this->massage = msg;
}

const char *FileException::what() {
    return massage.c_str();
}

RepositoryException::RepositoryException(string &msg) : message{msg} {

}

const char *RepositoryException::what() {
    return this->message.c_str();
}

RepositoryException::RepositoryException() : exception{}, message{""} {

}

const char *DuplicateEventException::what() {
    return "There is another event with the same title!\n";
}

const char *deleteNonExisting::what() {
    return "It doesn't exist!\n";
}
