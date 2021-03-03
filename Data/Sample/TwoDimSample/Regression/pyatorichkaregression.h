#ifndef PYATORICHKAREGRESSION_H
#define PYATORICHKAREGRESSION_H
#include "Data/Sample/TwoDimSample/twodimsample.h"

class PyatorichkaRegression
{
public:
    PyatorichkaRegression();
    double a_value;
    double b_value;
    double psi_average;
    double phi_average;
    double phi_two_average;
    double psi_phi_average;

    double error_value;
    QList<XY> buildFirst(const TwoDimSample &sample, const bool &should_use = true);

    double A();
    double B();
    double Phi(const double &x);
    double Psi(const double &x, const double &y);
    double wCoefficient(const double &x, const double &y, const bool &should_use = true);

    double PhiAverage(const QList<double> &x, const QList<double> &y, const bool &should_use = true);
    double PsiAverage(const QList<double> &x, const QList<double> &y, const bool &should_use = true);
    double PsiPhiAverage(const QList<double> &x, const QList<double> &y, const bool &should_use = true);
    double PhiTwoAverage(const QList<double> &x, const QList<double> &y, const bool &should_use = true);

    QList<XY> MaxConfidenceInterval(const QList<XY> &value, const TwoDimSample &sample);
    QList<XY> MinConfidenceInterval(const QList<XY> &value, const TwoDimSample &sample);

    double SXY(const double &x, const double &b_error, const TwoDimSample &sample);

    QList<TwoDimParameter*> buildPyatorichkaParameter(const TwoDimSample &sample);
};

#endif // PYATORICHKAREGRESSION_H
