#include "linearregression.h"

LinearRegression::LinearRegression()
{

}

void LinearRegression::MNKParameter(const TwoDimSample &sample)
{
    mnk_b = sample.GetValueParameter("CorrelationCoefficient") * sample.second.GetParameter("Dispersion") / sample.first.GetParameter("Dispersion");
    mnk_a = sample.second.GetParameter("Average") - mnk_b * sample.first.GetParameter("Average");
}

void LinearRegression::TaylorParameter(const TwoDimSample &sample)
{
    QList<double> value_for_b;
    QList<double> value_for_a;
    for(int i = 0; i < sample.sample.size(); i++){
        for(int j = i + 1; j < sample.sample.size(); j++){
            value_for_b << (sample.sample.at(j).y - sample.sample.at(i).y) / (sample.sample.at(j).x - sample.sample.at(i).x);
        }
    }
    std::sort(value_for_b.begin(), value_for_b.end());
    taylor_b = Parameter::MED(value_for_b);
    for(int i = 0; i < sample.sample.size(); i++)
        value_for_a << sample.sample.at(i).y - taylor_b * sample.sample.at(i).x;
    std::sort(value_for_a.begin(), value_for_a.end());
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

QList<TwoDimParameter*> LinearRegression::LinearParameter(const QString &name, const double &a, const double &b, const double &error_value, const TwoDimSample &sample)
{
    double a_error_value = error_value * sqrt(1.0 / sample.sample.size()
                                              + (pow(sample.first.GetParameter("Average"), 2.0) /
                                                    (pow(sample.first.GetParameter("Dispersion"), 2.0) * (sample.sample.size() - 1))));
    double b_error_value = error_value / (sample.first.GetParameter("Dispersion") * sqrt(sample.sample.size() - 1));

    double t_a = a / a_error_value;
    double t_b = b / b_error_value;


    TwoDimParameter *error_parameter = new TwoDimParameter("error_value_" + name, error_value);
    double t_quantile = Quantile::TQuantile(0.1, sample.sample.size() - 2);
    TwoDimParameter *parameter_a = new TwoDimParameter("a_" + name, a, t_a, abs(t_a) > t_quantile, a - t_quantile * a_error_value, a + t_quantile * a_error_value, t_quantile);
    TwoDimParameter *parameter_b = new TwoDimParameter("b_" + name, b, t_b, abs(t_b) > t_quantile, b - t_quantile * b_error_value, b + t_quantile * b_error_value, t_quantile);
    TwoDimParameter *a_error_parameter = new TwoDimParameter("a_error_value_" + name, a_error_value);
    TwoDimParameter *b_error_parameter = new TwoDimParameter("b_error_value_" + name, b_error_value);

    QList<TwoDimParameter*> parameters = QList<TwoDimParameter*>();
    parameters.append(error_parameter);
    parameters.append(parameter_a);
    parameters.append(parameter_b);
    parameters.append(a_error_parameter);
    parameters.append(b_error_parameter);
    return parameters;
}

QList<TwoDimParameter *> LinearRegression::buildLinearParameter(const TwoDimSample &sample, const int &choise)
{
    switch(choise){
        case 0:
        return LinearParameter("mnk", mnk_a, mnk_b, mnk_error, sample);
    case 1:
        return LinearParameter("taylor", taylor_a, taylor_b, taylor_error, sample);
    default:
        return QList<TwoDimParameter*>();
    }
}

QList<XY> LinearRegression::buildMNK(const TwoDimSample &sample)
{
    QList<XY> value = QList<XY>();
    MNKParameter(sample);
    double error_value = 0;
    for(int i = 0; i < sample.sample.size(); i++){
        value << *new XY(sample.sample.at(i).x, MNK(sample.sample.at(i).x));
        error_value += pow(sample.sample.at(i).y - value.at(i).y, 2.0);
    }
    error_value *= (1.0 / (sample.sample.size() - 2.0));
    this->mnk_error = error_value;
    return value;
}

QList<XY> LinearRegression::buildTaylor(const TwoDimSample &sample)
{
    QList<XY> value = QList<XY>();
    TaylorParameter(sample);
    double error_value = 0;
    for(int i = 0; i < sample.sample.size(); i++){
        value << *new XY(sample.sample.at(i).x, Taylor(sample.sample.at(i).x));
        error_value += pow(sample.sample.at(i).y - value.at(i).y, 2.0);
    }
    error_value *= (1.0 / (sample.sample.size() - 2.0));
    this->taylor_error = error_value;
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
