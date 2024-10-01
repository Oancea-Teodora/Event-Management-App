#pragma once

#include <QWidget>
#include <QPushButton>
#include "Service.h"
#include "TableMode.h"
#include <QLineEdit>
#include <QListWidget>
#include <QShortcut>
#include "Repository.h"
#include <qtableview.h>

class GUI : public QWidget {

private:
    ServiceAdmin *serv;
  //  RepositoryAdmin& repo;
    int opp{};

    //AdminWidget *adminWidget;
    //UserWidget *userWidget;
    void buildGui();

    QPushButton* addButton{};

public:
    GUI();

    void html_menu();

    void csv_menu();

    void admin_menu();

    void user_menu();

    void handleItemClicked(QListWidgetItem* item);

    void add();

    void delete1();

    void update1();

    void show1();

    void show_given_month();

    void show_user_events();

    void delete_user();

    void open();

    void save();

    void show_Event(Event &elem);

    void plot();

    void undo();

    void redo();

    void openTableView();

    QLineEdit *titleEdit;
    QLineEdit *descriptionEdit;
    QLineEdit *linkEdit;
    QLineEdit *number_of_peopleEdit;
    QLineEdit *dayEdit;
    QLineEdit *monthEdit;
    QLineEdit *timeEdit;
    QLineEdit *input;
    QShortcut* undoShortcut, *redoShortcut;

    QTableView* shoppingBasketTableView;
    TableMode* tableMode;

    int columnCount = 6;
    int rowCount = 0;

    void show_given_month1();

    void onTableSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};
