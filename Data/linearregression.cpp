#include "linearregression.h"

LinearRegression::LinearRegression()
{

}

void LinearRegression::MNKParameter(const TwoDimSample &sample)
{
    mnk_b = sample.GetParameter("CorrelationCoefficient") * sample.second.GetParameter("Dispersion") / sample.first.GetParameter("Dispersion");
    mnk_a = sample.second.GetParameter("Average") - mnk_b * sample.first.GetParameter("Average");
}

void LinearRegression::TaylorParameter(const TwoDimSample &sample)
{
    QList<double> value_for_b;
    QList<double> value_for_a;
    for(int i = 0; i < sample.sample.size(); i++){
        for(int j = 0; j < sample.sample.size(); j++){
            value_for_b << (sample.second.samplesorted.at(j) - sample.second.samplesorted.at(i)) / (sample.first.samplesorted.at(j) - sample.first.samplesorted.at(i));
        }
    }
    taylor_b = Parameter::MED(value_for_b);
    for(int i = 0; i < sample.sample.size(); i++)
        value_for_a << sample.second.samplesorted.at(i) - taylor_b * sample.first.samplesorted.at(i);
    taylor_a = Parameter::MED(value_for_a);
}

double LinearRegression::MNK(const double &value)
{
    return mnk_a + mnk_b * value;
}

double LinearRegression::Taylor(const double &value)
{
    return taylor_a + taylor_b * value;
}

QList<XY> LinearRegression::buildMNK(const TwoDimSample &sample)
{
    QList<XY> value = QList<XY>();
    MNKParameter(sample);
    for(double x : sample.first.sample){
        value << *new XY(x, MNK(x));
    }
    return value;
}

QList<XY> LinearRegression::buildTaylor(const TwoDimSample &sample)
{
    QList<XY> value = QList<XY>();
    TaylorParameter(sample);
    for(double x : sample.first.sample){
        value << *new XY(x, Taylor(x));
    }
    return value;
}

QList<XY> LinearRegression::buildRegression(const TwoDimSample &sample, const int &choise)
{
    switch(choise){
    case 0:
        return buildMNK(sample);
    case 1:
        return buildTaylor(sample);
    default:
        return QList<XY>();
    }
}
