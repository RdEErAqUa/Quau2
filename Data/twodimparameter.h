#ifndef TWODIMPARAMETER_H
#define TWODIMPARAMETER_H
#include "twodimsample.h"

class TwoDimSample;
class TwoDimParameter{
public:
    QString name;
    double value;
    double t_value;
    bool is_significance;

    double min_value;
    double max_value;

    TwoDimParameter(const QString &name, const double &value, const double &t_value = 0,
                    const bool &is_significance = false, const double &min_value = 0, const double &max_value = 0);

    static double Average(const Sample &first,const  Sample &second);
    static TwoDimParameter* buildAverage(const TwoDimSample &sample);

    static double CorrelationCoefficient(const Sample &first,const  Sample &second);
    static TwoDimParameter* buildCorrelationCoefficient(const TwoDimSample &sample);

    static double CorrelationRatio(const QList<XMultipleY> &sample, const double &average_y);
    static TwoDimParameter* buildCorrelationRatio(const TwoDimSample &sample);

    static QList<TwoDimParameter*> buildParameters(const TwoDimSample &sample);

};

#endif // TWODIMPARAMETER_H
