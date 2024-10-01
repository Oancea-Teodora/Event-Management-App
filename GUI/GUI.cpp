
#include <QLabel>
#include <QStackedLayout>
#include <QListWidget>
#include "GUI.h"
#include <qlayout.h>
#include <QPushButton>
#include "HTML_Repo.h"
#include "CSV_Repo.h"
#include <QDialog>
#include <QTableWidget>
#include <QMessageBox>
#include <QEventLoop>
#include "Event.h"
#include "Exceptions.h"
#include "Repository.h"
#include <QtGraphs/QBarSet>
#include <QtGraphs/QBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QBarSeries>
#include <QShortcut>
#include <QAbstractListModel>
#include <QHeaderView>


void GUI::buildGui() {

    auto* mainLayout = new QVBoxLayout{this};

    auto *html_button = new QPushButton("HTML");
    auto *csv_button = new QPushButton("CSV");

    mainLayout->addWidget(html_button,1);
    mainLayout->addWidget(csv_button,1);

    connect(html_button, &QPushButton::clicked, this, &GUI::html_menu);
    connect(csv_button, &QPushButton::clicked, this, &GUI::csv_menu);

    setLayout(mainLayout);



}

GUI::GUI() : serv(){

    serv = new ServiceAdmin("test");
    this->buildGui();
}

void GUI::html_menu() {

    HTML_Repo *htm = new HTML_Repo("C:\\Users\\teodo\\Documents\\GitHub\\oop-a6-7-915-Oancea-Teodora\\input.txt", "test");
    serv->addrepo(htm);

    QDialog *pop = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout{pop};

    auto *admin = new QPushButton("Admin menu");
    auto *user = new QPushButton("User menu");

    connect(admin, &QPushButton::clicked, this, &GUI::admin_menu);
    connect(user, &QPushButton::clicked, this, &GUI::user_menu);

    layout->addWidget(admin,1);
    layout->addWidget(user,1);

    pop->setLayout(layout);
    pop->exec();



}

void GUI::csv_menu() {
    CSV_Repo *csv = new CSV_Repo("C:\\Users\\teodo\\Documents\\GitHub\\oop-a6-7-915-Oancea-Teodora\\input.txt", "test");
    serv->addrepo(csv);

    QDialog *pop = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout{pop};

    auto *admin = new QPushButton("Admin menu");
    auto *user = new QPushButton("User menu");

    connect(admin, &QPushButton::clicked, this, &GUI::admin_menu);
    connect(user, &QPushButton::clicked, this, &GUI::user_menu);

    layout->addWidget(admin,1);
    layout->addWidget(user,1);

    pop->setLayout(layout);
    pop->exec();
}



void GUI::admin_menu() {

    QDialog *pop = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout{pop};

    QListWidget list;
  //  this->undoShortcut = new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z), this);
   // this->redoShortcut = new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_Y), this);

    this->undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), pop);
    this->redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), pop);


    auto *e1 = new QListWidgetItem("1 - Add an event", &list);
    auto *e2 = new QListWidgetItem("2 - Delete an event", &list);
    auto *e3 = new QListWidgetItem("3 - Update an event", &list);
    auto *e4 = new QListWidgetItem("4 - Show all the events", &list);
    auto *e5 = new QListWidgetItem("5 - Plot", &list);
    auto *e6 = new QListWidgetItem("6 - Undo", &list);
    auto *e7 = new QListWidgetItem("7 - Redo", &list);

    connect(&list, &QListWidget::itemClicked, this, &GUI::handleItemClicked);
    connect(this->undoShortcut, &QShortcut::activated, this, &GUI::undo);
    connect(this->redoShortcut, &QShortcut::activated, this, &GUI::redo);


    layout->addWidget(&list);

    pop->setLayout(layout);
    pop->exec();

}

void GUI::user_menu() {

    QDialog *pop = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout{pop};
  //  pop->setWindowModality(Qt::NonModal);
  //  QVBoxLayout *layout = new QVBoxLayout{pop};

    QListWidget list;

    auto *e1 = new QListWidgetItem("1 - Show the events for a given month", &list);
    auto *e2 = new QListWidgetItem("2 - Show the events in your list", &list);
    auto *e3 = new QListWidgetItem("3 - Delete an event from your list", &list);
    auto *e4 = new QListWidgetItem("4 - Save and open to file the list of your events", &list);
    auto *e5 = new QListWidgetItem("5 - Open tableview", &list);

    layout->addWidget(&list);

    connect(&list, &QListWidget::itemClicked, this, &GUI::handleItemClicked);

    pop->setLayout(layout);
    pop->exec();
}

