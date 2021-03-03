#include "parabolicregression.h"

ParabolicRegression::ParabolicRegression() : a_first(0), b_first(0), c_first(0), a_second(0), b_second(0), c_second(0)
{

}

void ParabolicRegression::FirstParameter(const TwoDimSample &sample)
{
    double x_average = sample.first.GetParameter("Average");
    double y_average = sample.second.GetParameter("Average");
    double x_average_fourth_degree = Parameter::InitialStaticMoment(sample.first.samplesorted, 4);
    double x_dispersion = sample.first.GetParameter("Dispersion");
    double y_dispersion = sample.second.GetParameter("Dispersion");
    double correlation_coefficient = sample.GetValueParameter("CorrelationCoefficient");
    double x_dispersion_square = pow(x_dispersion, 2.0);

    double correaltion_two_dispersion = correlation_coefficient  *
            x_dispersion * y_dispersion;

    double xy_needed_value = 0;
    for(int i = 0; i < sample.sample.size(); i++){
        xy_needed_value += (pow(sample.sample.at(i).x, 2.0) - x_average_second_degree) * (sample.sample.at(i).y - y_average);
    }
    xy_needed_value *= (1.0 / sample.sample.size());

    double first_important = (x_average_fourth_degree - pow(x_average_second_degree, 2.0));
    double second_important = (x_average_third_degree - x_average_second_degree * x_average);
    double second_important_square = pow(x_average_third_degree - x_average_second_degree * x_average, 2.0);


    double b_value = (pow(x_dispersion, 2.0) * first_important - second_important_square);
    b_first = (first_important * correaltion_two_dispersion-
            second_important * xy_needed_value)/
            b_value;

    c_first = (x_dispersion_square * xy_needed_value - second_important * correaltion_two_dispersion) /
            (x_dispersion_square * first_important - second_important_square);

    a_first = y_average - b_first * x_average - c_first * x_average_second_degree;

}

void ParabolicRegression::SecondParameter(const TwoDimSample &sample)
{
    phi_two_average_value = 0;
    for(double value : sample.first.sample)
        phi_two_average_value += pow(PhiTwo(value, sample), 2.0);

    phi_two_average_value *= (1.0 / sample.sample.size());

    a_second = sample.second.GetParameter("Average");

    double b_value = 0;
    for(int i = 0; i < sample.sample.size(); i++){
        b_value += (sample.sample.at(i).x - sample.first.GetParameter("Average")) * sample.sample.at(i).y;
    }
    b_value *= (1.0 / sample.sample.size());
    b_second = b_value / (pow(sample.first.GetParameter("Dispersion"), 2.0));
    double c_value_first = 0;
    double c_value_second = 0;
    for(int i = 0; i < sample.sample.size(); i++){
        c_value_first += PhiTwo(sample.sample.at(i).x, sample) * sample.sample.at(i).y;
        c_value_second += pow(PhiTwo(sample.sample.at(i).x, sample), 2.0);
    }
    c_second = c_value_first / c_value_second;
}

double ParabolicRegression::First(const double &value)
{
    return a_first + b_first * value + c_first * pow(value, 2.0);
}

double ParabolicRegression::Second(const double &value, const TwoDimSample &sample)
{
    return a_second + b_second * PhiOne(value, sample) + c_second * PhiTwo(value, sample);
}

double ParabolicRegression::PhiOne(const double &x, const TwoDimSample &sample)
{
    return x - sample.first.GetParameter("Average");
}

double ParabolicRegression::PhiTwo(const double &x, const TwoDimSample &sample)
{
    double x_average = sample.first.GetParameter("Average");

    return pow(x, 2.0) - (x_average_third_degree - x_average_second_degree * x_average) / pow(sample.first.GetParameter("Dispersion"), 2.0) * (x - x_average) - x_average_second_degree;
}

QList<XY> ParabolicRegression::MaxConfidenceInterval(const QList<XY> &value, const double &error_value, const TwoDimSample &sample)
{
    QList<XY> *returnValue = new QList<XY>();

    double t_value = Quantile::TQuantile(Quantile::AValue(value.size()), value.size());

    for(XY xy : value){
        double y = xy.y + t_value * error_value;
        returnValue->append(XY(xy.x, y));
    }
    return *returnValue;
}

QList<XY> ParabolicRegression::MinConfidenceInterval(const QList<XY> &value, const double &error_value, const TwoDimSample &sample)
{
    QList<XY> *returnValue = new QList<XY>();

    double t_value = Quantile::TQuantile(Quantile::AValue(value.size()), value.size());

    for(XY xy : value){
        double y = xy.y - t_value * error_value;
        returnValue->append(XY(xy.x, y));
    }
    return *returnValue;
}

