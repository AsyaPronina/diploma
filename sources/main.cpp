#include "presenters/mainpresenter.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    MainPresenter p(&w);

    return a.exec();
}
