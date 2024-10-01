#pragma once
#include "Repository.h"
//#include <Windows.h>

class HTML_Repo : public RepositoryAdmin {

public:
    HTML_Repo(string filename, string filename2);
    void writeToFile() override;

};