QList<XY> ParabolicRegression::MaxNewConfidenceInterval(const QList<XY> &value, const double &error_value, const TwoDimSample &sample)
{
    QList<XY> *returnValue = new QList<XY>();

    double t_value = Quantile::TQuantile(Quantile::AValue(value.size()), value.size());
    double sxy_value = SYX(sample.first.samplesorted.first(), error_value, value.size(), sample.first.GetParameter("Dispersion"), sample);
    for(XY xy : value){
        double y = xy.y + t_value * sxy_value;
        returnValue->append(XY(xy.x, y));
    }
    return *returnValue;
}

QList<XY> ParabolicRegression::MinNewConfidenceInterval(const QList<XY> &value, const double &error_value, const TwoDimSample &sample)
{
    QList<XY> *returnValue = new QList<XY>();

    double t_value = Quantile::TQuantile(Quantile::AValue(value.size()), value.size());
    double sxy_value = SYX(sample.first.samplesorted.first(), error_value, value.size(), sample.first.GetParameter("Dispersion"), sample);
    for(XY xy : value){
        double y = xy.y - t_value * sxy_value;
        returnValue->append(XY(xy.x, y));
    }
    return *returnValue;
}

QList<XY> ParabolicRegression::MaxToleranceInterval(const QList<XY> &value, const double &error_value, const TwoDimSample &sample)
{
    QList<XY> *returnValue = new QList<XY>();
    double t_value = Quantile::TQuantile(Quantile::AValue(value.size()), value.size());
    for(XY xy : value){
        double y = xy.y + t_value * SYX(xy.x, error_value, value.size(), sample.first.GetParameter("Dispersion"), sample);
        returnValue->append(XY(xy.x, y));
    }
    return *returnValue;
}

QList<XY> ParabolicRegression::MinToleranceInterval(const QList<XY> &value, const double &error_value, const TwoDimSample &sample)
{
    QList<XY> *returnValue = new QList<XY>();

    double t_value = Quantile::TQuantile(Quantile::AValue(value.size()), value.size());
    for(XY xy : value){
        double y = xy.y - t_value * SYX(xy.x, error_value, value.size(), sample.first.GetParameter("Dispersion"), sample);
        returnValue->append(XY(xy.x, y));
    }
    return *returnValue;
}

double ParabolicRegression::SYX(const double &x, const double &error_value, const double &size, const double &dispersion, const TwoDimSample &sample)
{
    return error_value / sqrt((double)size) * sqrt(1.0 + pow(PhiOne(x, sample), 2.0) / pow(dispersion, 2.0) + pow(PhiTwo(x, sample), 2.0) / phi_two_average_value);
}

