#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include "Data/Sample/TwoDimSample/twodimsample.h"

class TwoDimSample;
class Distribution
{
public:
    double x;
    double y;
    double p;
    Distribution(const double &x, const double &y, const double &p);

    static QList<Distribution*> TwoDimDistributionIndependentBuild(OneDimSample &first, OneDimSample &second);

    static double TwoDimDistributionIndependentValue(const double &_firstDispersion, const double &_secondDispersion, const double &_x, const double &_y,
                                          const double &_xAverage, const double &_yAverage);

    static QList<Distribution*> TwoDimDistributionBuild(OneDimSample &first, OneDimSample &second, double correlationCoefficient);

    static double TwoDimDistributionValue(const double &_firstDispersion, const double &_secondDispersion, const double &_x, const double &_y,
                                          const double &_xAverage, const double &_yAverage, const double &correlationCoefficient);
};

#endif // DISTRIBUTION_H
