#include "ui.h"
#include "tests.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tests t;
    t.testAll();

    MainWindow w;
    w.show();
    return a.exec();
}
