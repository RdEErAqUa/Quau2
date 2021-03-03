#include "twodimparameter.h"

TwoDimParameter::TwoDimParameter(const QString &name, const double &value, const double &t_value, const bool &is_significance, const double &min_value, const double &max_value, const double &t_quantile):
    name(name), value(value), t_value(t_value), t_quantile(t_quantile),is_significance(is_significance), min_value(min_value), max_value(max_value)
{}

double TwoDimParameter::Average(const OneDimSample &first,const  OneDimSample &second){
    double value = 0;
    for(int i = 0; i < first.sample.size(); i++)
        value += first.sample[i] * second.sample[i];

    return value * (1.0 / first.sample.size());
}

TwoDimParameter *TwoDimParameter::buildAverage(const TwoDimSample &sample){
    double average = Average(sample.first, sample.second);
    return new TwoDimParameter("Average", average);
}

double TwoDimParameter::CorrelationCoefficient(const OneDimSample &first,const  OneDimSample &second){
    return first.sample.size() / (first.sample.size() - 1.0) * (Average(first, second) - first.GetParameter("Average") * second.GetParameter("Average"))
            / (first.GetParameter("Dispersion") * second.GetParameter("Dispersion"));
}

TwoDimParameter *TwoDimParameter::buildCorrelationCoefficient(const TwoDimSample &sample){
    double coefficientCorrelation = CorrelationCoefficient(sample.first, sample.second);

    double coeff = coefficientCorrelation + coefficientCorrelation * (1.0 - pow(coefficientCorrelation, 2.0)) / (sample.sample.size() * 2.0);
    double coeffPlus = Quantile::UQuantile(0.05) * (1.0 - pow(coefficientCorrelation, 2.0)) / sqrt(sample.sample.size() - 1.0);
    double t_test = coefficientCorrelation * sqrt(sample.sample.size() - 2.0) / (1.0 - pow(coefficientCorrelation, 2.0));
    return new TwoDimParameter("CorrelationCoefficient", coefficientCorrelation, t_test, abs(t_test) > Quantile::TQuantile(0.1, sample.sample.size() - 2),
                               coeff - coeffPlus, coeff + coeffPlus, Quantile::TQuantile(0.1, sample.sample.size() - 2));
}

double TwoDimParameter::CorrelationRatio(const QList<XMultipleY> &sample, const double &average_y){
    double upper_value = 0;
    double lower_value = 0;
    for(int i = 0; i < sample.size(); i++){
        double average_value = 0;
        for(int j = 0; j < sample[i].y.size(); j++){
            lower_value += pow(sample[i].y[j] - average_y, 2.0);
            average_value += sample[i].y[j];
        }
        average_value /= sample[i].y.size();

        upper_value += (sample[i].y.size() * pow(average_value - average_y, 2.0));
    }
    return (upper_value / lower_value);
}

TwoDimParameter *TwoDimParameter::buildCorrelationRatio(const TwoDimSample &sample){
    double correlationRatio = CorrelationRatio(sample.splitted_sample, sample.second.GetParameter("Average"));
    int v1 = pow(sample.splitted_sample.size() - 1 + sample.sample.size() * correlationRatio, 2.0) /
            (sample.splitted_sample.size() - 1 + 2 *  sample.sample.size() * correlationRatio);
    int v2 = sample.sample.size() - sample.splitted_sample.size();
    double ratioMax = (sample.sample.size() - sample.splitted_sample.size()) * correlationRatio/ (sample.sample.size() *
                        (1.0 - correlationRatio) * Quantile::FQuantile(0.95, v1, v2)) - (sample.splitted_sample.size() - 1.0) / sample.sample.size();
    double ratioMin = (sample.sample.size() - sample.splitted_sample.size()) * correlationRatio/ (sample.sample.size() *
                        (1.0 - correlationRatio) * Quantile::FQuantile(0.05, v1, v2)) - (sample.splitted_sample.size() - 1.0) / sample.sample.size();
    double t_test = sqrt(correlationRatio) * sqrt(sample.sample.size() - 2.0) / (1.0 - correlationRatio);
    return new TwoDimParameter("CorrelationRatio", correlationRatio, t_test, abs(t_test) > Quantile::TQuantile(0.1, sample.sample.size() - 2),
                               ratioMin, ratioMax, Quantile::TQuantile(0.1, sample.sample.size() - 2));
}

double TwoDimParameter::LinearDeterminationCoefficient(const double &correlation_coefficient)
{
    return pow(correlation_coefficient, 2.0) * 100;
}

TwoDimParameter *TwoDimParameter::buildLinearDeterminationCoefficient(const double &correlation_coefficient)
{
    return new TwoDimParameter("LinearDeterminationCoefficient", LinearDeterminationCoefficient(correlation_coefficient));
}

double TwoDimParameter::NonLinearDeterminationCoefficient(const double &correlation_ratio)
{
    return pow(correlation_ratio, 2.0) * 100;
}

TwoDimParameter *TwoDimParameter::buildNonLinearDeterminationCoefficient(const double &correlation_ratio)
{
    return new TwoDimParameter("NonLinearDeterminationCoefficient", NonLinearDeterminationCoefficient(correlation_ratio));
}

QList<TwoDimParameter *> TwoDimParameter::buildParameters(const TwoDimSample &sample){
    QList<TwoDimParameter*> *parameters = new QList<TwoDimParameter*>();
    parameters->append(buildAverage(sample));
    parameters->append(buildCorrelationCoefficient(sample));
    if(!parameters->at(1)->is_significance){
        parameters->append(buildCorrelationRatio(sample));
        parameters->append(buildNonLinearDeterminationCoefficient(parameters->at(2)->value));
    }
    parameters->append(buildLinearDeterminationCoefficient(parameters->at(1)->value));
    return *parameters;
}
