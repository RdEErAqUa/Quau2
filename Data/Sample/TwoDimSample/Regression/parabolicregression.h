#ifndef PARABOLICREGRESSION_H
#define PARABOLICREGRESSION_H
#include "Data/Sample/TwoDimSample/twodimsample.h"

class TwoDimSample;
class ParabolicRegression
{
public:
    ParabolicRegression();

    double a_first;
    double b_first;
    double c_first;
    double error_first;

    double a_second;
    double b_second;
    double c_second;
    double error_second;

    double x_average_second_degree;
    double x_average_third_degree;

    double phi_two_average_value;

    void FirstParameter(const TwoDimSample &sample);
    void SecondParameter(const TwoDimSample &sample);

    double First(const double &value);
    double Second(const double &value, const TwoDimSample &sample);
    double PhiOne(const double &x, const TwoDimSample &sample);
    double PhiTwo(const double &x, const TwoDimSample &sample);

    QList<XY> MaxConfidenceInterval(const QList<XY> &value, const double &error_value, const TwoDimSample &sample);
    QList<XY> MinConfidenceInterval(const QList<XY> &value, const double &error_value, const TwoDimSample &sample);

    QList<XY> MaxNewConfidenceInterval(const QList<XY> &value, const double &error_value, const TwoDimSample &sample);
    QList<XY> MinNewConfidenceInterval(const QList<XY> &value, const double &error_value, const TwoDimSample &sample);


    QList<XY> MaxToleranceInterval(const QList<XY> &value, const double &error_value, const TwoDimSample &sample);
    QList<XY> MinToleranceInterval(const QList<XY> &value, const double &error_value, const TwoDimSample &sample);

    double SYX(const double &x, const double &error_value, const double &size, const double &dispersion, const TwoDimSample &sample);

    QList<TwoDimParameter*> ParabolicParameter(const QString &name, const double &a, const double &b, const double &c, const double &error_value, const TwoDimSample &sample);

    QList<TwoDimParameter*> buildParabolicParameter(const TwoDimSample &sample, const int &choise);

    QList<XY> buildFirst(const TwoDimSample &sample);
    QList<XY> buildSecond(const TwoDimSample &sample);

    QList<XY> buildRegression(const TwoDimSample &sample, const int &choise = 0);
};

#endif // PARABOLICREGRESSION_H
