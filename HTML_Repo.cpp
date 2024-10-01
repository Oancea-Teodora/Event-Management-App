#include <Windows.h>
#include <fstream>
#include "HTML_Repo.h"



HTML_Repo::HTML_Repo(string filename, string filename2) : RepositoryAdmin(filename, filename2) {


}

void HTML_Repo::writeToFile() {
    ofstream html_out(this->filename2+".html");
    if(!html_out.is_open())
        throw exception();
    html_out << "<!DOCTYPE html> <html> <head> <title> Events </title> </head > <body> <table border=\"1\">";
    html_out << "<tr> <td> Index </td> <td> Title </td> <td> Description </td> <td> Link </td> <td> Time </td> <td> Day </td> <td> Month </td> <td> Number of people </td> </tr>";
    int index = 0;
    auto events = getelementsUser();
    for (auto event : events)
        html_out << "<tr> <td>" << ++index << "</td> <td>" << event.getTitle() << "</td> <td>" << event.getDescription() << "</td><td><a href=\"" << event.getLink()<<"\">Link</a></td><td>"<<event.getDatetime().time << "</td> <td>"<<event.getDatetime().date_day << "</td> <td>"<<event.getDatetime().date_month << "</td> <td>"<<event.getNumberOfPeople()<<"</td> </tr>";
    html_out << "</table> </body> </html>";

    html_out.close();

   // std::string currentPath = std::filesystem::current_path().string();
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    std::string path(buffer);
    path += "\\" + filename2+".html";
    std::string command = "start \"\" \"" + path + "\"";
    system(command.c_str());
}
