#ifndef TWODIMPARAMETER_H
#define TWODIMPARAMETER_H


#include "Data/Sample/OneDimSample/onedimsample.h"
#include "Data/Sample/TwoDimSample/twodimsample.h"

class TwoDimSample;
class TwoDimParameter{
public:
    QString name;
    QString ua_name = "";
    double value;
    double t_value;
    double t_quantile;
    bool is_significance;

    double min_value;
    double max_value;

    TwoDimParameter(const QString &name, const double &value, const double &t_value = 0,
                    const bool &is_significance = false, const double &min_value = 0, const double &max_value = 0,  const double &t_quantile = 0);

    static double Average(const OneDimSample &first,const  OneDimSample &second);
    static TwoDimParameter* buildAverage(const TwoDimSample &sample);

    static double CorrelationCoefficient(const OneDimSample &first,const  OneDimSample &second);
    static TwoDimParameter* buildCorrelationCoefficient(const TwoDimSample &sample);

    static double CorrelationRatio(const QList<XMultipleY> &sample, const double &average_y);
    static TwoDimParameter* buildCorrelationRatio(const TwoDimSample &sample);

    static double LinearDeterminationCoefficient(const double &correlation_coefficient);
    static TwoDimParameter* buildLinearDeterminationCoefficient(const double &correlation_coefficient);

    static double NonLinearDeterminationCoefficient(const double &correlation_ratio);
    static TwoDimParameter* buildNonLinearDeterminationCoefficient(const double &correlation_ratio);

    static QList<TwoDimParameter*> buildParameters(const TwoDimSample &sample);

};

#endif // TWODIMPARAMETER_H
