#include "mainwindow.h"

#include <QApplication>
#include "Data/Group/group.h"

struct foo{};
struct doo{};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
