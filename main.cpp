#include "ui.h"
#include "tests.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    Tests t;
    t.testAll();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