void GUI::handleItemClicked(QListWidgetItem* item) {
    if (item->text() == "1 - Add an event") {
        this->add();
    } else if (item->text() == "2 - Delete an event") {
        this->delete1();
    } else if (item->text() == "3 - Update an event") {
       this->update1();
    } else if (item->text() == "4 - Show all the events") {
        this->show1();
    } else if (item->text() == "5 - Plot") {
        this->plot();
    } else if (item->text() == "6 - Undo") {
        this->undo();
    } else if (item->text() == "7 - Redo") {
        this->redo();
    } else if (item->text() == "1 - Show the events for a given month") {
        this->show_given_month();
    } else if (item->text() == "2 - Show the events in your list") {
        this->show_user_events();
    } else if (item->text() == "3 - Delete an event from your list") {
        this->delete_user();
    } else if (item->text() == "4 - Save and open to file the list of your events") {
        this->save();
    } else if (item->text() == "5 - Open tableview") {
        this->openTableView();
    }
}

void GUI::add() {
    QDialog *pop = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout{pop};

    layout->addWidget(new QLabel("Title:"));
    this->titleEdit= new QLineEdit{};
    layout->addWidget(titleEdit);

    layout->addWidget(new QLabel("Description:"));
    this->descriptionEdit= new QLineEdit{};
    layout->addWidget(descriptionEdit);

    layout->addWidget(new QLabel("Link:"));
    this->linkEdit= new QLineEdit{};
    layout->addWidget(linkEdit);

    layout->addWidget(new QLabel("Number of People:"));
    this->number_of_peopleEdit= new QLineEdit{};
    layout->addWidget(number_of_peopleEdit);

    layout->addWidget(new QLabel("Day:"));
    this->dayEdit= new QLineEdit{};
    layout->addWidget(dayEdit);

    layout->addWidget(new QLabel("Month:"));
    this->monthEdit= new QLineEdit{};
    layout->addWidget(monthEdit);

    layout->addWidget(new QLabel("Time:"));
    this->timeEdit= new QLineEdit{};
    layout->addWidget(timeEdit);

    QPushButton *addButton = new QPushButton("Add Event");
    layout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, [this, pop]() {
        try {
            QString title = this->titleEdit->text();
            QString description = this->descriptionEdit->text();
            QString link = this->linkEdit->text();
            QString numberOfPeople = this->number_of_peopleEdit->text();
            QString day = this->dayEdit->text();
            QString month = this->monthEdit->text();
            QString time = this->timeEdit->text();
            Event event = Event(title.toStdString(), description.toStdString(), link.toStdString(),
                                {time.toInt(), day.toInt(), month.toInt()}, numberOfPeople.toInt());

            this->serv->add3(event);
            pop->accept();
        }
        catch (RepositoryException &ex)
        {
            QMessageBox::warning(pop, "Add Error", ex.what());
        }

    });

    pop->setLayout(layout);
    pop->exec();

}

void GUI::delete1() {

    QDialog *pop = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout{pop};

    layout->addWidget(new QLabel("Title:"));
    QLineEdit *titleEdit = new QLineEdit();
    layout->addWidget(titleEdit);

    QPushButton *deleteButton = new QPushButton("Delete Event");
    layout->addWidget(deleteButton);

    connect(deleteButton, &QPushButton::clicked, this, [this, pop, titleEdit]() {
        QString title = titleEdit->text();
        try
        {
            serv->delete3(title.toStdString());
            pop->accept();
        }
        catch (RepositoryException &ex)
        {
            QMessageBox::warning(pop, "Deletion Error", ex.what());
        }

    });
    pop->setLayout(layout);
    pop->exec();
}

