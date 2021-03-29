#include "mainwindow.h"

#include <QApplication>
#include "Data/Group/group.h"
#include "Data/Sample/HigherDimSample/higherdimsample.h"

struct foo{};
struct doo{};



int main(int argc, char *argv[])
{

    QList<QList<double>> JUST_FOR_Lulz = {{1, 2, 3, 4, 5},
                                          {5, 13, 2, 5, 1},
                                          {16, 13, 2, 8, 7}};
    HigherDimSample samples(JUST_FOR_Lulz);
    samples.PrimaryAnalysis();
    TwoDimParameter *s = samples.SetPartial({{1, 0.5, 0.2, 0.7}, {0.5, 1, 0.6, 0.9}, {0.2, 0.6, 1, 0.3}, {0.7, 0.9, 0.3, 1}}, 0, 2, {1, 3});
    TwoDimParameter *s_v = samples.SetMultiple({{1, 0.5, 0.2, 0.7}, {0.5, 1, 0.6, 0.9}, {0.2, 0.6, 1, 0.3}, {0.7, 0.9, 0.3, 1}}, 0, 0);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
