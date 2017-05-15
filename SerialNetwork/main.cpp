#include "mainwindow.h"
#include <QApplication>
#include "dialog.h"
#include "portwindow.h"

   MainWindow *w;
   Dialog *d;


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    w = new MainWindow;

    d = new Dialog;

    w -> show();

    return a.exec();
}
