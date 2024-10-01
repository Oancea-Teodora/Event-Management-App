#include "UI.h"
#include <iostream>
#include <string>
#include <cstring>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "Exceptions.h"
#include "Validations.h"
#include <cstdlib>
#include <QtWidgets/QDialog>
#include <QtWidgets/QvBoxLayout>
#include <QtWidgets/QLabel>
#include <QtCore/QObject>
#include <QtWidgets/QPushButton>

using namespace std;
UI::UI(): serv(""){
  //  cin.ignore();
}

bool compare(Event i1, Event i2)
{
    return i1.getDatetime().date_month<i2.getDatetime().date_month ||
           (i1.getDatetime().date_month==i2.getDatetime().date_month && i1.getDatetime().date_day<i2.getDatetime().date_day)||
           (i1.getDatetime().date_month==i2.getDatetime().date_month && i1.getDatetime().date_day==i2.getDatetime().date_day && i1.getDatetime().time<i2.getDatetime().time);
}

void UI::start1 ()
{
    char op[100];

    string filename;
    cout << "Output file:\n";
    cin >> filename;
    this->serv = ServiceAdmin(filename);
    string type;
    cout<<"HTML/CSV:\n";
    cin>>type;
    cin.ignore();
    if(type == "HTML")
    {
        HTML_Repo *htm = new HTML_Repo("C:\\Users\\teodo\\Documents\\GitHub\\oop-a6-7-915-Oancea-Teodora\\input.txt", filename);
        serv.addrepo(htm);

    }
    else if(type == "CSV")
    {
        CSV_Repo *csv = new CSV_Repo("C:\\Users\\teodo\\Documents\\GitHub\\oop-a6-7-915-Oancea-Teodora\\input.txt", filename);
        serv.addrepo(csv);
    }
    else
        cout<<"Invalid!\n";


   // serv.generate();
   // cout<<this->serv.getsize()<<"***** \n";
    strcpy(op,"zero");
    while (strcmp(op, "exit")!=0)
    {
        cout<<"Choose admin/user/exit menu\n";
        cin.getline(op,100);

        if (strcmp(op, "admin") == 0)
        {
            cout << "Admin Menu\n";
            cout << "1 - Add an event\n";
            cout << "2 - Delete an event\n";
            cout << "3 - Update an event\n";
            cout << "4 - Show all the events\n";
            cout << "0 - Exit the admin mode\n";
            int opp = -1;
            try
            {
                while (opp != 0)
                {

                    char name_input[100], description_input[100], link_input[100];
                    int num_input, hour, month, day;
                    cout << "Choose your option\n";
                    cin >> opp;
                    if (opp == 1)
                    {
                        try
                        {
                            Validations valid;
                            cin.ignore();

                            cout << "Introduce the name of the event:\n";
                            cin.getline(name_input, 100);
                            valid.empty(name_input);

                            cout << "Introduce the description of the event:\n";
                            cin.getline(description_input, 100);
                            valid.empty(description_input);

                            cout << "Introduce the link of the event:\n";
                            cin.getline(link_input, 100);
                            valid.empty(link_input);

                            cout << "Introduce the hour:\n";
                            cin >> hour;
                            cin.ignore();
                            valid.hour(hour);

                            cout << "Introduce the day:\n";
                            cin >> day;
                            cin.ignore();
                            valid.day(day);

                            cout << "Introduce the month:\n";
                            cin >> month;
                            cin.ignore();
                            valid.month(month);

                            cout << "Introduce the number of people:\n";
                            cin >> num_input;
                            cin.ignore();
                            valid.people(num_input);

                            Event event;
                            event = Event((name_input), (description_input),
                                          (link_input), {hour, day, month}, num_input);

                            serv.add3(event);
                        }
                        catch (RepositoryException &ex) {
                            cout << ex.what() <<"\n";
                        }

                    } else if (opp == 2) {
                        try {
                            cin.ignore();
                            cout << "Introduce the title of the event that will be removed:\n";
                            cin.getline(name_input, 100);
                            serv.delete3((string) name_input);
                        }
                        catch (RepositoryException &ex) {
                            cout << ex.what() <<"\n";
                        }
                    } else if (opp == 3)
                    {
                        try
                        {
                            cin.ignore();
                            cout << "Introduce the title of the event that will be updated:\n";
                            cin.getline(name_input, 100);

                            cout << "Introduce the new description of the event:\n";
                            cin.getline(description_input, 100);

                            cout << "Introduce the new link of the event:\n";
                            cin.getline(link_input, 100);

                            cout << "Introduce the new hour:\n";
                            cin >> hour;

                            cout << "Introduce the new day:\n";
                            cin >> day;

                            cout << "Introduce the new month:\n";
                            cin >> month;

                            cout << "Introduce the new number of people:\n";
                            cin >> num_input;

                            int index = serv.getindex((string) (name_input));

                            Event event = Event(name_input, description_input, link_input, {hour, day, month},
                                                num_input);
                            serv.update3(index, event);
                        }
                        catch (RepositoryException &ex) {
                            cout << ex.what() <<"\n";
                        }
                    } else if (opp == 4) {
                        vector<Event> arr = serv.getelements();
                        int i = 0;
                        for (i = 0; i < serv.getsize(); i++) {
                            Event elem = arr[i];
                            cout << "#" << i + 1 << ". Title: " << elem.getTitle() << "\nDescription: "
                                 << elem.getDescription() << "\nLink: " << elem.getLink() << "\nHour: "
                                 << elem.getDatetime().time << " Day: " << elem.getDatetime().date_day << " Month: "
                                 << elem.getDatetime().date_month << "\nPeople: " << elem.getNumberOfPeople() << '\n';
                            cout << "\n";
                        }
                    } else if (opp == 0)
                        {cin.ignore();
                        break;}

                    else
                        cout << "Invalid option!";

                }
            }
            catch (exception &ex) {
                cout << "Error!\n";
            }
        }
        else if(strcmp(op, "user") == 0)
        {
            cout << "User Menu\n";
            cout << "1 - Show the events for a given month\n";
            cout << "2 - Show the events in your list\n";
            cout << "3 - Delete an event from your list\n";
            cout << "4 - Save to file the list of your events\n";
            cout << "5 - Open the list of events\n";
            cout << "0 - Exit the user mode\n";
            int opp = -1;
            try
            {
                while (opp != 0)
                {
                    cout<<"Choose your option:\n";
                    cin>>opp;
                    if(opp==1)
                    {
                        char month[100], enter[100], ras[100];
                        cout<<"Choose the month:\n";
                        cin.clear();
                        cin.ignore();
                        cin.getline(month, 100, '\n');
                        vector<Event> arr = serv.filter_month(month);

                        int i = 0;
                        strcpy(ras,"bun");
                        while(strcmp(ras,"Exit")!=0)
                        {
                            for (i = 0; i < arr.size(); i++)
                            {
                                try
                                {
                                Event elem = arr[serv.getindex(this->serv.getElement(arr,i).getTitle())];

                                cout << "#" << i + 1 << ". Title: " << elem.getTitle() << "\nDescription: "
                                     << elem.getDescription() << "\nLink: " << elem.getLink() << "\nHour: "
                                     << elem.getDatetime().time << " Day: " << elem.getDatetime().date_day << " Month: "
                                     << elem.getDatetime().date_month << "\nPeople: " << elem.getNumberOfPeople() << '\n';
                                cout << "\n";

                                string command = "start " + elem.getLink();
                                system(command.c_str());

                                cout<<"Do you want to add it to your list? Yes/No/Exit\n";
                                cin.getline(ras,100);
                                if(strcmp(ras,"Yes") == 0)
                                {
                                    serv.add_user(elem);
                                    Event elem2 = {elem.getTitle(), elem.getDescription(), elem.getLink(),elem.getDatetime(),elem.getNumberOfPeople()+1};
                                    int index = serv.getindex(elem.getTitle());
                                    serv.update3(index,elem2);
                                }
                                else if(strcmp(ras,"Exit") == 0)
                                    break;
                                }
                                catch (exception &ex) {
                                    cout << "The event was already added!\n";}
                            }
                            if(arr.size() == 0)
                                strcpy(ras,"Exit");
                        }


                    }
                    else if(opp==2)
                    {
                        vector<Event> arr = serv.getelementsUser();
                       // sort(arr);
                        sort(arr.begin(),arr.end(), compare);
                        int i = 0;
                        for (i = 0; i < serv.getsizeUser(); i++) {
                            Event elem = arr[i];
                            cout << "#" << i + 1 << ". Title: " << elem.getTitle() << "\nDescription: "
                                 << elem.getDescription() << "\nLink: " << elem.getLink() << "\nHour: "
                                 << elem.getDatetime().time << " Day: " << elem.getDatetime().date_day << " Month: "
                                 << elem.getDatetime().date_month << "\nPeople: " << elem.getNumberOfPeople() << '\n';
                            cout << "\n";
                        }
                    }
                    else if(opp == 3)
                    {
                        try {
                            char name[100];
                            cin.ignore();
                            cout << "Introduce the title of the event that will be removed from the user:\n";
                            cin.getline(name, 100);
                            serv.delete_user((string)(name));

                            int index = serv.getindex(name);
                            vector<Event> arr = serv.getelements();
                            Event elem = serv.getElement(arr, index);
                            Event elem2 = {elem.getTitle(), elem.getDescription(), elem.getLink(),elem.getDatetime(),elem.getNumberOfPeople()-1};
                            serv.update3(index, elem2);

                        }
                        catch (exception &ex) {
                            cout << "The event doesn't exist!\n";
                        }
                    }
                    else if(opp == 4)
                    {
                       // cin.ignore();
                        this->saveToFile();
                    }
                    else if(opp == 5)
                    {
                        for(auto i:serv.getrepos())
                        {
                            for(auto j:serv.getelementsUser())
                                i->add_user(j);
                            i->saveToFile();
                        }
                    }
                    else if (opp == 0)
                    {
                        cin.ignore();
                        break;
                    }
                }
            }
            catch (exception &ex) {
                cout << "Error!\n";
            }
        }
    }
}

void UI::saveToFile() {
   // string filename;
    //cout<<"Introduce the name of the file:\n";
    //cin>>filename;
    try
    {
        this->serv.saveToFile();

        if (serv.getelementsUser().empty())
        {
            cout << "Playlist cannot be displayed!" << endl;
            return;
        }
    }
    catch (exception &ex)
    {
       cout << "Error!\n";
    }

}