void GUI::update1() {
    QDialog *pop = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout{pop};

    layout->addWidget(new QLabel("Title of the event to be updated:"));
    QLineEdit *titleEdit = new QLineEdit();
    layout->addWidget(titleEdit);

    layout->addWidget(new QLabel("New Description:"));
    QLineEdit *descriptionEdit = new QLineEdit();
    layout->addWidget(descriptionEdit);

    layout->addWidget(new QLabel("New Link:"));
    QLineEdit *linkEdit = new QLineEdit();
    layout->addWidget(linkEdit);

    layout->addWidget(new QLabel("New Hour:"));
    QLineEdit *hourEdit = new QLineEdit();
    layout->addWidget(hourEdit);

    layout->addWidget(new QLabel("New Day:"));
    QLineEdit *dayEdit = new QLineEdit();
    layout->addWidget(dayEdit);

    layout->addWidget(new QLabel("New Month:"));
    QLineEdit *monthEdit = new QLineEdit();
    layout->addWidget(monthEdit);

    layout->addWidget(new QLabel("New Number of People:"));
    QLineEdit *numPeopleEdit = new QLineEdit();
    layout->addWidget(numPeopleEdit);

    QPushButton *updateButton = new QPushButton("Update Event");
    layout->addWidget(updateButton);

    connect(updateButton, &QPushButton::clicked, this, [this, pop, titleEdit, descriptionEdit, linkEdit, hourEdit, dayEdit, monthEdit, numPeopleEdit]() {
        QString title = titleEdit->text();
        QString description = descriptionEdit->text();
        QString link = linkEdit->text();
        int hour = hourEdit->text().toInt();
        int day = dayEdit->text().toInt();
        int month = monthEdit->text().toInt();
        int numPeople = numPeopleEdit->text().toInt();

        int index = serv->getindex(title.toStdString());
        if (index != -1) {
            Event event(title.toStdString(), description.toStdString(), link.toStdString(), {hour, day, month}, numPeople);
            serv->update3(index, event);
        } else {
            QMessageBox::warning(pop, "Update Error", "Event not found!");
        }

        pop->accept();
    });

    pop->setLayout(layout);
    pop->exec();
}

void GUI::show1() {

    QDialog *pop = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout{pop};
    QTableWidget *table = new QTableWidget(pop);

    table->setColumnCount(7);
    QStringList headerLabels;
    headerLabels << "Title" << "Description" << "Link" << "Hour" << "Day" << "Month"<<"People";
    table->setHorizontalHeaderLabels(headerLabels);

    int rowIndex = 0;
    vector<Event> arr = serv->getelements();
    int rowCount = arr.size();
    table->setRowCount(rowCount);
    for (int i = 0; i < serv->getsize(); i++)
    {
        Event elem = arr[i];
        QTableWidgetItem* titleItem = new QTableWidgetItem(elem.getTitle().c_str());
        QTableWidgetItem* descriptionItem = new QTableWidgetItem(elem.getDescription().c_str());
        QTableWidgetItem* linkItem = new QTableWidgetItem(elem.getLink().c_str());
        QTableWidgetItem* hourItem = new QTableWidgetItem(QString::number(elem.getDatetime().time));
        QTableWidgetItem* dayItem = new QTableWidgetItem(QString::number(elem.getDatetime().date_day));
        QTableWidgetItem* monthItem = new QTableWidgetItem(QString::number(elem.getDatetime().date_month));
        QTableWidgetItem* peopleItem = new QTableWidgetItem(QString::number(elem.getNumberOfPeople()));


        table->setItem(rowIndex, 0, titleItem);
        table->setItem(rowIndex, 1, descriptionItem);
        table->setItem(rowIndex, 2, linkItem);
        table->setItem(rowIndex, 3, hourItem);
        table->setItem(rowIndex, 4, dayItem);
        table->setItem(rowIndex, 5, monthItem);
        table->setItem(rowIndex, 6, peopleItem);

        rowIndex++;
    }
    QHeaderView* header = table->horizontalHeader();
    QHeaderView* verticalHeader = table->verticalHeader();

    table->resizeRowsToContents();
    table->resizeColumnsToContents();
    layout->addWidget(table);
    pop->setLayout(layout);
    pop->resize(1000,750);
    pop->exec();
}

