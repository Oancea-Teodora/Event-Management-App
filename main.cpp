#include "GUI/GUI.h"
//#include "GUI/GUI.h"
#include <QtWidgets/QApplication>
#include <QLabel>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
   // UI ui = UI();
   // ui.start1();
    GUI gui;
    gui.show();
    return app.exec();
}