#ifndef DIVISION_H
#define DIVISION_H
#include "Data/sample.h"

class TwoDimSample;
class Division
{
public:
    double x;
    int n;
    double p;

    Division(const double &x, const int &n, const double &p);

    static QList<Division*> buildDivision(const QList<double> &sample, const double &stepSize, const int &classSize);

    static QList<double> DivisionSample(const double &sampleFirst, const double &stepSize, const int &classSize);

    static QList<int> Frequency(const QList<double> &sample, const QList<double> &sampleDivision);

    static QList<double> RelativeFrequency(const QList<int> &frequency);
};

#endif // DIVISION_H