void GUI::show_given_month() {
    QDialog *pop = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(pop);

    layout->addWidget(new QLabel("Choose the month:"));
    QLineEdit *monthEdit = new QLineEdit();
    layout->addWidget(monthEdit);

    QPushButton *search = new QPushButton("Search");
    layout->addWidget(search);

    QPushButton *add = new QPushButton("Add");
    layout->addWidget(add);

    QPushButton *next = new QPushButton("Next");
    layout->addWidget(next);

    int idx = 0;
    QString monthText = monthEdit->text();
    string month = monthText.toStdString();
    vector<Event> arr = serv->filter_month(month);

    connect(search, &QPushButton::clicked, pop, [this, &monthEdit, &layout]()
    {
        int idx = 0;

        QString monthText = monthEdit->text();
        string month = monthText.toStdString();
        vector<Event> arr = serv->filter_month(month);
        if(arr.size() == 0)
        {
            QMessageBox::warning(this, "Invalid!", "Please enter another month!");
            return ;
        }

        QDialog *eventDialog = new QDialog(this);
        QVBoxLayout *eventLayout = new QVBoxLayout(eventDialog);

        auto elem = arr[idx];

        layout->addWidget(new QLabel(QString::fromStdString("Title: " + elem.getTitle())));
        layout->addWidget(new QLabel(QString::fromStdString("Description: " + elem.getDescription())));
        layout->addWidget(new QLabel(QString::fromStdString("Link: " + elem.getLink())));
        layout->addWidget(new QLabel(QString::number(elem.getDatetime().time)));
        layout->addWidget(new QLabel(QString::number(elem.getDatetime().date_day)));
        layout->addWidget(new QLabel(QString::number(elem.getDatetime().date_month)));
        layout->addWidget(new QLabel(QString::number(elem.getNumberOfPeople())));

        string command = "start " + elem.getLink();
        system(command.c_str());

        layout->addWidget(new QLabel("Do you want to add it to your list?"));

     //   QPushButton *add = new QPushButton("Add");
       // eventLayout->addWidget(add);

     //   QPushButton *next = new QPushButton("Next");
     //   eventLayout->addWidget(next);

        //eventDialog->setLayout(eventLayout);
        //eventDialog->exec();



    });

    connect(add, &QPushButton::clicked, pop, [this, &arr, &idx]()
    {
        try {
            this->serv->add_user(arr[idx]);
        }
        catch (const std::exception &ex) {
            QMessageBox::warning(this, "It already exists!", ex.what());
        }



    });

    connect(next, &QPushButton::clicked, pop, [this, &idx, &arr, &layout]()
    {
        idx++;
        if(idx>arr.size()-1)
            idx=0;

        QDialog *eventDialog = new QDialog(this);
        QVBoxLayout *eventLayout = new QVBoxLayout(eventDialog);

        auto elem = arr[idx];

        layout->addWidget(new QLabel(QString::fromStdString("Title: " + elem.getTitle())));
        layout->addWidget(new QLabel(QString::fromStdString("Description: " + elem.getDescription())));
        layout->addWidget(new QLabel(QString::fromStdString("Link: " + elem.getLink())));
        layout->addWidget(new QLabel(QString::number(elem.getDatetime().time)));
        layout->addWidget(new QLabel(QString::number(elem.getDatetime().date_day)));
        layout->addWidget(new QLabel(QString::number(elem.getDatetime().date_month)));
        layout->addWidget(new QLabel(QString::number(elem.getNumberOfPeople())));

        string command = "start " + elem.getLink();
        system(command.c_str());

        layout->addWidget(new QLabel("Do you want to add it to your list?"));

       // QPushButton *add = new QPushButton("Add");
       // eventLayout->addWidget(add);

       // QPushButton *next = new QPushButton("Next");
       // eventLayout->addWidget(next);

    });

    pop->setLayout(layout);
    pop->exec();
}


void GUI::show_user_events() {

    vector<Event> arr = serv->getelementsUser();

    QDialog *pop = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(pop);
    QTableWidget *table = new QTableWidget(pop);

    table->setColumnCount(7);
    QStringList headerLabels;
    headerLabels << "Title" << "Description" << "Link" << "Hour" << "Day" << "Month" << "People";
    table->setHorizontalHeaderLabels(headerLabels);

    int rowCount = arr.size();
    table->setRowCount(rowCount);

    for (int i = 0; i < rowCount; i++) {
        Event elem = arr[i];
        QTableWidgetItem* titleItem = new QTableWidgetItem(elem.getTitle().c_str());
        QTableWidgetItem* descriptionItem = new QTableWidgetItem(elem.getDescription().c_str());
        QTableWidgetItem* linkItem = new QTableWidgetItem(elem.getLink().c_str());
        QTableWidgetItem* hourItem = new QTableWidgetItem(QString::number(elem.getDatetime().time));
        QTableWidgetItem* dayItem = new QTableWidgetItem(QString::number(elem.getDatetime().date_day));
        QTableWidgetItem* monthItem = new QTableWidgetItem(QString::number(elem.getDatetime().date_month));
        QTableWidgetItem* peopleItem = new QTableWidgetItem(QString::number(elem.getNumberOfPeople()));

        table->setItem(i, 0, titleItem);
        table->setItem(i, 1, descriptionItem);
        table->setItem(i, 2, linkItem);
        table->setItem(i, 3, hourItem);
        table->setItem(i, 4, dayItem);
        table->setItem(i, 5, monthItem);
        table->setItem(i, 6, peopleItem);
    }

    table->resizeRowsToContents();
    table->resizeColumnsToContents();
    layout->addWidget(table);


    QPushButton *closeButton = new QPushButton("Close");
    layout->addWidget(closeButton);
    connect(closeButton, &QPushButton::clicked, pop, &QDialog::accept);

    pop->setLayout(layout);
    pop->resize(1000, 750);
    pop->exec();
}

