#ifndef VARIATION_H
#define VARIATION_H
#include <QList>
#include "Data/sample.h"
#include "QListUseful.h"

class TwoDimSample;
class Variation
{
public:
    double x;
    int n;
    double p;

    Variation(const double &x, const int &n, const double &p);

    static QList<Variation*> buildVariation(QList<double> &sample);

    static QList<int> Frequency(const QList<double> &sample, const QList<double> &sampleUnique);

    static QList<double> RelativeFrequency(const QList<int> &frequency);
};

#endif // VARIATION_H
