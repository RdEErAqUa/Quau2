#ifndef PARAMETER_H
#define PARAMETER_H

#include <QString>
#include "QListUseful.h"
#include <cmath>

struct Parameter
{
    QString name;
    double value;
    double dispersion;
    double rootMeanSquare;
    double maxValue;
    double minValue;

    Parameter(const QString &name,const double &value,const double dispersion = 0,const double rootMeanSquare = 0,const double maxValue = 0,const double minValue = 0);

    static double InitialStaticMoment(const QList<double> &value,const int &power){
        double returnValue = 0;
        for(double v : value){
            returnValue += pow(v, power);
        }
        return returnValue/value.size();
    }
    static double CentralMoment(const QList<double> &value,const int &power)
    {
        double initialStaticMoment = Parameter::InitialStaticMoment(value, 1);

        double returnValue = 0;
        for(double v : value){
            returnValue += pow(v - initialStaticMoment, power);
        }
        return returnValue/value.size();
    }
    static double Average(const QList<double> &value){
        double returnValue = 0;
        for(double v : value){
            returnValue += v;
        }
        return returnValue/value.size();
    }
    static double Dispersion(const QList<double> &value)
    {
        return sqrt(Parameter::CentralMoment(value, 2));
    }
    static double DispersionUnshifted(const QList<double> &value){
        double initialStaticMoment = Parameter::InitialStaticMoment(value, 1);
        double returnValue = 0;
        for(double v : value){
            returnValue += pow(v - initialStaticMoment, 2);
        }
        return sqrt(returnValue/(value.size() - 1.0));
    }
    static double Skewness(const QList<double> &value)
    {
        return Parameter::CentralMoment(value, 2);
    }
    static double SkewnessUnShifted(const QList<double> &value)
    {
        int size = value.size();
        return sqrt(size * (size - 1.0)) / (size - 2.0) * Parameter::Skewness(value);
    }
    static double Kurtosis(const QList<double> &value)
    {
        return Parameter::CentralMoment(value, 4) / pow(Parameter::CentralMoment(value, 2), 2.0);
    }
    static double KurtosisUnshifted(const QList<double> &value)
    {
        int size = value.size();
        return ((pow(size, 2.0) - 1.0) / ((size - 2.0) * (size - 3.0)) *
                            ((Parameter::Kurtosis(value) - 3.0) + 6.0 / (size + 1.0)));
    }
    static double CounterKurtosis(const QList<double> &value)
    {
        return 1.0 / sqrt(abs(Parameter::KurtosisUnshifted(value)));
    }
    static double MAD(const QList<double> &value)
    {
        return (1.483 * Parameter::MED(value));
    }
    static double MED(const QList<double> &value)
    {
        int size = value.size();
        if (size % 2 == 0)
        {
            int k = size;
            k /= 2;
            double MED = value[k] + value[k + 1];
            MED /= 2;
            return MED;
        }
        else
        {
            int k = size - 1;
            k /= 2;
            double MED = value[k + 1];
            return MED;
        }
    }
    static double PearsonVariation(const QList<double> &value)
    {
        return Parameter::Dispersion(value) / Parameter::Average(value);
    }

};

#endif // PARAMETER_H