void GUI::delete_user() {

    QDialog *pop = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout{pop};

    layout->addWidget(new QLabel("Title:"));
    QLineEdit *titleEdit = new QLineEdit();
    layout->addWidget(titleEdit);

    QPushButton *deleteButton = new QPushButton("Delete Event");
    layout->addWidget(deleteButton);

    connect(deleteButton, &QPushButton::clicked, this, [this, pop, titleEdit]() {
        QString title = titleEdit->text();
        try
        {
            serv->delete_user(title.toStdString());
            pop->accept();
        }
        catch (RepositoryException &ex)
        {
            QMessageBox::warning(pop, "Deletion Error", ex.what());
        }

    });
    pop->setLayout(layout);
    pop->exec();
}

void GUI::open() {
    QDialog *pop = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout{pop};
    try
    {
        serv->saveToFile();

        if (serv->getelementsUser().empty())
        {
            layout->addWidget(new QLabel("The list is empty!"));
            return;
        }
    }
    catch (exception &ex)
    {
        QMessageBox::warning(pop, "Save Error", ex.what());
    }
    pop->setLayout(layout);
    pop->exec();

}

void GUI::save() {

    for(auto i:serv->getrepos())
    {
        for(auto j:serv->getelementsUser())
            if(i->getindexuser(j.getTitle()) == -1)
                i->add_user(j);
        i->saveToFile();
    }
}

void GUI::show_Event(Event &elem) {


}

void GUI::plot() {
    QDialog *pop = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout{pop};

    QBarSeries *ser = new QBarSeries();

    vector<Event> arr = serv->getelements();
    for(int i=0;i<arr.size();i++)
    {
        QBarSet *set = new QBarSet(QString::fromStdString(arr[i].getTitle()));
        *set<<arr[i].getDatetime().date_month;
        ser->append(set);
    }

    QChart *chart = new QChart();
    chart->addSeries(ser);
    chart->setTitle("Name of event");

    QBarCategoryAxis *y = new QBarCategoryAxis();
    y->append("Statistics");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).append(y);

    pop->setWindowTitle("Data Plot");
    pop->resize(500,500);

    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartview);
    pop->setLayout(layout);
    pop->exec();


}

void GUI::undo() {
    try
    {
        this->serv->undoAdmin();
    }
    catch(...)
    {
        QMessageBox::critical(this, "Error", "There are no more undos");
        return;
    }

}

void GUI::redo()
{
    try
    {
        this->serv->redoAdmin();
    }
    catch(...)
    {
        QMessageBox::critical(this, "Error", "There are no more redos");
        return;
    }
}

void GUI::openTableView() {

    QDialog *tableViewDialog = new QDialog(this);  // Use QDialog to manage modal views
    tableViewDialog->setWindowTitle("View List");
    QVBoxLayout *layout = new QVBoxLayout(tableViewDialog);

    QTableView *tableView = new QTableView(tableViewDialog);
    TableMode *model = new TableMode(serv->getRepo());

    tableView->setModel(model);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);

    layout->addWidget(tableView);

    // Add a close button
    QPushButton *closeButton = new QPushButton("Close", tableViewDialog);
    connect(closeButton, &QPushButton::clicked, tableViewDialog, &QDialog::accept);
    layout->addWidget(closeButton);

    tableViewDialog->setLayout(layout);
    tableViewDialog->resize(800, 600);
    tableViewDialog->exec();  // Use exec for modal dialog
  /*  QDialog *tableViewDialog = new QDialog(this);
    tableViewDialog->setWindowTitle("View List");
    QVBoxLayout *layout = new QVBoxLayout(tableViewDialog);

    QTableView *tableView = new QTableView(tableViewDialog);
    this->tableMode = new TableMode(serv->getRepo());
    tableView->setModel(this->tableMode);

    // Set selection behavior to select entire rows and connect the selection change signal
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Connect the signal for item selection
    connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &GUI::onTableSelectionChanged);

    layout->addWidget(tableView);
    QPushButton *closeButton = new QPushButton("Close", tableViewDialog);
    connect(closeButton, &QPushButton::clicked, tableViewDialog, &QDialog::accept);
    layout->addWidget(closeButton);

    tableViewDialog->setLayout(layout);
    tableViewDialog->resize(800, 600);
    tableViewDialog->exec();
*/

}

void GUI::onTableSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);  // Mark deselected as unused to avoid compiler warnings

    // Check if there is any selection
    if (!selected.indexes().isEmpty()) {
        QModelIndex index = selected.indexes().first(); // Get the first selected item index
        if (index.isValid()) {
            // Possibly store the selected row index for use in actions like deleting
            int currentSelectedRow = index.row(); // Assume currentSelectedRow is declared in GUI.h
        }
    }
}
