#ifndef REGRESSION_H
#define REGRESSION_H
#include "Data/Sample/TwoDimSample/twodimsample.h"

class TwoDimParameter;
class Regression
{
public:
    int regression_type;
    QList<XY> regression_value;
    QList<TwoDimParameter*> parameter;

    QList<XY> max_tolerance_interval;
    QList<XY> min_tolerance_interval;

    QList<XY> max_confidence_interval;
    QList<XY> min_confidence_interval;

    QList<XY> max_new_confidence_interval;
    QList<XY> min_new_confidence_interval;

    Regression(const int &regression_type, const QList<XY> &regression_value, QList<TwoDimParameter*> parameter);
};

#endif // REGRESSION_H
