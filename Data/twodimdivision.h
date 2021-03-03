#ifndef TWODIMDIVISION_H
#define TWODIMDIVISION_H

#include "Data/Sample/TwoDimSample/twodimsample.h"

class TwoDimSample;
class TwoDimDivision
{
public:
    TwoDimDivision(const double &X, const double &Y, const double &N, const double &P);
    double x;
    double y;
    double n;
    double p;

    static QList<TwoDimDivision*> buildDivision(const QList<XY> &sample, const double &sampleFirstX, const double &sampleFirstY,
                                                const double &stepSizeX, const double &stepSizeY,
                                                const int &classSizeX,const int &classSizeY);

    static QList<XY> DivisionSample(const double &sampleFirstX, const double &sampleFirstY,
                                    const double &stepSizeX, const double &stepSizeY,
                                    const int &classSizeX,const int &classSizeY);

    static QList<int> Frequency(const QList<XY> &sample, const double &classSizeX, const double &classSizeY,const QList<XY> &sampleDivision);

    static QList<double> RelativeFrequency(const QList<int> &frequency);

};

#endif // TWODIMDIVISION_H
