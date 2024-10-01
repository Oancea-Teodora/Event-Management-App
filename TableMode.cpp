//
// Created by teodo on 6/2/2024.
//

#include "TableMode.h"
#include <QFont>
#include <QBrush>
#include "TableMode.h"
#include <QPixmap>
#include <QPainter>

TableMode::TableMode(RepositoryAdmin &repo, QObject *parent): repo{repo}, QAbstractTableModel{parent}{
    this->eventCount = this->repo.getelementsUser().size();
}

TableMode::~TableMode() {

}

int TableMode::rowCount(const QModelIndex &parent) const {
    int eventsNumber =  this->repo.getelementsUser().size();
    return eventsNumber;
}

int TableMode::columnCount(const QModelIndex &parent) const {
    return 7;
}

QVariant TableMode::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();

    if( role == Qt::DisplayRole || role == Qt::EditRole)
    {
        vector<Event> events = this->repo.getelementsUser();
        Event c = events[row];
        switch(column)
        {
            case 0:
                return QString::fromStdString(c.getTitle());

            case 1:
                return QString::fromStdString((c.getDescription()));

            case 2:
                return QString::fromStdString((c.getLink()));

            case 3:
                return QString::number(c.getNumberOfPeople());

            case 4:
                return QString::number(c.getDatetime().time);

            case 5:
                return QString::number(c.getDatetime().date_day);

            case 6:
                return QString::number(c.getDatetime().date_month);
            default:
                break;

        }
    }

    if(role == Qt::FontRole) {

        QFont font("Times", 15, 10, true);
        font.setItalic(false);
        return font;
    }

    return QVariant{};

};

QVariant TableMode::headerData(int section, Qt::Orientation orientation, int role) const {

    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch(section){
                case 0:
                    return QString{"Title"};

                case 1:
                    return QString{"Description"};

                case 2:
                    return QString{"Link"};

                case 3:
                    return QString{"Number people"};

                case 4:
                    return QString{"Time"};

                case 5:
                    return QString{"Day"};

                case 6:
                    return QString{"Month"};

                default:
                    break;
            }
        }
    }

    if(role == Qt::FontRole)
    {
        QFont font("Times", 15, 10, true);
        font.setBold(true);
        font.setItalic(false);
        return font;
    }

    return QVariant{};
}

Qt::ItemFlags TableMode::flags(const QModelIndex &index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void TableMode::updateInternalData() {

    endResetModel();

}