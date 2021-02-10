#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include "Data/twodimsample.h"

class TwoDimSample;
class LinearRegression
{
public:
    double mnk_a;
    double mnk_b;
    double taylor_a;
    double taylor_b;
    LinearRegression();

    void MNKParameter(const TwoDimSample &sample);
    void TaylorParameter(const TwoDimSample &sample);

    double MNK(const double &value);
    double Taylor(const double &value);

    QList<XY> buildMNK(const TwoDimSample &sample);
    QList<XY> buildTaylor(const TwoDimSample &sample);

    QList<XY> buildRegression(const TwoDimSample &sample, const int &choise = 0);
};

#endif // LINEARREGRESSION_H
