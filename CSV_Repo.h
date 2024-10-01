#pragma once
#include "Repository.h"

class CSV_Repo : public RepositoryAdmin {

public:
    CSV_Repo(string filename, string filename2);
    void writeToFile() override;

};
