#ifndef PARAMETER_H
#define PARAMETER_H

#include <QString>
#include "QListUseful.h"
#include <cmath>
#include "Quantile.h"

class Parameter
{
public:
    QString name;
    double value;
    double dispersion;
    double max_value;
    double min_value;

    Parameter(const QString &name,const double &value, const double rootMeanSquare = 0,const double maxValue = 0,const double minValue = 0);

    static double InitialStaticMoment(const QList<double> &value,const int &power);
    static double CentralMoment(const QList<double> &value,const int &power);
    static double Average(const QList<double> &value);
    static double Dispersion(const QList<double> &value);
    static double DispersionUnshifted(const QList<double> &value);
    static double Skewness(const QList<double> &value);
    static double SkewnessUnShifted(const QList<double> &value);
    static double Kurtosis(const QList<double> &value);
    static double KurtosisUnshifted(const QList<double> &value);
    static double CounterKurtosis(const QList<double> &value);
    static double MAD(const QList<double> &value);
    static double MED(const QList<double> &value);
    static double PearsonVariation(const QList<double> &value);

    static double DispersionAverage(const QList<double> &value);
    static Parameter *buildAverage(const QList<double> &value, const double &quantile);
    static double DispersionDispersion(const QList<double> &value);
    static Parameter *buildDispersion(const QList<double> &value, const double &quantile);
    static Parameter *buildDispersionUnshifted(const QList<double> &value);
    static double DispersionSkewness(const QList<double> &value);
    static Parameter *buildSkewness(const QList<double> &value, const double &quantile);
    static Parameter *buildSkewnessUnShifted(const QList<double> &value);
    static Parameter *buildKurtosis(const QList<double> &value);
    static Parameter *buildKurtosisUnshifted(const QList<double> &value);
    static Parameter *buildCounterKurtosis(const QList<double> &value);
    static Parameter *buildMAD(const QList<double> &value);
    static Parameter *buildMED(const QList<double> &value);
    static Parameter *buildPearsonVariation(const QList<double> &value);

    static QList<Parameter*> buildParameters(const QList<double> &value ,const double &quantile);


};

#endif // PARAMETER_H
