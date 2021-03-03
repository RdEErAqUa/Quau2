#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include "Data/Sample/TwoDimSample/twodimsample.h"

class TwoDimSample;
class TwoDimParameter;
class LinearRegression
{
public:
    double mnk_a;
    double mnk_b;
    double taylor_a;
    double taylor_b;
    double mnk_error;
    double taylor_error;
    LinearRegression();

    void MNKParameter(const TwoDimSample &sample);
    void TaylorParameter(const TwoDimSample &sample);

    double MNK(const double &value);
    double Taylor(const double &value);

    QList<TwoDimParameter*> LinearParameter(const QString &name, const double &a, const double &b, const double &error_value, const TwoDimSample &sample);

    QList<TwoDimParameter*> buildLinearParameter(const TwoDimSample &sample, const int &choise);

    QList<XY> buildMNK(const TwoDimSample &sample);
    QList<XY> buildTaylor(const TwoDimSample &sample);

    QList<XY> buildRegression(const TwoDimSample &sample, const int &choise = 0);
};

#endif // LINEARREGRESSION_H
