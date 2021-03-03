#include "Data/parameter.h"

Parameter::Parameter(const QString name, const double value, const int data_size,const double dispersion,const double maxValue,const double minValue)
    : name(name), value(value), data_size(data_size),dispersion(dispersion), max_value(maxValue), min_value(minValue){}

double Parameter::InitialStaticMoment(const QList<double> &value, const int &power){
    double returnValue = 0;
    for(double v : value){
        returnValue += pow(v, power);
    }
    return returnValue/value.size();
}

double Parameter::CentralMoment(const QList<double> &value, const int &power)
{
    double initialStaticMoment = Parameter::InitialStaticMoment(value, 1);

    double returnValue = 0;
    for(double v : value){
        returnValue += pow(v - initialStaticMoment, power);
    }
    return returnValue/value.size();
}

double Parameter::Average(const QList<double> &value){
    double returnValue = 0;
    for(double v : value){
        returnValue += v;
    }
    return returnValue/value.size();
}

double Parameter::Dispersion(const QList<double> &value)
{
    return sqrt(Parameter::CentralMoment(value, 2));
}

double Parameter::DispersionUnshifted(const QList<double> &value){
    double initialStaticMoment = Parameter::InitialStaticMoment(value, 1);
    double returnValue = 0;
    for(double v : value){
        returnValue += pow(v - initialStaticMoment, 2);
    }
    return sqrt(returnValue/(value.size() - 1.0));
}

double Parameter::Skewness(const QList<double> &value)
{
    return Parameter::CentralMoment(value, 2);
}

double Parameter::SkewnessUnShifted(const QList<double> &value)
{
    int size = value.size();
    return sqrt(size * (size - 1.0)) / (size - 2.0) * Parameter::Skewness(value);
}

double Parameter::Kurtosis(const QList<double> &value)
{
    return Parameter::CentralMoment(value, 4) / pow(Parameter::CentralMoment(value, 2), 2.0);
}

double Parameter::KurtosisUnshifted(const QList<double> &value)
{
    int size = value.size();
    return ((pow(size, 2.0) - 1.0) / ((size - 2.0) * (size - 3.0)) *
            ((Parameter::Kurtosis(value) - 3.0) + 6.0 / (size + 1.0)));
}

double Parameter::CounterKurtosis(const QList<double> &value)
{
    return 1.0 / sqrt(abs(Parameter::KurtosisUnshifted(value)));
}

double Parameter::MAD(const QList<double> &value)
{
    return (1.483 * Parameter::MED(value));
}

double Parameter::MED(const QList<double> &value)
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

double Parameter::PearsonVariation(const QList<double> &value)
{
    return Parameter::Dispersion(value) / Parameter::Average(value);
}

double Parameter::DispersionAverage(const QList<double> &value){
    return DispersionUnshifted(value) / sqrt(value.size());
}

Parameter *Parameter::buildAverage(const QList<double> &value, const double &quantile){
    double dispersionAverage = Parameter::DispersionAverage(value);
    double average = Average(value);
    return new Parameter("Average",average, 4, dispersionAverage, average + quantile * dispersionAverage, average - quantile * dispersionAverage);
}

double Parameter::DispersionDispersion(const QList<double> &value)
{
    return DispersionUnshifted(value) / sqrt(2.0 * value.size());
}

Parameter *Parameter::buildDispersion(const QList<double> &value, const double &quantile){
    double dispersionDispersion = Parameter::DispersionDispersion(value);
    double dispersion = Dispersion(value);
    return new Parameter("Dispersion", dispersion,4, dispersionDispersion, dispersion + quantile * dispersionDispersion, dispersion - quantile * dispersionDispersion);
}

Parameter *Parameter::buildDispersionUnshifted(const QList<double> &value){
    return new Parameter("DispersionUnshifted", DispersionUnshifted(value), 1);
}

double Parameter::DispersionSkewness(const QList<double> &value)
{
    return sqrt(6.0 / value.size()) * (1.0 - 12.0 / (2.0 * value.size() + 7));
}

Parameter *Parameter::buildSkewness(const QList<double> &value, const double &quantile){
    double dispersionSkewness = Parameter::DispersionSkewness(value);
    double skewness = Skewness(value);
    return new Parameter("Skewness", skewness, 4,dispersionSkewness, skewness + quantile * dispersionSkewness, skewness - quantile * dispersionSkewness);

}

Parameter *Parameter::buildSkewnessUnShifted(const QList<double> &value){
    return new Parameter("SkewnessUnshifted", SkewnessUnShifted(value), 1);
}

Parameter *Parameter::buildKurtosis(const QList<double> &value){
    return new Parameter("Kurtosis", Kurtosis(value), 1);
}

Parameter *Parameter::buildKurtosisUnshifted(const QList<double> &value){
    return new Parameter("KurtosisUnshifted", KurtosisUnshifted(value), 1);
}

Parameter *Parameter::buildCounterKurtosis(const QList<double> &value){
    return new Parameter("CounterKurtosis", CounterKurtosis(value), 1);
}

Parameter *Parameter::buildMAD(const QList<double> &value){
    return new Parameter("MAD", MAD(value), 1);
}

Parameter *Parameter::buildMED(const QList<double> &value){
    return new Parameter("MED", MED(value), 1);
}

Parameter *Parameter::buildPearsonVariation(const QList<double> &value){
    return new Parameter("PearsonVariation", PearsonVariation(value), 1);
}

QList<Parameter *> Parameter::buildParameters(const QList<double> &value, const double &quantile){
    QList<Parameter*> *parameters = new QList<Parameter*>();
    parameters->append(buildAverage(value, quantile));
    parameters->append(buildDispersion(value, quantile));
    parameters->append(buildDispersionUnshifted(value));
    parameters->append(buildSkewness(value, quantile));
    parameters->append(buildSkewnessUnShifted(value));
    parameters->append(buildKurtosis(value));
    parameters->append(buildKurtosisUnshifted(value));
    parameters->append(buildCounterKurtosis(value));
    parameters->append(buildMAD(value));
    parameters->append(buildMED(value));
    parameters->append(buildPearsonVariation(value));
    return *parameters;
};

