#include <Windows.h>
#include <fstream>
#include "CSV_Repo.h"
#include <shellapi.h>

CSV_Repo::CSV_Repo(string filename, string filename2) : RepositoryAdmin(filename, filename2) {

}

void CSV_Repo::writeToFile() {
    ofstream csv_out(this->filename2+".csv");
    if(!csv_out.is_open())
        throw exception();
    for(auto i:getelementsUser())
        csv_out<<i;
    csv_out.close();
    string file = filename2+".csv";

    ShellExecuteA(NULL,
                  "open",
                  "C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE",
                  file.c_str(),
                  NULL,
                  SW_MAXIMIZE
    );
}
