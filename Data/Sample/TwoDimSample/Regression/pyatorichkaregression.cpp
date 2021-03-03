#include "pyatorichkaregression.h"

PyatorichkaRegression::PyatorichkaRegression()
{
}

QList<XY> PyatorichkaRegression::buildFirst(const TwoDimSample &sample, const bool &should_use)
{
    phi_average = PhiAverage(sample.first.sample, sample.second.sample, should_use);
    psi_average = PsiAverage(sample.first.sample, sample.second.sample, should_use);
    phi_two_average = PhiTwoAverage(sample.first.sample, sample.second.sample, should_use);
    psi_phi_average = PsiPhiAverage(sample.first.sample, sample.second.sample, should_use);

    b_value = B();
    a_value = A();

    QList<XY> value = QList<XY>();

    error_value = 0;
    for(int i = 0; i < sample.sample.size(); i++){
        value << *new XY(sample.sample.at(i).x,  sample.sample.at(i).x / (a_value + b_value * Phi(sample.sample.at(i).x)));
        error_value += pow(sample.sample.at(i).y - value.at(i).y, 2.0);
    }
    error_value *= (1.0 / (sample.sample.size() - 3.0));
    error_value = sqrt(error_value);
    return value;
}

double PyatorichkaRegression::A()
{
    return psi_average - b_value * phi_average;
}

double PyatorichkaRegression::B()
{
    return (psi_phi_average - psi_average * phi_average) / (phi_two_average - pow(phi_average, 2.0));
}

double PyatorichkaRegression::Phi(const double &x)
{
    return x;
}

double PyatorichkaRegression::Psi(const double &x, const double &y)
{
    return x/y;
}

double PyatorichkaRegression::wCoefficient(const double &x, const double &y, const bool &should_use)
{
    if(should_use)
        return pow(y, 4.0) / pow(x, 2.0);
    else
        return 1;
}

double PyatorichkaRegression::PhiAverage(const QList<double> &x, const QList<double> &y, const bool &should_use)
{
    double upper_value = 0;
    double lower_value = 0;
    for(int i = 0; i < x.size(); i++){
        upper_value += Phi(x[i]) * wCoefficient(x[i], y[i], should_use);
        lower_value += wCoefficient(x[i], y[i]);
    }
    return upper_value / lower_value;
}

double PyatorichkaRegression::PsiAverage(const QList<double> &x, const QList<double> &y, const bool &should_use)
{
    double upper_value = 0;
    double lower_value = 0;
    for(int i = 0; i < x.size(); i++){
        upper_value += Psi(x[i], y[i]) * wCoefficient(x[i], y[i], should_use);
        lower_value += wCoefficient(x[i], y[i]);
    }
    return upper_value / lower_value;
}

double PyatorichkaRegression::PsiPhiAverage(const QList<double> &x, const QList<double> &y, const bool &should_use)
{
    double upper_value = 0;
    double lower_value = 0;
    for(int i = 0; i < x.size(); i++){
        upper_value += Phi(x[i]) * Psi(x[i], y[i]) * wCoefficient(x[i], y[i], should_use);
        lower_value += wCoefficient(x[i], y[i]);
    }
    return upper_value / lower_value;
}

double PyatorichkaRegression::PhiTwoAverage(const QList<double> &x, const QList<double> &y, const bool &should_use)
{
    double upper_value = 0;
    double lower_value = 0;
    for(int i = 0; i < x.size(); i++){
        upper_value += pow(Phi(x[i]), 2.0) * wCoefficient(x[i], y[i], should_use);
        lower_value += wCoefficient(x[i], y[i]);
    }
    return upper_value / lower_value;
}

QList<XY> PyatorichkaRegression::MaxConfidenceInterval(const QList<XY> &value, const TwoDimSample &sample)
{
    QList<XY> *returnValue = new QList<XY>();

    double t_value = Quantile::TQuantile(Quantile::AValue(value.size()), value.size());
    double b_error = this->error_value / (sample.first.GetParameter("Dispersion") * sqrt(sample.sample.size() - 1.0));
    for(XY xy : value){
        double y = (((xy.y + t_value * SXY(xy.x, b_error, sample))));
        returnValue->append(XY(xy.x, y));
    }
    return *returnValue;
}

QList<XY> PyatorichkaRegression::MinConfidenceInterval(const QList<XY> &value, const TwoDimSample &sample)
{
    QList<XY> *returnValue = new QList<XY>();

    double t_value = Quantile::TQuantile(Quantile::AValue(value.size()), value.size());
    double b_error = this->error_value / (sample.first.GetParameter("Dispersion") * sqrt(sample.sample.size() - 1.0));
    for(XY xy : value){
        double y = (((xy.y - t_value * SXY(xy.x, b_error, sample))));
        returnValue->append(XY(xy.x, y));
    }
    return *returnValue;
}

double PyatorichkaRegression::SXY(const double &x, const double &b_error, const TwoDimSample &sample)
{
    return sqrt(pow(error_value, 2.0) * (1.0 / sample.sample.size()) + pow(b_error, 2.0) * pow(x - sample.first.GetParameter("Average"), 2.0));
}

QList<TwoDimParameter *> PyatorichkaRegression::buildPyatorichkaParameter(const TwoDimSample &sample)
{
    double a_error = this->error_value * sqrt((1.0 / sample.sample.size()) +
                            (pow(sample.first.GetParameter("Average"), 2.0) / (pow(sample.first.GetParameter("Dispersion"), 2.0) * (sample.sample.size() - 1.0))));
    double b_error = this->error_value / (sample.first.GetParameter("Dispersion") * sqrt(sample.sample.size() - 1.0));
    double t_quantile = Quantile::TQuantile(Quantile::AValue(sample.sample.size()), sample.sample.size() - 1);
    TwoDimParameter *parameter_a = new TwoDimParameter("pyatorichka_a", a_value, 0, false, a_value - t_quantile * a_error, a_value + t_quantile * a_error, t_quantile);
    TwoDimParameter *parameter_b = new TwoDimParameter("parabolic_b", b_value, 0, false, b_value - t_quantile * b_error, b_value + t_quantile * b_error, t_quantile);
    TwoDimParameter *parameter_error = new TwoDimParameter("pyatorichka_error", error_value);
    QList<TwoDimParameter*> parameters = QList<TwoDimParameter*>();
    parameter_error->ua_name = "5-варіант залишкова дисперсія(5)";
    parameter_a->ua_name = "5-варіант параметр a(5)";
    parameter_b->ua_name = "5-варіант параметр b(5)";
    parameters.append(parameter_error);
    parameters.append(parameter_a);
    parameters.append(parameter_b);

    return parameters;
}
