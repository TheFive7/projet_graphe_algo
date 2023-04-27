#include "mainwindow.h"
#include <QApplication>

#include "test.h"
#include "algorithms.h"
#include "widgetgraph.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w{};
    w.show();


    int exe = a.exec();

    test(); // Pour lancer les tests

    return exe;
}