QList<TwoDimParameter *> ParabolicRegression::ParabolicParameter(const QString &name, const double &a, const double &b, const double &c, const double &error_value, const TwoDimSample &sample)
{
    double t_a = a / error_value * sqrt(sample.sample.size());
    double t_b = (b * sample.first.GetParameter("Dispersion")) / error_value * sqrt(sample.sample.size());
    double t_c_addition_value = 0;
    for(int i = 0; i < sample.sample.size(); i++)
        t_c_addition_value += pow(PhiTwo(sample.sample.at(i).x, sample), 2.0);
    t_c_addition_value *= (1.0 / sample.sample.size());
    double t_c = c / error_value * sqrt(sample.sample.size() * t_c_addition_value);

    double a_error_value = error_value / sqrt(sample.sample.size());
    double b_error_value = error_value / (sqrt(sample.sample.size()) * sample.first.GetParameter("Dispersion"));
    double c_error_value = error_value / (sqrt(sample.sample.size() * t_c_addition_value));

    TwoDimParameter *error_parameter = new TwoDimParameter("parabolic_error_value_" + name, error_value);
    double t_quantile = Quantile::TQuantile(1.0 - Quantile::AValue(sample.sample.size()) / 2.0, sample.sample.size() - 3);
    TwoDimParameter *parameter_a = new TwoDimParameter("parabolic_a_" + name, a, t_a, abs(t_a) > t_quantile, a - t_quantile * a_error_value, a + t_quantile * a_error_value, t_quantile);
    TwoDimParameter *parameter_b = new TwoDimParameter("parabolic_b_" + name, b, t_b, abs(t_b) > t_quantile, b - t_quantile * b_error_value, b + t_quantile * b_error_value, t_quantile);
    TwoDimParameter *parameter_c = new TwoDimParameter("parabolic_c_" + name, c, t_c, abs(t_c) > t_quantile, c - t_quantile * c_error_value, c + t_quantile * c_error_value, t_quantile);
    TwoDimParameter *a_error_parameter = new TwoDimParameter("parabolic_a_error_value_" + name, a_error_value);
    TwoDimParameter *b_error_parameter = new TwoDimParameter("parabolic_b_error_value_" + name, b_error_value);
    TwoDimParameter *c_error_parameter = new TwoDimParameter("parabolic_c_error_value_" + name, c_error_value);

    double conformity = pow(error_value, 2.0) / pow(sample.second.GetParameter("Dispersion"), 2.0);
    double f_quantile = Quantile::FQuantile(Quantile::AValue(sample.sample.size()), sample.sample.size() - 1, sample.sample.size() - 3);

    TwoDimParameter *conformity_parameter = new TwoDimParameter("parabolic_conformity_regression" + name,
                                                                conformity, conformity, conformity <= f_quantile,
                                                                0, 0, f_quantile);

    error_parameter->ua_name = "Параболічна зашилкова дисперсія(" + name + ")";
    conformity_parameter->ua_name = "Параболічна регресія відповідності(" + name + ")";
    parameter_a->ua_name = "Параболічний параметр a(" + name + ")";
    parameter_b->ua_name = "Параболічний параметр b(" + name + ")";
    parameter_c->ua_name = "Параболічний параметр c(" + name + ")";
    a_error_parameter->ua_name = "Параболічна залишкова дисперсія параметра a(" + name + ")";
    b_error_parameter->ua_name = "Параболічна залишкова дисперсія параметра b(" + name + ")";
    c_error_parameter->ua_name = "Параболічна залишкова дисперсія параметра c(" + name + ")";

    QList<TwoDimParameter*> parameters = QList<TwoDimParameter*>();
    parameters.append(error_parameter);
    parameters.append(conformity_parameter);
    parameters.append(parameter_a);
    parameters.append(parameter_b);
    parameters.append(parameter_c);
    parameters.append(a_error_parameter);
    parameters.append(b_error_parameter);
    parameters.append(c_error_parameter);
    return parameters;
}

QList<TwoDimParameter *> ParabolicRegression::buildParabolicParameter(const TwoDimSample &sample, const int &choise)
{
    switch(choise){
        case 0:
        return ParabolicParameter("fast", a_first, b_first, c_first, error_first,sample);
    case 1:
        return ParabolicParameter("slow", a_second, b_second, c_second, error_second,sample);
    default:
        return QList<TwoDimParameter*>();
    }
}

QList<XY> ParabolicRegression::buildFirst(const TwoDimSample &sample)
{
    QList<XY> value = QList<XY>();
    FirstParameter(sample);
    double error_value = 0;
    for(int i = 0; i < sample.sample.size(); i++){
        value << *new XY(sample.sample.at(i).x, First(sample.sample.at(i).x));
        error_value += pow(sample.sample.at(i).y - value.at(i).y, 2.0);
    }
    error_value *= (1.0 / (sample.sample.size() - 3.0));
    this->error_first = sqrt(error_value);
    return value;
}

QList<XY> ParabolicRegression::buildSecond(const TwoDimSample &sample)
{
    QList<XY> value = QList<XY>();
    SecondParameter(sample);
    double error_value = 0;
    for(int i = 0; i < sample.sample.size(); i++){
        value << *new XY(sample.sample.at(i).x, Second(sample.sample.at(i).x, sample));
        error_value += pow(sample.sample.at(i).y - value.at(i).y, 2.0);
    }
    error_value *= (1.0 / (sample.sample.size() - 3.0));
    this->error_second = sqrt(error_value);
    return value;
}

QList<XY> ParabolicRegression::buildRegression(const TwoDimSample &sample, const int &choise)
{

    phi_two_average_value = 0;
    for(double value : sample.first.sample)
        phi_two_average_value += pow(PhiTwo(value, sample), 2.0);

    phi_two_average_value *= (1.0 / sample.sample.size());

    x_average_second_degree = Parameter::InitialStaticMoment(sample.first.samplesorted, 2);
    x_average_third_degree = Parameter::InitialStaticMoment(sample.first.samplesorted, 3);

    switch(choise){
    case 0:
        return buildFirst(sample);
    case 1:
        return buildSecond(sample);
    default:
        return QList<XY>();
    }
}
